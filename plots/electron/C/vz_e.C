#ifdef __CLING__
#pragma cling optimize(0)
#endif
void vz_e()
{
//=========Macro generated from canvas: c1/
//=========  (Wed Apr 30 11:50:49 2025) by ROOT version 6.34.08
   TCanvas *c1 = new TCanvas("c1", "",0,0,800,600);
   c1->SetHighLightColor(2);
   c1->Range(-37.89474,-0.6631579,27.89474,4.863158);
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
   
   TH1F *hs_stack_5 = new TH1F("hs_stack_5","",200,-30,20);
   hs_stack_5->SetMinimum(0);
   hs_stack_5->SetMaximum(4.2);
   hs_stack_5->SetDirectory(nullptr);
   hs_stack_5->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hs_stack_5->SetLineColor(ci);
   hs_stack_5->SetLineWidth(0);
   hs_stack_5->GetXaxis()->SetTitle("Vz_{e} [cm]");
   hs_stack_5->GetXaxis()->SetLabelFont(42);
   hs_stack_5->GetXaxis()->SetTitleSize(0.05);
   hs_stack_5->GetXaxis()->SetTitleOffset(0.8);
   hs_stack_5->GetXaxis()->SetTitleFont(42);
   hs_stack_5->GetYaxis()->SetLabelFont(42);
   hs_stack_5->GetYaxis()->SetTitleFont(42);
   hs_stack_5->GetZaxis()->SetLabelFont(42);
   hs_stack_5->GetZaxis()->SetTitleOffset(1);
   hs_stack_5->GetZaxis()->SetTitleFont(42);
   hs->SetHistogram(hs_stack_5);
   
   
   TH1D *vz_e_stack_1 = new TH1D("vz_e_stack_1","",200,-30,20);
   vz_e_stack_1->SetBinContent(0,2);
   vz_e_stack_1->SetBinContent(3,2);
   vz_e_stack_1->SetBinContent(5,4);
   vz_e_stack_1->SetBinContent(13,2);
   vz_e_stack_1->SetBinContent(14,2);
   vz_e_stack_1->SetBinContent(26,2);
   vz_e_stack_1->SetBinContent(30,2);
   vz_e_stack_1->SetBinContent(49,2);
   vz_e_stack_1->SetBinContent(61,2);
   vz_e_stack_1->SetBinContent(64,2);
   vz_e_stack_1->SetBinContent(67,2);
   vz_e_stack_1->SetBinContent(76,2);
   vz_e_stack_1->SetBinContent(78,2);
   vz_e_stack_1->SetBinContent(80,4);
   vz_e_stack_1->SetBinContent(86,2);
   vz_e_stack_1->SetBinContent(88,2);
   vz_e_stack_1->SetBinContent(91,2);
   vz_e_stack_1->SetBinContent(95,4);
   vz_e_stack_1->SetBinContent(100,4);
   vz_e_stack_1->SetBinContent(107,2);
   vz_e_stack_1->SetBinContent(108,2);
   vz_e_stack_1->SetBinContent(111,2);
   vz_e_stack_1->SetBinContent(114,2);
   vz_e_stack_1->SetBinContent(118,2);
   vz_e_stack_1->SetBinContent(122,2);
   vz_e_stack_1->SetBinContent(123,2);
   vz_e_stack_1->SetBinContent(125,2);
   vz_e_stack_1->SetBinContent(130,2);
   vz_e_stack_1->SetBinContent(133,2);
   vz_e_stack_1->SetBinContent(139,2);
   vz_e_stack_1->SetBinContent(141,2);
   vz_e_stack_1->SetBinContent(142,2);
   vz_e_stack_1->SetBinContent(149,2);
   vz_e_stack_1->SetBinContent(154,2);
   vz_e_stack_1->SetBinContent(155,2);
   vz_e_stack_1->SetBinContent(157,2);
   vz_e_stack_1->SetBinContent(172,2);
   vz_e_stack_1->SetBinContent(177,2);
   vz_e_stack_1->SetBinContent(183,2);
   vz_e_stack_1->SetBinContent(184,2);
   vz_e_stack_1->SetBinContent(187,4);
   vz_e_stack_1->SetBinContent(201,14);
   vz_e_stack_1->SetEntries(106);
   vz_e_stack_1->SetDirectory(nullptr);

   ci = 1195;
   color = new TColor(ci, 0.07058824, 0.07843138, 0.08235294, " ", 0);
   vz_e_stack_1->SetFillColor(ci);

   ci = TColor::GetColor("#121415");
   vz_e_stack_1->SetLineColor(ci);
   vz_e_stack_1->GetXaxis()->SetRange(1,200);
   vz_e_stack_1->GetXaxis()->SetLabelFont(42);
   vz_e_stack_1->GetXaxis()->SetTitleOffset(1);
   vz_e_stack_1->GetXaxis()->SetTitleFont(42);
   vz_e_stack_1->GetYaxis()->SetLabelFont(42);
   vz_e_stack_1->GetYaxis()->SetTitleFont(42);
   vz_e_stack_1->GetZaxis()->SetLabelFont(42);
   vz_e_stack_1->GetZaxis()->SetTitleOffset(1);
   vz_e_stack_1->GetZaxis()->SetTitleFont(42);
   hs->Add(vz_e_stack_1,"hist");
   
   TH1D *vz_e_cut_stack_2 = new TH1D("vz_e_cut_stack_2","",200,-30,20);
   vz_e_cut_stack_2->SetBinContent(3,2);
   vz_e_cut_stack_2->SetBinContent(5,2);
   vz_e_cut_stack_2->SetBinContent(14,2);
   vz_e_cut_stack_2->SetBinContent(26,2);
   vz_e_cut_stack_2->SetBinContent(49,2);
   vz_e_cut_stack_2->SetBinContent(61,2);
   vz_e_cut_stack_2->SetBinContent(64,2);
   vz_e_cut_stack_2->SetBinContent(67,2);
   vz_e_cut_stack_2->SetBinContent(78,2);
   vz_e_cut_stack_2->SetBinContent(80,2);
   vz_e_cut_stack_2->SetBinContent(86,2);
   vz_e_cut_stack_2->SetBinContent(88,2);
   vz_e_cut_stack_2->SetBinContent(91,2);
   vz_e_cut_stack_2->SetBinContent(95,4);
   vz_e_cut_stack_2->SetBinContent(100,4);
   vz_e_cut_stack_2->SetBinContent(107,2);
   vz_e_cut_stack_2->SetBinContent(108,2);
   vz_e_cut_stack_2->SetBinContent(111,2);
   vz_e_cut_stack_2->SetBinContent(114,2);
   vz_e_cut_stack_2->SetBinContent(118,2);
   vz_e_cut_stack_2->SetBinContent(122,2);
   vz_e_cut_stack_2->SetBinContent(123,2);
   vz_e_cut_stack_2->SetBinContent(130,2);
   vz_e_cut_stack_2->SetBinContent(133,2);
   vz_e_cut_stack_2->SetBinContent(141,2);
   vz_e_cut_stack_2->SetBinContent(149,2);
   vz_e_cut_stack_2->SetBinContent(154,2);
   vz_e_cut_stack_2->SetBinContent(155,2);
   vz_e_cut_stack_2->SetBinContent(157,2);
   vz_e_cut_stack_2->SetBinContent(172,2);
   vz_e_cut_stack_2->SetBinContent(177,2);
   vz_e_cut_stack_2->SetBinContent(183,2);
   vz_e_cut_stack_2->SetBinContent(187,4);
   vz_e_cut_stack_2->SetBinContent(201,8);
   vz_e_cut_stack_2->SetEntries(80);
   vz_e_cut_stack_2->SetDirectory(nullptr);

   ci = 1195;
   color = new TColor(ci, 0.07058824, 0.07843138, 0.08235294, " ", 0);
   vz_e_cut_stack_2->SetFillColor(ci);

   ci = TColor::GetColor("#0c5da5");
   vz_e_cut_stack_2->SetLineColor(ci);
   vz_e_cut_stack_2->GetXaxis()->SetRange(1,200);
   vz_e_cut_stack_2->GetXaxis()->SetLabelFont(42);
   vz_e_cut_stack_2->GetXaxis()->SetTitleOffset(1);
   vz_e_cut_stack_2->GetXaxis()->SetTitleFont(42);
   vz_e_cut_stack_2->GetYaxis()->SetLabelFont(42);
   vz_e_cut_stack_2->GetYaxis()->SetTitleFont(42);
   vz_e_cut_stack_2->GetZaxis()->SetLabelFont(42);
   vz_e_cut_stack_2->GetZaxis()->SetTitleOffset(1);
   vz_e_cut_stack_2->GetZaxis()->SetTitleFont(42);
   hs->Add(vz_e_cut_stack_2,"hist");
   hs->Draw("nostack");
   TLine *line = new TLine(-15,0,-15,3.2);

   ci = TColor::GetColor("#ff2c00");
   line->SetLineColor(ci);
   line->SetLineWidth(2);
   line->Draw();
   line = new TLine(5,0,5,3.2);

   ci = TColor::GetColor("#ff2c00");
   line->SetLineColor(ci);
   line->SetLineWidth(2);
   line->Draw();
   c1->Modified();
   c1->SetSelected(c1);
}
