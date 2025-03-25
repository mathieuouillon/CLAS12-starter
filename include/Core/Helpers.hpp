#pragma once

// C++ headers
#include <algorithm>
#include <chrono>
#include <filesystem>
#include <iostream>
#include <optional>
#include <ranges>
#include <vector>

// Project headers
#include <Core/Particle.hpp>
#include <Core/Constantes.hpp>

namespace Core {

template <typename T>
inline auto format_string(const T a, int precision = 2) -> std::string {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(precision) << a;
    return stream.str();
}

inline auto read_recursive_file_in_directory(const std::filesystem::path& directory, const float dataSize = 100) -> std::vector<std::string> {
    auto f = [](const std::filesystem::directory_entry& entry) {
        return std::string(entry.path());
    };
    auto pred = [](std::string_view fileName) {
        return fileName.find(".hipo") != std::string::npos;
    };

    std::vector<std::string> fileNames;
    std::vector<std::string> output;
    std::vector<std::string> reduceFiles;
    auto iterator = std::filesystem::recursive_directory_iterator{directory};
    std::transform(begin(iterator), end(iterator), std::back_inserter(fileNames), f);
    std::ranges::copy_if(fileNames, std::back_inserter(output), pred);
    std::ranges::sort(output);

    output.resize(static_cast<int>(dataSize / 100 * static_cast<float>(output.size())));
    return output;
}

inline auto find_trigger_electron(std::vector<Core::Particle>& electrons) -> std::optional<Core::Particle> {
    auto result = std::ranges::find_if(electrons, [](const Core::Particle& electron) { return electron.status() < 0; });
    if (result == electrons.end()) return std::nullopt;
    Core::Particle electron = *result;

    // Sanity check, probably not needed
    if (electron.p() == 0.0) return std::nullopt;

    return electron;
}

inline auto find_most_energetic_electron(std::vector<Core::Particle>& electrons) -> std::optional<Core::Particle> {
    auto result = std::ranges::max(electrons, [](const Core::Particle& a, const Core::Particle& b) { return a.E() < b.E(); });
    Core::Particle electron = result;

    // if (electron.p() == 0.0) return std::nullopt;

    return electron;
}

inline auto compute_energy(double px, double py, double pz, int pid) -> double {
    double mass = std::numeric_limits<double>::quiet_NaN();
    if (pid == 11)
        mass = Core::Constantes::ElectronMass;
    if (pid == 22)
        mass = 0.;
    if (pid == 211 || pid == -211)
        mass = Core::Constantes::PionMass;
    if (pid == 321 || pid == -321)
        mass = Core::Constantes::KaonMass;
    return std::hypot(std::hypot(px, py, pz), mass);
}

/**
 * @brief Computes the floating-point modulo operation.
 *
 * This function calculates the remainder of the division of `x` by `y` using
 * floating-point arithmetic. It handles boundary cases that may result from
 * floating-point precision issues.
 *
 * @tparam T The type of the input values, expected to be a floating-point type.
 * @param x The dividend.
 * @param y The divisor.
 * @return The remainder of the division of `x` by `y`.
 *
 * @note The function uses `static_assert` to ensure that the template parameter
 *       `T` is a floating-point type.
 * @note If `y` is zero, the function returns `x`.
 * @note The function handles boundary cases where floating-point precision
 *       might cause unexpected results.
 */
template <typename T>
auto mod(const T x, const T y) -> T {
    static_assert(!std::numeric_limits<T>::is_exact, "Mod: floating-point type expected");

    if (0. == y) return x;

    double m = x - y * floor(x / y);
    // handle boundary cases resulted from floating-point cut off:
    if (y > 0) {               // modulo range: [0..y)
        if (m >= y) return 0;  // Mod(-1e-16             , 360.    ): m= 360.
        if (m < 0) {
            if (y + m == y) return 0;  // just in case...
            else
                return y + m;  // Mod(106.81415022205296 , _TWO_PI ): m= -1.421e-14
        }
    } else {                   // modulo range: (y..0]
        if (m <= y) return 0;  // Mod(1e-16              , -360.   ): m= -360.
        if (m > 0) {
            if (y + m == y) return 0;  // just in case...
            else
                return y + m;  // Mod(-106.81415022205296, -_TWO_PI): m= 1.421e-14
        }
    }

    return m;
}

/**
 * @brief Warps an angle to the range [-180, 180].
 *
 * This function takes an angle and normalizes it to be within the range
 * of -π to π. It uses the modulo operation to wrap the angle around
 * the circle and then shifts it to the desired range.
 *
 * @param angle The angle in degree.
 * @return The angle within the range [-180, 180].
 */
inline double warp_neg_pos_pi(double angle) {
    return mod(angle, 2. * 180) - 180;
}

/**
 * @brief Determines the sector based on the given angle phi.
 * 
 * This function takes an angle phi (in degrees) and determines which sector 
 * it belongs to. The sectors are defined as follows:
 * - Sector 1: -30 <= phi < 30
 * - Sector 2: 30 <= phi < 90
 * - Sector 3: 90 <= phi < 150
 * - Sector 4: phi >= 150 or phi < -150
 * - Sector 5: -150 <= phi < -90
 * - Sector 6: -90 <= phi < -30
 * 
 * @param phi The angle in degrees for which the sector needs to be determined.
 * @return int The sector number (1 to 6) or -1 if the angle does not fall into any sector.
 */
inline auto determine_sector(double phi) -> int {
    if (phi <= 30 && phi > -30) {
        return 1;
    } else if (phi <= 90 && phi > 30) {
        return 2;
    } else if (phi <= 150 && phi > 90) {
        return 3;
    } else if (phi > 150 || phi <= -150) {
        return 4;
    } else if (phi <= -90 && phi > -150) {
        return 5;
    } else if (phi <= -30 && phi > -90) {
        return 6;
    }
    return -1;
}

template <class iterator_type>
class combination_generator {
    iterator_type first;
    iterator_type last;
    std::vector<bool> use;
    unsigned r;
    using element_type = typename std::iterator_traits<iterator_type>::value_type;

   public:
    combination_generator(iterator_type first_, iterator_type last_, unsigned r_)
        : first(first_), last(last_), r(r_) {
        use.resize(std::distance(first, last), false);
        if (r > use.size()) throw std::domain_error("can't select more elements than exist for combination");
        std::fill(use.end() - r, use.end(), true);
    }

    bool operator()(std::vector<std::vector<element_type>>& result) {
        iterator_type c = first;
        std::vector<element_type> v;
        v.reserve(r);
        for (unsigned i = 0; i < use.size(); ++i, ++c)
            if (use[i]) v.emplace_back(*c);

        result.emplace_back(v);
        return std::next_permutation(use.begin(), use.end());
    }
};

template <class iterator_type>
combination_generator<iterator_type> MakeCombinationGenerator(iterator_type first, iterator_type last, unsigned r) {
    return combination_generator<iterator_type>(first, last, r);
}

/**
 * @brief Finds bin edges for a given set of values.
 *
 * This function takes a vector of double values and calculates bin edges
 * based on the specified number of bins. The values are first sorted, and
 * then the bin edges are determined by taking the value at regular intervals
 * (countsPerBin) within the sorted vector. The bin edges are then rounded up
 * to two decimal places.
 *
 * @param values A vector of double values to be binned.
 * @param numBins The number of bins to divide the values into. Default is 2.
 *
 * @note The function prints the bin edges to the standard output.
 */
inline auto find_binning(std::vector<double> values, int numBins = 6) -> void {
    int counts_per_bin = static_cast<int>(values.size()) / numBins;

    std::ranges::sort(values);

    std::vector<double> bin_edges;
    bin_edges.push_back(values.front());
    for (int edge = 1; edge < numBins; edge++)
        bin_edges.push_back(values.at(counts_per_bin * edge));

    bin_edges.push_back(values.back());

    for (auto& elm : bin_edges)
        elm = std::ceil(elm * 100.0) / 100.0;

    std::cout << "bin_edges = [";
    for (auto elm : bin_edges) {
        std::cout << elm;
        if (&elm != &bin_edges.back()) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

}  // namespace Core