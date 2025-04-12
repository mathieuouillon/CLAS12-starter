#ifdef __CLING__
#pragma cling optimize(0)
#endif
void chi2_e()
{
//=========Macro generated from canvas: c1/
//=========  (Sat Apr 12 15:22:33 2025) by ROOT version 6.32.10
   TCanvas *c1 = new TCanvas("c1", "",0,0,800,600);
   c1->SetHighLightColor(2);
   c1->Range(-7.894737,-0.6631579,7.894737,4.863158);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetLeftMargin(0.12);
   c1->SetRightMargin(0.12);
   c1->SetTopMargin(0.12);
   c1->SetBottomMargin(0.12);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   THStack *hs = new THStack();
   hs->SetName("hs");
   hs->SetTitle("");
   
   TH1F *hs_stack_2 = new TH1F("hs_stack_2","",200,-6,6);
   hs_stack_2->SetMinimum(0);
   hs_stack_2->SetMaximum(4.2);
   hs_stack_2->SetDirectory(nullptr);
   hs_stack_2->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hs_stack_2->SetLineColor(ci);
   hs_stack_2->SetLineWidth(0);
   hs_stack_2->GetXaxis()->SetTitle("chi2pid_{e}");
   hs_stack_2->GetXaxis()->SetLabelFont(42);
   hs_stack_2->GetXaxis()->SetTitleSize(0.05);
   hs_stack_2->GetXaxis()->SetTitleOffset(0.8);
   hs_stack_2->GetXaxis()->SetTitleFont(42);
   hs_stack_2->GetYaxis()->SetLabelFont(42);
   hs_stack_2->GetYaxis()->SetTitleFont(42);
   hs_stack_2->GetZaxis()->SetLabelFont(42);
   hs_stack_2->GetZaxis()->SetTitleOffset(1);
   hs_stack_2->GetZaxis()->SetTitleFont(42);
   hs->SetHistogram(hs_stack_2);
   
   
   TH1D *chi2_e_stack_1 = new TH1D("chi2_e_stack_1","",200,-6,6);
   chi2_e_stack_1->SetBinContent(29,2);
   chi2_e_stack_1->SetBinContent(39,4);
   chi2_e_stack_1->SetBinContent(41,2);
   chi2_e_stack_1->SetBinContent(46,4);
   chi2_e_stack_1->SetBinContent(47,2);
   chi2_e_stack_1->SetBinContent(49,2);
   chi2_e_stack_1->SetBinContent(58,2);
   chi2_e_stack_1->SetBinContent(59,2);
   chi2_e_stack_1->SetBinContent(62,2);
   chi2_e_stack_1->SetBinContent(64,2);
   chi2_e_stack_1->SetBinContent(66,4);
   chi2_e_stack_1->SetBinContent(69,4);
   chi2_e_stack_1->SetBinContent(76,4);
   chi2_e_stack_1->SetBinContent(82,4);
   chi2_e_stack_1->SetBinContent(83,2);
   chi2_e_stack_1->SetBinContent(84,2);
   chi2_e_stack_1->SetBinContent(86,2);
   chi2_e_stack_1->SetBinContent(88,2);
   chi2_e_stack_1->SetBinContent(94,2);
   chi2_e_stack_1->SetBinContent(95,2);
   chi2_e_stack_1->SetBinContent(97,2);
   chi2_e_stack_1->SetBinContent(99,2);
   chi2_e_stack_1->SetBinContent(105,2);
   chi2_e_stack_1->SetBinContent(107,4);
   chi2_e_stack_1->SetBinContent(110,2);
   chi2_e_stack_1->SetBinContent(111,2);
   chi2_e_stack_1->SetBinContent(113,2);
   chi2_e_stack_1->SetBinContent(116,4);
   chi2_e_stack_1->SetBinContent(117,2);
   chi2_e_stack_1->SetBinContent(119,2);
   chi2_e_stack_1->SetBinContent(120,2);
   chi2_e_stack_1->SetBinContent(121,2);
   chi2_e_stack_1->SetBinContent(123,2);
   chi2_e_stack_1->SetBinContent(126,2);
   chi2_e_stack_1->SetBinContent(129,2);
   chi2_e_stack_1->SetBinContent(134,2);
   chi2_e_stack_1->SetBinContent(140,2);
   chi2_e_stack_1->SetBinContent(141,2);
   chi2_e_stack_1->SetBinContent(147,2);
   chi2_e_stack_1->SetBinContent(148,2);
   chi2_e_stack_1->SetBinContent(155,2);
   chi2_e_stack_1->SetBinContent(158,2);
   chi2_e_stack_1->SetBinContent(160,2);
   chi2_e_stack_1->SetBinContent(161,2);
   chi2_e_stack_1->SetBinContent(165,2);
   chi2_e_stack_1->SetEntries(106);
   chi2_e_stack_1->SetDirectory(nullptr);

   ci = 1196;
   color = new TColor(ci, 0.07058824, 0.07843138, 0.08235294, " ", 0);
   chi2_e_stack_1->SetFillColor(ci);

   ci = TColor::GetColor("#121415");
   chi2_e_stack_1->SetLineColor(ci);
   chi2_e_stack_1->GetXaxis()->SetRange(1,200);
   chi2_e_stack_1->GetXaxis()->SetLabelFont(42);
   chi2_e_stack_1->GetXaxis()->SetTitleOffset(1);
   chi2_e_stack_1->GetXaxis()->SetTitleFont(42);
   chi2_e_stack_1->GetYaxis()->SetLabelFont(42);
   chi2_e_stack_1->GetYaxis()->SetTitleFont(42);
   chi2_e_stack_1->GetZaxis()->SetLabelFont(42);
   chi2_e_stack_1->GetZaxis()->SetTitleOffset(1);
   chi2_e_stack_1->GetZaxis()->SetTitleFont(42);
   hs->Add(chi2_e_stack_1,"hist");
   
   TH1D *chi2_e_cut_stack_2 = new TH1D("chi2_e_cut_stack_2","",200,-6,6);
   chi2_e_cut_stack_2->SetBinContent(39,2);
   chi2_e_cut_stack_2->SetBinContent(41,2);
   chi2_e_cut_stack_2->SetBinContent(58,2);
   chi2_e_cut_stack_2->SetBinContent(59,2);
   chi2_e_cut_stack_2->SetBinContent(69,2);
   chi2_e_cut_stack_2->SetBinContent(82,2);
   chi2_e_cut_stack_2->SetBinContent(95,2);
   chi2_e_cut_stack_2->SetBinContent(105,2);
   chi2_e_cut_stack_2->SetBinContent(107,4);
   chi2_e_cut_stack_2->SetBinContent(110,2);
   chi2_e_cut_stack_2->SetBinContent(111,2);
   chi2_e_cut_stack_2->SetBinContent(113,2);
   chi2_e_cut_stack_2->SetBinContent(116,4);
   chi2_e_cut_stack_2->SetBinContent(117,2);
   chi2_e_cut_stack_2->SetBinContent(121,2);
   chi2_e_cut_stack_2->SetBinContent(123,2);
   chi2_e_cut_stack_2->SetBinContent(134,2);
   chi2_e_cut_stack_2->SetBinContent(140,2);
   chi2_e_cut_stack_2->SetBinContent(141,2);
   chi2_e_cut_stack_2->SetBinContent(147,2);
   chi2_e_cut_stack_2->SetBinContent(148,2);
   chi2_e_cut_stack_2->SetBinContent(158,2);
   chi2_e_cut_stack_2->SetBinContent(160,2);
   chi2_e_cut_stack_2->SetEntries(50);
   chi2_e_cut_stack_2->SetDirectory(nullptr);

   ci = 1196;
   color = new TColor(ci, 0.07058824, 0.07843138, 0.08235294, " ", 0);
   chi2_e_cut_stack_2->SetFillColor(ci);

   ci = TColor::GetColor("#0c5da5");
   chi2_e_cut_stack_2->SetLineColor(ci);
   chi2_e_cut_stack_2->GetXaxis()->SetRange(1,200);
   chi2_e_cut_stack_2->GetXaxis()->SetLabelFont(42);
   chi2_e_cut_stack_2->GetXaxis()->SetTitleOffset(1);
   chi2_e_cut_stack_2->GetXaxis()->SetTitleFont(42);
   chi2_e_cut_stack_2->GetYaxis()->SetLabelFont(42);
   chi2_e_cut_stack_2->GetYaxis()->SetTitleFont(42);
   chi2_e_cut_stack_2->GetZaxis()->SetLabelFont(42);
   chi2_e_cut_stack_2->GetZaxis()->SetTitleOffset(1);
   chi2_e_cut_stack_2->GetZaxis()->SetTitleFont(42);
   hs->Add(chi2_e_cut_stack_2,"hist");
   hs->Draw("nostack");
   TLine *line = new TLine(-3,0,-3,3.2);

   ci = TColor::GetColor("#ff2c00");
   line->SetLineColor(ci);
   line->SetLineWidth(2);
   line->Draw();
   line = new TLine(3,0,3,3.2);

   ci = TColor::GetColor("#ff2c00");
   line->SetLineColor(ci);
   line->SetLineWidth(2);
   line->Draw();
   c1->Modified();
   c1->SetSelected(c1);
}
