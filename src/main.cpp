// C++ headers
#include <algorithm>
#include <chrono>
#include <filesystem>
#include <iostream>
#include <ranges>
#include <vector>

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

int main(int argc, char* argv[]) {
    ROOT::EnableThreadSafety();  // To stop random errors in multithread mode

    auto start_time = std::chrono::high_resolution_clock::now();

    // Read the configuration file
    const toml::table config = toml::parse_file("../config/study1.toml");

    // Read the files
    std::vector<std::string> files = Core::read_recursive_file_in_directory("../data/");
    
    // Process the data
    study1::Histograms histograms;
    study1::Reader reader(histograms, config);
    multithread_reader(reader, files, 1);

    // Draw the histograms
    study1::Drawing drawing(histograms, config);
    drawing.draw_electron_kinematics();

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);

    fmt::println("Time take: {} seconds", duration.count());
    

    return EXIT_SUCCESS;
}

