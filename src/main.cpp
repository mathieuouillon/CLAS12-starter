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
#include <Core/Helpers.hpp>
#include <study1/Histograms.hpp>
#include <study1/Reader.hpp>
#include <study1/Drawing.hpp>

#include <thread_pool/multi_thread.hpp>

auto SetROOTOption() -> void {
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


int main(int argc, char* argv[]) {
    ROOT::EnableThreadSafety();  // To stop random errors in multithread mode
    SetROOTOption();

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

