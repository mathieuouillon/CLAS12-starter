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
#include <vector>
#include <hipo4/hipoeventiterator.h>
namespace study1 {

class Reader {
    using particles_map_t = std::unordered_map<int, std::vector<Core::Particle>>;

   private:
    // ****** private variables
    Histograms& m_histograms;
    const toml::parse_result& m_config;
    const std::vector<int> m_pids;

    // ****** private constants
    static constexpr double NaN = std::numeric_limits<double>::quiet_NaN();

    // ****** private methods
    auto select_electron(const Core::Particle& electron, const hipo::bank& REC_Calorimeter, const hipo::bank& REC_Cherenkov) const -> bool;
    auto get_topology(const hipo::bank& REC_Particle, particles_map_t& particle_collections) -> void;

   public:
    // ****** constructors and destructor
    explicit Reader(Histograms& histograms, const toml::parse_result& config, const std::vector<int>& pids = {11});
    ~Reader();

    // ****** public methods
    auto operator()(const std::string& file) -> void;
};

}  // namespace study1