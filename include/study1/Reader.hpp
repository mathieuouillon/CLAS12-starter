#pragma once

// C++ headers
#include <string>

// <fmt> headers
#include <fmt/core.h>

// toml++ headers
#include <toml++/toml.h>

// Project headers
#include <hipo4/reader.h>
#include <Core/Constantes.hpp>
#include <Core/Helpers.hpp>
#include <Core/Particle.hpp>
#include <Core/ReadBank.hpp>
#include <study1/Histograms.hpp>

namespace study1 {

class Reader {
   private:
    struct Topology {
        std::vector<Core::Particle> electrons;
    };

    Histograms& m_histograms;
    const toml::parse_result& m_config;

    const double NaN = std::numeric_limits<double>::quiet_NaN();

    // ****** private methods
    auto get_topology(const hipo::bank& REC_Particle) const -> Topology;
    auto select_electron(const Core::Particle& electron, const hipo::bank& REC_Calorimeter, const hipo::bank& REC_Cherenkov) const -> bool;

   public:
    // ****** constructors and destructor
    explicit Reader(Histograms& histograms, const toml::parse_result& config);
    ~Reader();

    // ****** public methods
    auto operator()(const std::string& file) const -> void;
};

}  // namespace study1