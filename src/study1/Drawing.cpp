#include <study1/Drawing.hpp>

namespace study1 {

Drawing::Drawing(Histograms& histograms, const toml::parse_result& config)
    : m_histograms(histograms), m_config(config) {
}

auto Drawing::draw_electron_kinematics() -> void {

    // Cuts ---------------------------------------------------------------------------------------
    const double vz_min_e = m_config["electron"]["vz_min"].value_or(NaN);
    const double vz_max_e = m_config["electron"]["vz_max"].value_or(NaN);
    const double chi2_min_e = m_config["electron"]["chi2_min"].value_or(NaN);
    const double chi2_max_e = m_config["electron"]["chi2_max"].value_or(NaN);
    //---------------------------------------------------------------------------------------------

    // Merge 1D histograms ------------------------------------------------------------------------
    const std::shared_ptr<TH1D> hist1D_p = m_histograms.electron.hist1D_p->Merge();
    const std::shared_ptr<TH1D> hist1D_chi2 = m_histograms.electron.hist1D_chi2->Merge();
    const std::shared_ptr<TH1D> hist1D_phi = m_histograms.electron.hist1D_phi->Merge();
    const std::shared_ptr<TH1D> hist1D_theta = m_histograms.electron.hist1D_theta->Merge();
    const std::shared_ptr<TH1D> hist1D_vz = m_histograms.electron.hist1D_vz->Merge();

    const std::shared_ptr<TH1D> hist1D_p_cut = m_histograms.electron.hist1D_p_cut->Merge();
    const std::shared_ptr<TH1D> hist1D_chi2_cut = m_histograms.electron.hist1D_chi2_cut->Merge();
    const std::shared_ptr<TH1D> hist1D_phi_cut = m_histograms.electron.hist1D_phi_cut->Merge();
    const std::shared_ptr<TH1D> hist1D_theta_cut = m_histograms.electron.hist1D_theta_cut->Merge();
    const std::shared_ptr<TH1D> hist1D_vz_cut = m_histograms.electron.hist1D_vz_cut->Merge();
    // --------------------------------------------------------------------------------------------

    Plotting::draw_hist1D(hist1D_p, hist1D_p_cut, m_path_electron, {.label = "p_{e} [GeV/c]"});
    Plotting::draw_hist1D(hist1D_chi2, hist1D_chi2_cut, m_path_electron, {.cuts = {chi2_min_e, chi2_max_e}, .label = "chi2pid_{e}"});
    Plotting::draw_hist1D(hist1D_phi, hist1D_phi_cut, m_path_electron, {.label = "#phi_{e} [deg.]"});
    Plotting::draw_hist1D(hist1D_theta, hist1D_theta_cut, m_path_electron, {.label = "#theta_{e} [deg.]"});
    Plotting::draw_hist1D(hist1D_vz, hist1D_vz_cut, m_path_electron, {.cuts = {vz_min_e, vz_max_e}, .label = "Vz_{e} [cm]"});
}


}  // namespace study1