#include <study1/Reader.hpp>

namespace study1 {

Reader::Reader(Histograms& histograms, const toml::parse_result& config)
    : m_histograms(histograms), m_config(config) {
}

Reader::~Reader() = default;

auto Reader::operator()(const std::string& file) const -> void {

    auto dict = hipo::dictionary();
    auto reader = hipo::reader(file, dict);
    auto hipo_event = hipo::event();

    fmt::println("Entries: {}", reader.getEntries());

    auto REC_Particle = hipo::bank(dict.getSchema("REC::Particle"));
    auto REC_Calorimeter = hipo::bank(dict.getSchema("REC::Calorimeter"));
    auto REC_Cherenkov = hipo::bank(dict.getSchema("REC::Cherenkov"));
    auto REC_Event = hipo::bank(dict.getSchema("REC::Event"));

    int counter = 0;
    while (reader.next(hipo_event, REC_Particle, REC_Calorimeter, REC_Event, REC_Cherenkov) /*&& counter < 10*/) {
        if (REC_Particle.getRows() == 0) continue;
        counter++;

        Topology topology = get_topology(REC_Particle);

        auto possible_electron = Core::find_trigger_electron(topology.electrons);
        if (!possible_electron.has_value()) continue;
        Core::Particle electron = possible_electron.value();

        bool pass_electron_cuts = select_electron(electron, REC_Calorimeter, REC_Cherenkov);
        if (!pass_electron_cuts) continue;
    }
}

auto Reader::get_topology(const hipo::bank& REC_Particle) const -> Topology {
    std::vector<Core::Particle> electrons;

    for (int i = 0; i < REC_Particle.getRows(); i++) {
        int pid = REC_Particle.get<int>("pid", i);
        int status = REC_Particle.get<int>("status", i);
        int charge = REC_Particle.get<int>("charge", i);

        double px = REC_Particle.get<double>("px", i);
        double py = REC_Particle.get<double>("py", i);
        double pz = REC_Particle.get<double>("pz", i);
        double vx = REC_Particle.get<double>("vx", i);
        double vy = REC_Particle.get<double>("vy", i);
        double vz = REC_Particle.get<double>("vz", i);
        double vt = REC_Particle.get<double>("vt", i);
        double beta = REC_Particle.get<double>("beta", i);
        double chi2pid = REC_Particle.get<double>("chi2pid", i);
        double E = Core::compute_energy(px, py, pz, pid);

        if (pid == 11) electrons.emplace_back(pid, status, i, charge, Core::Constantes::ElectronMass, px, py, pz, E, vx, vy, vz, vt, beta, chi2pid);
    }

    return {.electrons = electrons};
}

auto Reader::select_electron(const Core::Particle& electron, const hipo::bank& REC_Calorimeter, const hipo::bank& REC_Cherenkov) const -> bool {
    bool pass = false;

    Core::CherenkovBank cherenkov = Core::read_Cherenkov_bank(REC_Cherenkov, electron.index());
    Core::CalorimeterBank calorimeter = Core::read_Calorimeter_bank(REC_Calorimeter, electron.index());

    double ETot = calorimeter.pcal.energy + calorimeter.inner.energy + calorimeter.outer.energy;
    double SF = ETot / electron.p();

    // Cuts ---------------------------------------------------------------------------------------
    const double vz_min_e = m_config["electron"]["vz_min"].value_or(NaN);
    const double vz_max_e = m_config["electron"]["vz_max"].value_or(NaN);
    const double chi2_min_e = m_config["electron"]["chi2_min"].value_or(NaN);
    const double chi2_max_e = m_config["electron"]["chi2_max"].value_or(NaN);
    //---------------------------------------------------------------------------------------------

    // Get variables for electrons kinematics to apply the cuts -----------------------------------
    const double p_e = electron.p();
    const double chi2_e = electron.chi2pid();
    const double vz_e = electron.vz();
    const double phi_e = electron.phi();
    const double theta_e = electron.theta();
    //---------------------------------------------------------------------------------------------

    // Cuts ---------------------------------------------------------------------------------------
    const bool cut_chi2 = chi2_min_e < chi2_e && chi2_e < chi2_max_e;
    const bool cut_vz = vz_min_e <= vz_e && vz_e <= vz_max_e;
    const bool cuts = cut_chi2 && cut_vz;
    // --------------------------------------------------------------------------------------------

    // Fill the histograms before any cuts are applied --------------------------------------------
    m_histograms.electron.hist1D_p->Get()->Fill(p_e);
    m_histograms.electron.hist1D_phi->Get()->Fill(phi_e);
    m_histograms.electron.hist1D_theta->Get()->Fill(theta_e);
    m_histograms.electron.hist1D_chi2->Get()->Fill(chi2_e);
    m_histograms.electron.hist1D_vz->Get()->Fill(vz_e);

    //---------------------------------------------------------------------------------------------

    // Fill histograms after cuts: ----------------------------------------------------------------
    if (cut_chi2) m_histograms.electron.hist1D_vz_cut->Get()->Fill(vz_e);
    if (cut_vz) m_histograms.electron.hist1D_chi2_cut->Get()->Fill(chi2_e);

    if (cuts) {
        m_histograms.electron.hist1D_p_cut->Get()->Fill(p_e);
        m_histograms.electron.hist1D_phi_cut->Get()->Fill(phi_e);
        m_histograms.electron.hist1D_theta_cut->Get()->Fill(theta_e);
        pass = true;
    }
    //---------------------------------------------------------------------------------------------

    return pass;
}

}  // namespace study1