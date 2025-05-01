// C++ headers
#include <algorithm>
#include <chrono>
#include <filesystem>
#include <iostream>
#include <ranges>
#include <vector>
#include <numeric>

// fmt headers
#include <fmt/core.h>
#include <fmt/ranges.h>

#include <toml++/toml.hpp>

// ROOT headers
#include <TCanvas.h>
#include <TH1D.h>
#include <TLine.h>
#include <TROOT.h>
#include <TStyle.h>

// Project headers
#include <Core/Constantes.hpp>
#include <Core/Helpers.hpp>
#include <study1/Histograms.hpp>
#include <study1/Reader.hpp>
#include <study1/Drawing.hpp>
#include <thread_pool/multi_thread.hpp>

int main() {
    ROOT::EnableThreadSafety();  // To stop random errors in multithread mode

    std::vector<double> times;



    for (int i = 0; i < 100; ++i) {
        
        auto start_time = std::chrono::high_resolution_clock::now();

        // Read the configuration file
        const toml::table config = toml::parse_file("../config/study1.toml");

        // Read the files
        std::vector<std::string> files = Core::read_recursive_file_in_directory("../data/");
        
        // Process the data
        study1::Histograms histograms;
        study1::Reader reader(histograms, config);
        multithread_reader(reader, files, 1);

        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

        fmt::println("Time take: {} milliseconds", duration.count());
        times.push_back(duration.count());
    }

    // Calculate the average time
    double sum = std::accumulate(times.begin(), times.end(), 0.0);
    double average = sum / times.size();
    fmt::println("Average time: {} milliseconds", average);
    // Calculate the standard deviation
    double sq_sum = std::inner_product(times.begin(), times.end(), times.begin(), 0.0);
    double stdev = std::sqrt(sq_sum / times.size() - average * average);
    fmt::println("Standard deviation: {} milliseconds", stdev);

    return EXIT_SUCCESS;
}

