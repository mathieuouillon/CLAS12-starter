#include <Core/Particle.hpp>

namespace Core {

Particle::Particle(int pdg, int status, int index, int charge, double mass, double px, double py, double pz, double E, double vx, double vy, double vz, double vt, double beta, double chi2pid)
    : m_pdgcode(pdg), m_status(status), m_index(index), m_charge(charge), m_mass(mass), m_px(px), m_py(py), m_pz(pz), m_E(E), m_vx(vx), m_vy(vy), m_vz(vz), m_vt(vt), m_beta(beta), m_chi2pid(chi2pid) {
}

auto Particle::phi() const -> double {
    return m_px == 0.0 && m_py == 0.0 ? 0.0 : TMath::ATan2(m_py,m_px) * 180. / TMath::Pi();
};

auto Particle::theta() const -> double {
    return (m_pz == 0) ? TMath::PiOver2() * 180. / TMath::Pi() : TMath::ACos(m_pz / p()) * 180. / TMath::Pi();
}

auto Particle::theta(const Particle& other) const -> double {
    double product = p() * other.p();
    product = product == 0 ? 1 : (m_px * other.px() + m_py * other.py() + m_pz * other.pz()) / product;
    product = std::max(std::min(product, 1.0), -1.0);
    return TMath::ACos(product);
}

auto Particle::PxPyPzEVector() const -> ROOT::Math::PxPyPzEVector {
    return {m_px, m_py, m_pz, m_E};
}

auto Particle::VxVyVzVtVector() const -> ROOT::Math::XYZTVector {
    return {m_vx, m_vy, m_vz, m_vt};
}

auto Particle::PxPyPzVector() const -> ROOT::Math::XYZVector {
    return {m_px, m_py, m_pz};
}

auto Particle::VxVyVzVector() const -> ROOT::Math::XYZVector {
    return {m_vx, m_vy, m_vz};
}

auto Particle::r() const -> double {
    return TMath::Sqrt(m_vx * m_vx + m_vy * m_vy);
}

auto Particle::rho() const -> double {
    return TMath::Sqrt(m_vx * m_vx + m_vy * m_vy + m_vz * m_vz);
}

auto Particle::p() const -> double {
    return TMath::Sqrt(m_px * m_px + m_py * m_py + m_pz * m_pz);
}

auto Particle::pt() const -> double {
    return TMath::Sqrt(m_px * m_px + m_py * m_py);
}

auto Particle::index() const -> int {
    return m_index;
}

auto Particle::charge() const -> int {
    return m_charge;
}

auto Particle::pdg() const -> int {
    return m_pdgcode;
}

auto Particle::status() const -> int {
    return m_status;
}

auto Particle::beta() const -> double {
    return m_beta;
}

auto Particle::chi2pid() const -> double {
    return m_chi2pid;
}

auto Particle::E() const -> double {
    return m_E;
}

auto Particle::vx() const -> double {
    return m_vx;
}

auto Particle::vy() const -> double {
    return m_vy;
}

auto Particle::vz() const -> double {
    return m_vz;
}

auto Particle::vt() const -> double {
    return m_vt;
}

auto Particle::px() const -> double {
    return m_px;
}

auto Particle::py() const -> double {
    return m_py;
}

auto Particle::pz() const -> double {
    return m_pz;
}

auto Particle::mass() const -> double {
    return m_mass;
}

}  // namespace Core