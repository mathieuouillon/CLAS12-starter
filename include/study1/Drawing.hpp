#pragma once

// C++ headers
#include <limits>

// toml headers
#include <toml++/toml.h>

// Project headers
#include <Plotting/Draw.hpp>
#include <study1/Histograms.hpp>

namespace study1 {
class Drawing {

   private:
    // ****** private members
    Histograms& m_histograms;
    const toml::parse_result& m_config;
    const std::string m_path_electron = "../plots/electron/";

    const double NaN = std::numeric_limits<double>::quiet_NaN();

    // ****** private methods

   public:
    // ****** constructors and destructor
    explicit Drawing(Histograms& histograms, const toml::parse_result& config);

    // ****** public methods
    auto draw_electron_kinematics() -> void;
};

}  // namespace study1