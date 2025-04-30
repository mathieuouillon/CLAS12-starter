#pragma once

// C++ headers
#include <algorithm>
#include <chrono>
#include <filesystem>
#include <iostream>
#include <optional>
#include <ranges>
#include <vector>

// <fmt> headers
#include <fmt/core.h>

// ROOT headers
#include <TH1.h>
#include <TROOT.h>
#include <TStyle.h>

// Project headers
#include <Core/Constantes.hpp>
#include <Core/Particle.hpp>
#include <Core/Runs.hpp>

namespace Core {

/**
 * @brief Formats a given value into a string with a specified precision.
 * 
 * This function takes a value of any type that can be formatted by fmt
 * and converts it into a string representation with a fixed number of 
 * decimal places.
 * 
 * @tparam T The type of the value to be formatted.
 * @param value The value to format.
 * @param precision The number of decimal places to include in the formatted string.
 *                  Defaults to 2 if not specified.
 * @return std::string The formatted string representation of the input value.
 */
template <typename T>
std::string format_string(const T& value, int precision = 2) {
    return fmt::format("{:.{}f}", value, precision);
}

inline auto set_ROOT_option() -> void {
    ROOT::EnableThreadSafety();
    ROOT::EnableImplicitMT();
    TH1::SetDefaultSumw2(kTRUE);

    gErrorIgnoreLevel = kPrint;  // setting it to kPrint will print all messages again. kError, kFatal

    // gStyle->SetOptStat(0);
    gStyle->SetOptFit(1111);
    gStyle->SetNumberContours(255);
    gStyle->SetImageScaling(3.);

    gStyle->SetLineWidth(1);
    gStyle->SetFrameLineWidth(1);
    gStyle->SetHistLineWidth(1);
    gStyle->SetFuncWidth(1);
    gStyle->SetGridWidth(1);
    // gStyle->SetLineStyleString(1, "[12 12]");  // postscript dashes

    // put tick marks on top and RHS of plots
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
    gStyle->SetNdivisions(505, "x");
    gStyle->SetNdivisions(510, "y");

    gStyle->SetTextFont(42);
}

/**
 * @brief Reads all files recursively in a given directory, select only hipo files
 *        and reduces the output size based on a percentage of the total files.
 * 
 * @param directory The root directory to start the recursive search for files.
 * @param dataSize A percentage (0 to 100) indicating the proportion of filtered files to include in the output.
 *                 Defaults to 100, meaning all filtered files will be included.
 * 
 * @return A vector of strings containing the paths of the filtered and reduced files.
 * 
 * @details
 * - The function uses a recursive directory iterator to traverse the directory structure.
 * - Files are filtered to include only those with ".hipo" in their names.
 * - The filtered files are sorted alphabetically.
 * - The output size is reduced to a percentage of the total filtered files, as specified by the `dataSize` parameter.
 * 
 * @note
 * - If `dataSize` is set to a value less than 100, the output vector will contain fewer files.
 * - The function uses C++17 filesystem library and C++20 ranges library features.
 */
inline auto read_recursive_file_in_directory(const std::filesystem::path& directory, const double percentage = 100) -> std::vector<std::string> {

    // Check if the given directory exists and it is a directory.
    if (!std::filesystem::exists(directory)) throw std::runtime_error(fmt::format("Directory '{}' does not exist", directory.string()));
    if (!std::filesystem::is_directory(directory)) throw std::runtime_error(fmt::format("Path '{}' is not a directory", directory.string()));
    // Validate that the percentage is between 0 and 100.
    if (percentage < 0.0 || percentage > 100.0) throw std::out_of_range("Percentage must be between 0 and 100. Given: " + std::to_string(percentage));

    std::vector<std::string> files;
    //  Iterate recursively over the directory. Only add regular files with the ".hipo" extension to the list.
    for (const auto& entry : std::filesystem::recursive_directory_iterator(directory)) {
        if (entry.is_regular_file() && entry.path().extension() == ".hipo") files.push_back(entry.path().string());
    }

    std::ranges::sort(files);
    // Calculate the number of files to retain based on the provided percentage.
    const std::size_t total = files.size();
    const std::size_t num_to_keep = static_cast<std::size_t>(std::round((percentage / 100.0f) * total));
    if (num_to_keep < total) files.resize(num_to_keep);

    return files;
}

/**
 * @brief Finds the first trigger electron from a list of electrons.
 *
 * This function searches through a vector of `Core::Particle` objects representing electrons
 * and returns the first electron that satisfies the condition of having a negative status.
 * If no such electron is found, or if the found electron has a momentum of zero, the function
 * returns `std::nullopt`.
 *
 * @param electrons A vector of `Core::Particle` objects representing electrons.
 * @return An `std::optional<Core::Particle>` containing the first trigger electron if found,
 *         or `std::nullopt` if no valid trigger electron is found.
 */
inline auto find_trigger_electron(const std::vector<Core::Particle>& electrons) -> std::optional<Core::Particle> {
    if (auto result = std::ranges::find_if(electrons, [](const Core::Particle& electron) { return electron.status() < 0; });
        result != electrons.end() && result->p() != 0.0) {
        return *result;
    }
    return std::nullopt;
}

/**
 * @brief Finds the most energetic electron from a list of electrons.
 *
 * This function takes a vector of `Core::Particle` objects representing electrons
 * and returns the electron with the highest energy. If the input vector is empty
 * or if no valid electron with non-zero momentum is found, the function returns
 * `std::nullopt`.
 *
 * @param electrons A vector of `Core::Particle` objects representing electrons.
 * @return An `std::optional<Core::Particle>` containing the most energetic electron
 *         if found, or `std::nullopt` if the input vector is empty or no valid
 *         electron is found.
 */
inline auto find_most_energetic_electron(const std::vector<Core::Particle>& electrons) -> std::optional<Core::Particle> {
    if (auto result = std::ranges::max_element(electrons, [](const Core::Particle& a, const Core::Particle& b) { return a.E() < b.E(); });
        result != electrons.end() && result->p() != 0.0) {
        return *result;
    }

    return std::nullopt;
}

inline auto get_mass(const int pid) -> double {
    switch (pid) {
        case 11:
            return Core::Constantes::ElectronMass;
        case 22:
            return 0.0;
        case 211:
        case -211:
            return Core::Constantes::PionMass;
        case 321:
        case -321:
            return Core::Constantes::KaonMass;
        case 2212:
        case -2212:
            return Core::Constantes::ProtonMass;
        case 2112:
        case -2112:
            return Core::Constantes::NeutronMass;
        default:
            return std::numeric_limits<double>::quiet_NaN();
    }
    return std::numeric_limits<double>::quiet_NaN();
}

/**
 * @brief Computes the total energy of a particle given its momentum components and particle ID.
 *
 * This function calculates the energy of a particle using the relativistic energy-momentum relation:
 * E = sqrt(px^2 + py^2 + pz^2 + m^2), where m is the mass of the particle determined by its PID.
 *
 * @param px The x-component of the particle's momentum (in GeV/c).
 * @param py The y-component of the particle's momentum (in GeV/c).
 * @param pz The z-component of the particle's momentum (in GeV/c).
 * @param pid The particle ID (PDG code) used to determine the particle's mass.
 *            Supported PIDs:
 *              - 11: Electron
 *              - 22: Photon
 *              - 211, -211: Charged Pions
 *              - 321, -321: Charged Kaons
 *              - 2212, -2212: Protons
 *              - 2112, -2112: Neutrons
 *            For unsupported PIDs, the function returns NaN.
 *
 * @return The total energy of the particle (in GeV). If the PID is unsupported, returns NaN.
 */
inline auto compute_energy(double px, double py, double pz, int pid) -> double {
    double mass = get_mass(pid);
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
 * @brief Generates all unique pairs of elements from a given range.
 * 
 * This function takes a forward range as input and returns a vector of pairs,
 * where each pair represents a unique combination of two distinct elements
 * from the range. The order of elements in the pairs corresponds to their
 * order in the input range.
 * 
 * @tparam Range A forward range type that satisfies the `std::ranges::forward_range` concept
 *               and whose elements are copyable.
 * @param range The input range from which unique pairs are generated.
 * @return std::vector<std::pair<std::ranges::range_value_t<Range>, std::ranges::range_value_t<Range>>>
 *         A vector containing all unique pairs of elements from the input range.
 * 
 * @note The function pre-allocates memory for the resulting vector to improve efficiency.
 *       The number of pairs generated is `(n * (n - 1)) / 2`, where `n` is the number of
 *       elements in the input range.
 * 
 * @example
 * std::vector<int> numbers = {1, 2, 3};
 * auto pairs = generate_unique_pairs(numbers);
 * pairs will contain: {(1, 2), (1, 3), (2, 3)}
 */
template <std::ranges::forward_range Range>
requires std::copyable<std::ranges::range_value_t<Range>> [[nodiscard]] auto generate_unique_pairs(const Range& range) -> std::vector<std::pair<std::ranges::range_value_t<Range>, std::ranges::range_value_t<Range>>> {
    using T = std::ranges::range_value_t<Range>;
    std::vector<std::pair<T, T>> pairs;

    if (range.size() < 2) return {};

    pairs.reserve((std::ranges::distance(range) * (std::ranges::distance(range) - 1)) / 2);  // Pre-allocate memory for efficiency

    for (auto it1 = std::ranges::begin(range); it1 != std::ranges::end(range); ++it1) {
        for (auto it2 = std::next(it1); it2 != std::ranges::end(range); ++it2) {
            pairs.emplace_back(*it1, *it2);
        }
    }

    return pairs;
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
 * @param numBins The number of bins to divide the values into. Default is 6.
 *
 * @note The function prints the bin edges to the standard output.
 */
inline auto find_binning(const std::vector<double>& values, int numBins = 6) -> void {
    if (values.empty() || numBins <= 0) {
        std::cerr << "Error: Invalid input. Values must not be empty, and numBins must be positive." << std::endl;
        return;
    }

    int counts_per_bin = static_cast<int>(values.size()) / numBins;
    if (counts_per_bin == 0) {
        std::cerr << "Error: Number of bins exceeds the number of values." << std::endl;
        return;
    }

    auto sorted_values = values;
    std::ranges::sort(sorted_values);

    std::vector<double> bin_edges;
    bin_edges.reserve(numBins + 1);
    bin_edges.push_back(sorted_values.front());
    for (int edge = 1; edge < numBins; ++edge) {
        bin_edges.push_back(sorted_values.at(counts_per_bin * edge));
    }
    bin_edges.push_back(sorted_values.back());

    for (auto& elm : bin_edges) {
        elm = std::ceil(elm * 100.0) / 100.0;
    }

    std::cout << "bin_edges = [";
    for (size_t i = 0; i < bin_edges.size(); ++i) {
        std::cout << bin_edges[i];
        if (i != bin_edges.size() - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

/**
 * @brief Selects runs from a vector of file names based on a vector of run numbers.
 *
 * This function filters a vector of file names to include only those that contain
 * any of the specified run numbers. The filtering is done using a lambda function
 * that checks if the run number is present in the file name.
 *
 * @param runs A vector of file names to be filtered.
 * @param vec A vector of run numbers to match against the file names.
 * @return A vector of strings containing the filtered file names that match the run numbers.
 */
inline auto select_runs(const std::vector<std::string>& runs, const std::vector<std::string>& vec) -> std::vector<std::string> {
    auto filtered = runs | std::ranges::views::filter([&vec](const std::string& file_name) {
                        return std::ranges::any_of(vec, [&file_name](const std::string& run_num) {
                            return file_name.find(run_num) != std::string::npos;
                        });
                    });

    // Convert the filtered view into a vector.
    return std::vector<std::string>(filtered.begin(), filtered.end());
}

}  // namespace Core