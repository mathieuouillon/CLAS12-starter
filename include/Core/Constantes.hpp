#pragma once

#include <numbers>

namespace Core::Constantes {
static constexpr double ElectronMass = 0.00051099891;
static constexpr double ProtonMass = 0.938272;
static constexpr double ProtonMassSquare = ProtonMass * ProtonMass;
static constexpr double NeutronMass = 0.93956536;
static constexpr double NeutronMassSquare = NeutronMass * NeutronMass;
static constexpr double NucleonMass = (ProtonMass + NeutronMass) / 2;
static constexpr double Pion0Mass = 0.1349768;
static constexpr double DeuteriumMass = 1.87561294257;
static constexpr double DeuteriumMassSquare = DeuteriumMass * DeuteriumMass;
static constexpr double PionMass = 0.1396;
static constexpr double Rho0Mass = 0.770;
static constexpr double Rho0MassSquare = Rho0Mass * Rho0Mass;
static constexpr double KaonMass = 0.493677;
static constexpr double KaonMassSquare = KaonMass * KaonMass;

}  // namespace Core::Constantes