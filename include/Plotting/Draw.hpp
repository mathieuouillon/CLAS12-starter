#pragma once

// std includes
#include <memory>
#include <string>

// ROOT includes
#include <TCanvas.h>
#include <TColor.h>
#include <TF1.h>
#include <TH1D.h>
#include <TH2D.h>
#include <THStack.h>
#include <TLegend.h>
#include <TLine.h>
#include <TMath.h>
#include <TPaveStats.h>
#include <TStyle.h>
#include <TFile.h>

// Project headers
#include <Plotting/Colors.hpp>

namespace Plotting {

/**
 * @brief Generates a linearly spaced vector of values.
 * 
 * This function creates a vector containing `num` evenly spaced values 
 * starting from `start` and ending at `end`.
 * 
 * @tparam T The type of the start and end values.
 * @param start The starting value of the sequence.
 * @param end The ending value of the sequence.
 * @param num The number of values to generate.
 * @return std::vector<T> A vector containing the linearly spaced values.
 * 
 * @note If `num` is 0, an empty vector is returned. If `num` is 1, a vector 
 * containing only the `start` value is returned.
 */
template <typename T>
auto linspace(T start, T end, const int num) -> std::vector<T> {
    std::vector<T> v;
    if (num == 0) {
        return v;
    }
    if (num == 1) {
        v.push_back(start);
        return v;
    }

    double delta = static_cast<double>(end - start) / (num - 1);

    for (int i = 0; i < num - 1; ++i) {
        v.push_back(start + delta * i);
    }
    v.push_back(end);
    return v;
}

struct Figsize {
    const uint32_t width;
    const uint32_t height;
};

/**
 * @brief Creates a shared pointer to a TCanvas object with specified dimensions.
 * 
 * @param figsize The dimensions of the canvas, specified as a Figsize object. 
 *                Default is {800, 600}.
 * @return std::shared_ptr<TCanvas> A shared pointer to the created TCanvas object.
 */
inline auto make_canvas(const Figsize figsize = {800, 600}) -> std::shared_ptr<TCanvas> {
    auto canvas = std::make_shared<TCanvas>("", "", figsize.width, figsize.height);
    canvas->SetLeftMargin(0.12f);
    canvas->SetRightMargin(0.12f);
    canvas->SetTopMargin(0.12f);
    canvas->SetBottomMargin(0.12f);

    return canvas;
}

/**
 * @brief Saves the given canvas in multiple formats.
 *
 * This function saves the provided TCanvas object in PDF, C, TeX, and ROOT file formats.
 * The files are saved in respective subdirectories under the specified path.
 *
 * @param canvas A shared pointer to the TCanvas object to be saved.
 * @param path The directory path where the files will be saved. The function assumes
 *             that subdirectories "pdf", "C", "tex", and "root" exist under this path.
 * @param file_name The base name for the saved files. The function appends the appropriate
 *                 file extension for each format.
 */
inline auto save_canvas(const std::shared_ptr<TCanvas>& canvas, const std::string& path, const std::string& file_name) -> void {
    canvas->SaveAs((path + "pdf/" + file_name + ".pdf").c_str());
    canvas->SaveAs((path + "C/" + file_name + ".C").c_str());
    canvas->SaveAs((path + "tex/" + file_name + ".tex").c_str());

    std::unique_ptr<TFile> outputFile(TFile::Open((path + "root/" + file_name + ".root").c_str(), "RECREATE"));
    auto list = canvas->GetListOfPrimitives();
    for (int i = 1; i < list->GetSize(); ++i) {
        outputFile->WriteObject(list->At(i), list->At(i)->GetName());
    }
    outputFile->Close();
}

struct Position {
    const double x1;
    const double y1;
    const double x2;
    const double y2;
};

/**
     * @brief Move the statistics boxes to fill a tile.
     *
     * This function updates the position of the statistics boxes to fill a tile with the size of it giving by the parameters.
     *
     * @param boxes A unique pointer to TObjArray that contains the stats boxes.
     * @param numColumns The number of columns in the tile.
     * @param numRows The number of rows in the tile.
     *
     * @return None.
     */
inline auto update_tile_stats(const TObjArray& boxes) -> void {
    std::vector<Position> positions;
    for (int i = 0; i < boxes.GetEntries(); i++) {
        auto stat_box = static_cast<TPaveStats*>(boxes.At(i));

        positions.emplace_back(stat_box->GetX1NDC(), stat_box->GetY1NDC(), stat_box->GetX2NDC(), stat_box->GetY2NDC());

        if (!stat_box) {
            return;
        }
        if (positions.size() == 1) {
            stat_box->SetX1NDC(positions[i].x1);
            stat_box->SetY1NDC(positions[i].y1);
            stat_box->SetX2NDC(positions[i].x2);
            stat_box->SetY2NDC(positions[i].y2);
        } else {
            stat_box->SetX1NDC(positions[i].x1);
            stat_box->SetY1NDC(positions[i].y1 - (positions[i - 1].y2 - positions[i - 1].y1));
            stat_box->SetX2NDC(positions[i].x2);
            stat_box->SetY2NDC(positions[i].y2 - (positions[i - 1].y2 - positions[i - 1].y1));
        }
    }
}

template <typename... Args>
inline auto set_stat_boxes(const std::shared_ptr<TCanvas>& canvas, Args&&... args) -> void {
    canvas->Update();
    TObjArray boxes;
    for (const auto& h : {args...}) {
        auto st = dynamic_cast<TPaveStats*>(h->GetListOfFunctions()->FindObject("stats"));
        st->SetTextColor(h->GetLineColor());
        st->Draw();
        boxes.Add(st);
    }
    update_tile_stats(boxes);
    canvas->Modified();
}

/**
 * @brief Options for drawing a 1D histogram.
 */
struct OptionTH1 {
    const std::string file_name = "";

    const int16_t color1 = Color::kBlack;
    const float alpha_color1 = 0.0;

    const int16_t color2 = Color::kBlue;
    const float alpha_color2 = 0.0;

    const std::string draw_option = "histo";
    const std::string opt_stat = "emr";

    const std::pair<double, double> x_range = {};

    const std::vector<double> cuts = {};

    const double scale1 = 0;
    const double scale2 = 0;

    const std::string legend1 = "";
    const std::string legend2 = "";
    const std::string title = "";

    const bool log_x = false;
    const bool log_y = false;

    // label
    const std::string label = "";
    const float label_offset = 0.8f;
    const float label_size = 0.05f;
};

inline auto draw_hist1D(const std::shared_ptr<TH1>& h, const std::string& path, const OptionTH1& args = {}) -> void {

    std::shared_ptr<TCanvas> canvas = make_canvas();
    std::string file_name = args.file_name.empty() ? h->GetName() : args.file_name;

    gStyle->SetOptStat(args.opt_stat.data());

    h->Draw(args.draw_option.data());
    h->SetLineColor(args.color1);
    h->SetFillColorAlpha(args.color1, args.alpha_color1);

    h->GetXaxis()->SetTitle(args.label.data());
    h->GetXaxis()->SetTitleOffset(args.label_offset);
    h->GetXaxis()->SetTitleSize(args.label_size);

    if (!args.title.empty()) h->SetTitle(args.title.data());
    if (args.log_x) canvas->SetLogx();
    if (args.log_y) canvas->SetLogy();

    for (double cut : args.cuts) {
        TLine line;
        line.SetLineColor(Color::kRed);
        line.SetLineWidth(2);
        line.DrawLine(cut, 0, cut, 0.8 * h->GetMaximum());
    }

    if (args.opt_stat == "emr") set_stat_boxes(canvas, h);
    save_canvas(canvas, path, file_name);
}

inline auto draw_hist1D(const std::shared_ptr<TH1>& h1, const std::shared_ptr<TH1>& h2, const std::string& path, const OptionTH1& args = {}) -> void {

    std::shared_ptr<TCanvas> canvas = make_canvas();
    std::string file_name = args.file_name.empty() ? h1->GetName() : args.file_name;
    const auto hStack = std::make_shared<THStack>("hs", "");

    gStyle->SetOptStat(args.opt_stat.data());

    h1->SetLineColor(args.color1);
    h1->SetFillColorAlpha(args.color1, args.alpha_color1);
    if (args.scale1 != 0) h1->Scale(args.scale1);
    if (args.scale2 != 0) h2->Scale(args.scale2);
    h2->SetLineColor(args.color2);
    h2->SetFillColorAlpha(args.color1, args.alpha_color2);

    hStack->Add(h1.get(), "hist");
    hStack->Add(h2.get(), "hist");
    hStack->Draw("nostack");

    hStack->GetXaxis()->SetTitle(args.label.data());
    hStack->GetXaxis()->SetTitleOffset(args.label_offset);
    hStack->GetXaxis()->SetTitleSize(args.label_size);

    if (!args.title.empty()) hStack->SetTitle(args.title.data());
    if (args.log_x) canvas->SetLogx();
    if (args.log_y) canvas->SetLogy();

    for (double cut : args.cuts) {
        TLine line;
        line.SetLineColor(Color::kRed);
        line.SetLineWidth(2);
        line.DrawLine(cut, 0, cut, 0.8 * std::max({h1->GetMaximum(), h2->GetMaximum()}));
    }

    auto legend = new TLegend();
    if (!args.legend1.empty()) {
        legend->AddEntry(h1.get(), args.legend1.data(), "l");
    }
    if (!args.legend2.empty()) {
        legend->AddEntry(h2.get(), args.legend2.data(), "l");
    }
    if (!args.legend1.empty() || !args.legend2.empty()) {
        legend->Draw();
    }

    if (args.opt_stat == "emr") set_stat_boxes(canvas, h1, h2);
    save_canvas(canvas, path, file_name);
}

struct OptionTH2 {
    const std::string& file_name = "";

    const bool log_x = false;
    const bool log_y = false;
    const bool log_z = false;

    const std::string label_x;
    const float label_x_offset = 0.8f;
    const float label_x_size = 0.05f;

    const std::string label_y;
    const float label_y_offset = 1.0f;
    const float label_y_size = 0.05f;
};

inline auto draw_hist2D(const std::shared_ptr<TH2D>& h, const std::string& path, const OptionTH2& args = {}) -> void {
    const auto canvas = make_canvas();
    const auto myFileName = args.file_name.empty() ? h->GetName() : args.file_name;

    h->Draw("COLZ");

    h->GetXaxis()->SetTitle(args.label_x.data());
    h->GetXaxis()->SetTitleOffset(args.label_x_offset);
    h->GetXaxis()->SetTitleSize(args.label_x_size);

    h->GetYaxis()->SetTitle(args.label_y.data());
    h->GetYaxis()->SetTitleOffset(args.label_y_offset);
    h->GetYaxis()->SetTitleSize(args.label_y_size);

    if (args.log_x) canvas->SetLogx();
    if (args.log_y) canvas->SetLogy();
    if (args.log_z) canvas->SetLogz();

    save_canvas(canvas, path, myFileName);
}

}  // namespace Plotting