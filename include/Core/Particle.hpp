#pragma once

// ROOT includes
#include <Math/Vector3D.h>
#include <Math/Vector4D.h>
#include <TMath.h>

// <fmt> headers
#include <fmt/core.h>
#include <fmt/format.h>

namespace Core {

class Particle {

   private:
    // ****** private members
    int m_pdgcode;
    int m_status;
    int m_index;
    int m_charge;

    double m_mass;
    double m_px;
    double m_py;
    double m_pz;
    double m_E;
    double m_vx;
    double m_vy;
    double m_vz;
    double m_vt;
    double m_beta;
    double m_chi2pid;

    // ****** private methods

   public:
    // ****** constructors and destructor
    Particle() = delete;
    Particle(int pdg, int status, int index, int charge, double mass, double px, double py, double pz, double E, double vx, double vy, double vz, double vt, double beta, double chi2pid);

    // ****** public methods
    auto index() const -> int;
    auto charge() const -> int;
    auto pdg() const -> int;
    auto status() const -> int;

    auto PxPyPzEVector() const -> ROOT::Math::PxPyPzEVector;
    auto VxVyVzVtVector() const -> ROOT::Math::XYZTVector;
    auto PxPyPzVector() const -> ROOT::Math::XYZVector;
    auto VxVyVzVector() const -> ROOT::Math::XYZVector;

    auto phi() const -> double;
    auto theta() const -> double;
    auto theta(const Particle& other) const -> double;
    auto p() const -> double;
    auto pt() const -> double;
    auto r() const -> double;
    auto rho() const -> double;
    auto beta() const -> double;
    auto chi2pid() const -> double;
    auto E() const -> double;
    auto vx() const -> double;
    auto vy() const -> double;
    auto vz() const -> double;
    auto vt() const -> double;
    auto px() const -> double;
    auto py() const -> double;
    auto pz() const -> double;
    auto mass() const -> double;

    // ****** operators
    auto operator==(const Particle& other) const -> bool { return m_index == other.m_index; }

    auto operator!=(const Particle& other) const -> bool { return m_index != other.m_index; }

    auto operator<(const Particle& other) const -> bool { return m_index < other.m_index; }

    auto operator>(const Particle& other) const -> bool { return m_index > other.m_index; }
};
}  // namespace Core

namespace fmt {
template <>
class formatter<Core::Particle> {
   public:
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

    template <typename Context>
    constexpr auto format(Core::Particle const& foo, Context& ctx) const {
        return format_to(ctx.out(), "(PDG: {}, Index: {}, Status: {}, px: {}, py: {}, pz: {}, vx: {}, vy: {}, vz: {})", foo.pdg(), foo.index(), foo.status(), foo.px(), foo.py(), foo.pz(), foo.vx(), foo.vy(), foo.vz());
    }
};

}  // namespace fmt