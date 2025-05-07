#pragma once

// std includes
#include <iostream>
#include <string>
#include <vector>

// <fmt> headers
#include <fmt/core.h>
#include <fmt/ranges.h>

// ROOT includes
#include <TCanvas.h>
#include <TColor.h>
#include <TF1.h>
#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <THStack.h>
#include <TLegend.h>
#include <TLine.h>
#include <TMath.h>
#include <TPaveStats.h>
#include <TStyle.h>

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
    if (num == 0) return {};
    if (num == 1) return {start};

    std::vector<T> v;
    v.reserve(num);

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
inline auto make_canvas(const Figsize figsize = {800, 600}, const std::array<float, 4>& margins = {0.12f, 0.12f, 0.12f, 0.12f}) -> std::shared_ptr<TCanvas> {
    auto canvas = std::make_shared<TCanvas>("", "", figsize.width, figsize.height);
    canvas->SetLeftMargin(margins[0]);
    canvas->SetRightMargin(margins[1]);
    canvas->SetTopMargin(margins[2]);
    canvas->SetBottomMargin(margins[3]);

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
    if (!canvas) throw std::invalid_argument("Canvas pointer cannot be null");
    if (path.empty() || file_name.empty()) throw std::invalid_argument("Path and filename cannot be empty");

    canvas->SaveAs((path + "pdf/" + file_name + ".pdf").c_str());

    std::unique_ptr<TFile> output_file(TFile::Open((path + "root/" + file_name + ".root").c_str(), "RECREATE"));
    if (!output_file || output_file->IsZombie()) throw std::runtime_error("Failed to create ROOT file: " + path + "root/");
    canvas->Write("canvas");
    auto list = canvas->GetListOfPrimitives();
    for (int i = 1; i < list->GetSize(); ++i) {
        output_file->WriteObject(list->At(i), list->At(i)->GetName());
    }
    output_file->Close();
}

/**
 * @brief Represents a position of a box in normalized coordinates.
 */
struct Position {
    const double x1;  ///< Left position (0.0-1.0)
    const double y1;  ///< Bottom position (0.0-1.0)
    const double x2;  ///< Right position (0.0-1.0)
    const double y2;  ///< Top position (0.0-1.0)

    /**
     * @brief Constructor with validation.
     * 
     * @param x1_ Left position (0.0-1.0)
     * @param y1_ Bottom position (0.0-1.0)
     * @param x2_ Right position (0.0-1.0)
     * @param y2_ Top position (0.0-1.0)
     * @throws std::invalid_argument If coordinates are invalid (not in [0,1] or x1>=x2 or y1>=y2)
     */
    Position(double x1_, double y1_, double x2_, double y2_) : x1(x1_), y1(y1_), x2(x2_), y2(y2_) {
        const bool valid_range =
            x1 >= 0.0 && x1 <= 1.0 &&
            y1 >= 0.0 && y1 <= 1.0 &&
            x2 >= 0.0 && x2 <= 1.0 &&
            y2 >= 0.0 && y2 <= 1.0;
        const bool valid_order = (x1 < x2) && (y1 < y2);

        if (!valid_range || !valid_order) throw std::invalid_argument("Invalid position coordinates");
    }

    /**
     * @brief Get the width of the box.
     * @return Width in NDC units
     */
    double width() const { return x2 - x1; }

    /**
     * @brief Get the height of the box.
     * @return Height in NDC units
     */
    double height() const { return y2 - y1; }
};

/**
 * @brief Layout options for arranging statistics boxes.
 */
enum class StatsLayout {
    Stack,       ///< Stack boxes vertically
    Grid,        ///< Arrange boxes in a grid
    Horizontal,  ///< Arrange boxes horizontally
    Fixed        ///< Keep original positions
};

/**
 * @brief Move the statistics boxes to the specified layout.
 *
 * This function updates the position of the statistics boxes according to the specified layout.
 *
 * @param boxes A reference to TObjArray that contains the stats boxes.
 * @param layout The layout style to apply (defaults to Stack).
 * @param numColumns Number of columns for Grid layout (defaults to 2).
 * @param spacing Spacing between boxes as fraction of canvas (defaults to 0.01).
 * @param startPosition Starting position for first box (defaults to upper right).
 * @throws std::invalid_argument If boxes array is empty or contains invalid objects.
 */
inline auto update_stats_layout(
    const TObjArray& boxes,
    StatsLayout layout = StatsLayout::Stack,
    int numColumns = 2,
    double spacing = 0.01,
    const Position& startPosition = Position(0.65, 0.6, 0.95, 0.9)) -> void {
    if (boxes.GetEntries() <= 0) throw std::invalid_argument("Stats boxes array is empty");
    if (numColumns < 1) throw std::invalid_argument("Number of columns must be positive");

    std::vector<TPaveStats*> statBoxes;
    std::vector<Position> originalPositions;

    for (int i = 0; i < boxes.GetEntries(); i++) {
        auto statBox = dynamic_cast<TPaveStats*>(boxes.At(i));
        if (!statBox) continue;
        originalPositions.emplace_back(statBox->GetX1NDC(), statBox->GetY1NDC(), statBox->GetX2NDC(), statBox->GetY2NDC());
        statBoxes.push_back(statBox);
    }

    if (statBoxes.empty()) throw std::invalid_argument("No valid stats boxes found");

    const double boxWidth = originalPositions[0].width();
    const double boxHeight = originalPositions[0].height();

    switch (layout) {
        case StatsLayout::Fixed:
            // Do nothing, keep original positions
            break;

        case StatsLayout::Stack: {
            // Stack boxes vertically starting from the top
            double currentY = startPosition.y2;

            for (size_t i = 0; i < statBoxes.size(); i++) {
                statBoxes[i]->SetX1NDC(startPosition.x1);
                statBoxes[i]->SetX2NDC(startPosition.x2);

                const double yBottom = currentY - boxHeight;
                statBoxes[i]->SetY2NDC(currentY);
                statBoxes[i]->SetY1NDC(yBottom);

                currentY = yBottom - spacing;
            }
            break;
        }

        case StatsLayout::Horizontal: {
            // Arrange boxes horizontally
            double currentX = startPosition.x1;

            for (size_t i = 0; i < statBoxes.size(); i++) {
                const double xRight = currentX + boxWidth;

                statBoxes[i]->SetX1NDC(currentX);
                statBoxes[i]->SetX2NDC(xRight);
                statBoxes[i]->SetY1NDC(startPosition.y1);
                statBoxes[i]->SetY2NDC(startPosition.y2);
                currentX = xRight + spacing;
            }
            break;
        }

        case StatsLayout::Grid: {
            // Arrange boxes in a grid pattern
            for (size_t i = 0; i < statBoxes.size(); i++) {
                const int row = i / numColumns;
                const int col = i % numColumns;

                const double x1 = startPosition.x1 + col * (boxWidth + spacing);
                const double x2 = x1 + boxWidth;
                const double y2 = startPosition.y2 - row * (boxHeight + spacing);
                const double y1 = y2 - boxHeight;

                statBoxes[i]->SetX1NDC(x1);
                statBoxes[i]->SetX2NDC(x2);
                statBoxes[i]->SetY1NDC(y1);
                statBoxes[i]->SetY2NDC(y2);
            }
            break;
        }
    }
}

/**
 * @brief Set up and position statistics boxes for histograms on a canvas.
 *
 * This function finds stat boxes for the given histograms, updates their appearance,
 * and arranges them according to the specified layout.
 *
 * @tparam Args Variadic template for multiple histogram pointers.
 * @param canvas Shared pointer to the TCanvas containing the histograms.
 * @param layout Layout style to apply to the stat boxes (defaults to Stack).
 * @param histograms Pack of histogram pointers to process.
 * @throws std::runtime_error If canvas is null.
 */
template <typename... Args>
inline auto set_stat_boxes(
    const std::shared_ptr<TCanvas>& canvas,
    StatsLayout layout,
    Args&&... histograms) -> void {
    if (!canvas) throw std::runtime_error("Canvas pointer is null");

    canvas->Update();
    TObjArray boxes;

    for (const auto& h : {histograms...}) {
        if (!h) continue;

        auto statBox = dynamic_cast<TPaveStats*>(h->GetListOfFunctions()->FindObject("stats"));
        if (!statBox) {
            h->SetStats(true);
            canvas->Update();
            statBox = dynamic_cast<TPaveStats*>(h->GetListOfFunctions()->FindObject("stats"));

            if (!statBox) {
                fmt::print(stderr, "Warning: Could not create stats box for histogram\n");
                continue;
            }
        }

        statBox->SetTextColor(h->GetLineColor());
        statBox->SetBorderSize(1);
        statBox->SetFillColor(0);
        statBox->Draw();

        boxes.Add(statBox);
    }

    if (boxes.GetEntries() > 0) {
        update_stats_layout(boxes, layout);
        canvas->Modified();
    }
}

#include <fmt/core.h>

/**
 * @brief Options for drawing 1D histograms with comprehensive styling controls.
 */
class OptionTH1 {
   public:
    // File and canvas options
    std::string file_name = "";
    bool log_x = false;
    bool log_y = false;

    // Histogram style options
    int16_t color1 = Color::kBlack;
    float alpha_color1 = 0.0;
    int16_t color2 = Color::kBlue;
    float alpha_color2 = 0.0;
    std::string draw_option = "histo";
    std::string opt_stat = "emr";

    // Scaling and range options
    std::pair<double, double> x_range = {};
    std::pair<double, double> y_range = {};
    double scale1 = 0;
    double scale2 = 0;

    // Visual markers
    std::vector<double> cuts = {};
    int cut_color = Color::kRed;
    int cut_width = 2;
    double cut_height_fraction = 0.8;

    // Legend and labeling
    std::string legend1 = "";
    std::string legend2 = "";
    std::string title = "";

    // Axes styling
    std::string x_label = "";
    float x_label_offset = 0.8f;
    float x_label_size = 0.05f;
    std::string y_label = "";
    float y_label_offset = 0.8f;
    float y_label_size = 0.05f;

    // Legend positioning
    double legend_x1 = 0.65;
    double legend_y1 = 0.75;
    double legend_x2 = 0.89;
    double legend_y2 = 0.89;

    // Additional options
    StatsLayout stats_layout = StatsLayout::Stack;
};

/**
 * @brief Draw a single 1D histogram with the specified options.
 *
 * @param h Shared pointer to the histogram to draw.
 * @param path Directory path where the output will be saved.
 * @param args Drawing options.
 * @throws std::invalid_argument If histogram pointer is null.
 */
inline auto draw_hist1D(
    const std::shared_ptr<TH1>& h,
    const std::string& path,
    const OptionTH1& args = {}) -> void {
    if (!h) throw std::invalid_argument("Histogram pointer is null");

    auto canvas = make_canvas();
    std::string file_name = args.file_name.empty() ? h->GetName() : args.file_name;

    // Set up global style
    gStyle->SetOptStat(args.opt_stat.data());

    // Configure and draw histogram
    h->Draw(args.draw_option.data());
    h->SetLineColor(args.color1);
    h->SetFillColorAlpha(args.color1, args.alpha_color1);
    h->GetXaxis()->SetTitle(args.x_label.data());
    h->GetXaxis()->SetTitleOffset(args.x_label_offset);
    h->GetXaxis()->SetTitleSize(args.x_label_size);

    if (!args.y_label.empty()) {
        h->GetYaxis()->SetTitle(args.y_label.data());
        h->GetYaxis()->SetTitleOffset(args.y_label_offset);
        h->GetYaxis()->SetTitleSize(args.y_label_size);
    }

    if (!args.title.empty()) h->SetTitle(args.title.data());
    if (args.x_range.first < args.x_range.second) h->GetXaxis()->SetRangeUser(args.x_range.first, args.x_range.second);
    if (args.y_range.first < args.y_range.second) h->GetYaxis()->SetRangeUser(args.y_range.first, args.y_range.second);
    if (args.scale1 != 0) h->Scale(args.scale1);
    if (args.log_x) canvas->SetLogx();
    if (args.log_y) canvas->SetLogy();

    for (double cut : args.cuts) {
        auto line = std::make_unique<TLine>();
        line->SetLineColor(args.cut_color);
        line->SetLineWidth(args.cut_width);
        line->DrawLine(cut, 0, cut, args.cut_height_fraction * h->GetMaximum());
    }

    if (!args.legend1.empty()) {
        auto legend = std::make_unique<TLegend>(args.legend_x1, args.legend_y1, args.legend_x2, args.legend_y2);
        legend->AddEntry(h.get(), args.legend1.data(), "l");
        legend->Draw();
    }

    if (args.opt_stat != "0") set_stat_boxes(canvas, args.stats_layout, h);

    save_canvas(canvas, path, file_name);
}

/**
 * @brief Draw two 1D histograms on the same canvas with the specified options.
 *
 * @param h1 Shared pointer to the first histogram.
 * @param h2 Shared pointer to the second histogram.
 * @param path Directory path where the output will be saved.
 * @param args Drawing options.
 * @throws std::invalid_argument If either histogram pointer is null.
 */
inline auto draw_hist1D(
    const std::shared_ptr<TH1>& h1,
    const std::shared_ptr<TH1>& h2,
    const std::string& path,
    const OptionTH1& args = {}) -> void {
    if (!h1 || !h2) throw std::invalid_argument("One or both histogram pointers are null");

    auto canvas = make_canvas();
    std::string file_name = args.file_name.empty() ? h1->GetName() : args.file_name;
    auto hStack = std::make_shared<THStack>("hs", "");

    // Set up global style
    gStyle->SetOptStat(args.opt_stat.data());

    // Configure first histogram
    h1->SetLineColor(args.color1);
    h1->SetFillColorAlpha(args.color1, args.alpha_color1);
    if (args.scale1 != 0) h1->Scale(args.scale1);

    // Configure second histogram
    h2->SetLineColor(args.color2);
    h2->SetFillColorAlpha(args.color2, args.alpha_color2);  // Fixed: now using color2
    if (args.scale2 != 0) h2->Scale(args.scale2);

    hStack->Add(h1.get(), "hist");
    hStack->Add(h2.get(), "hist");
    hStack->Draw("nostack");

    hStack->GetXaxis()->SetTitle(args.x_label.data());
    hStack->GetXaxis()->SetTitleOffset(args.x_label_offset);
    hStack->GetXaxis()->SetTitleSize(args.x_label_size);

    if (!args.y_label.empty()) {
        hStack->GetYaxis()->SetTitle(args.y_label.data());
        hStack->GetYaxis()->SetTitleOffset(args.y_label_offset);
        hStack->GetYaxis()->SetTitleSize(args.y_label_size);
    }

    if (!args.title.empty()) hStack->SetTitle(args.title.data());
    if (args.x_range.first < args.x_range.second) hStack->GetXaxis()->SetRangeUser(args.x_range.first, args.x_range.second);
    if (args.y_range.first < args.y_range.second) hStack->GetYaxis()->SetRangeUser(args.y_range.first, args.y_range.second);
    if (args.log_x) canvas->SetLogx();
    if (args.log_y) canvas->SetLogy();

    double max_y = std::max(h1->GetMaximum(), h2->GetMaximum());
    for (double cut : args.cuts) {
        auto line = std::make_unique<TLine>();
        line->SetLineColor(args.cut_color);
        line->SetLineWidth(args.cut_width);
        line->DrawLine(cut, 0, cut, args.cut_height_fraction * max_y);
    }

    if (!args.legend1.empty() || !args.legend2.empty()) {
        auto legend = std::make_unique<TLegend>(args.legend_x1, args.legend_y1, args.legend_x2, args.legend_y2);
        if (!args.legend1.empty()) legend->AddEntry(h1.get(), args.legend1.data(), "l");
        if (!args.legend2.empty()) legend->AddEntry(h2.get(), args.legend2.data(), "l");
        legend->Draw();
    }

    if (args.opt_stat != "0") set_stat_boxes(canvas, args.stats_layout, h1, h2);

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