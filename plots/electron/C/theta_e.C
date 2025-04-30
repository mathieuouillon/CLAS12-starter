#ifdef __CLING__
#pragma cling optimize(0)
#endif
void theta_e()
{
//=========Macro generated from canvas: c1/
//=========  (Wed Apr 30 12:49:02 2025) by ROOT version 6.34.08
   TCanvas *c1 = new TCanvas("c1", "",0,0,800,600);
   c1->SetHighLightColor(2);
   c1->Range(-5.526316,-0.9947368,40.52632,7.294737);
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
   
   TH1F *hs_stack_4 = new TH1F("hs_stack_4","",200,0,35);
   hs_stack_4->SetMinimum(0);
   hs_stack_4->SetMaximum(6.3);
   hs_stack_4->SetDirectory(nullptr);
   hs_stack_4->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hs_stack_4->SetLineColor(ci);
   hs_stack_4->SetLineWidth(0);
   hs_stack_4->GetXaxis()->SetTitle("#theta_{e} [deg.]");
   hs_stack_4->GetXaxis()->SetLabelFont(42);
   hs_stack_4->GetXaxis()->SetTitleSize(0.05);
   hs_stack_4->GetXaxis()->SetTitleOffset(0.8);
   hs_stack_4->GetXaxis()->SetTitleFont(42);
   hs_stack_4->GetYaxis()->SetLabelFont(42);
   hs_stack_4->GetYaxis()->SetTitleFont(42);
   hs_stack_4->GetZaxis()->SetLabelFont(42);
   hs_stack_4->GetZaxis()->SetTitleOffset(1);
   hs_stack_4->GetZaxis()->SetTitleFont(42);
   hs->SetHistogram(hs_stack_4);
   
   
   TH1D *theta_e_stack_1 = new TH1D("theta_e_stack_1","",200,0,35);
   theta_e_stack_1->SetBinContent(32,2);
   theta_e_stack_1->SetBinContent(37,2);
   theta_e_stack_1->SetBinContent(40,2);
   theta_e_stack_1->SetBinContent(41,4);
   theta_e_stack_1->SetBinContent(46,6);
   theta_e_stack_1->SetBinContent(48,2);
   theta_e_stack_1->SetBinContent(49,2);
   theta_e_stack_1->SetBinContent(51,4);
   theta_e_stack_1->SetBinContent(53,6);
   theta_e_stack_1->SetBinContent(54,4);
   theta_e_stack_1->SetBinContent(56,2);
   theta_e_stack_1->SetBinContent(57,4);
   theta_e_stack_1->SetBinContent(59,6);
   theta_e_stack_1->SetBinContent(61,4);
   theta_e_stack_1->SetBinContent(64,2);
   theta_e_stack_1->SetBinContent(65,6);
   theta_e_stack_1->SetBinContent(69,2);
   theta_e_stack_1->SetBinContent(70,4);
   theta_e_stack_1->SetBinContent(72,2);
   theta_e_stack_1->SetBinContent(74,4);
   theta_e_stack_1->SetBinContent(75,2);
   theta_e_stack_1->SetBinContent(78,2);
   theta_e_stack_1->SetBinContent(81,4);
   theta_e_stack_1->SetBinContent(84,2);
   theta_e_stack_1->SetBinContent(89,2);
   theta_e_stack_1->SetBinContent(90,2);
   theta_e_stack_1->SetBinContent(94,2);
   theta_e_stack_1->SetBinContent(97,4);
   theta_e_stack_1->SetBinContent(101,6);
   theta_e_stack_1->SetBinContent(102,2);
   theta_e_stack_1->SetBinContent(105,2);
   theta_e_stack_1->SetBinContent(118,2);
   theta_e_stack_1->SetBinContent(119,2);
   theta_e_stack_1->SetBinContent(135,2);
   theta_e_stack_1->SetEntries(106);
   theta_e_stack_1->SetDirectory(nullptr);

   ci = 1195;
   color = new TColor(ci, 0.07058824, 0.07843138, 0.08235294, " ", 0);
   theta_e_stack_1->SetFillColor(ci);

   ci = TColor::GetColor("#121415");
   theta_e_stack_1->SetLineColor(ci);
   theta_e_stack_1->GetXaxis()->SetRange(1,200);
   theta_e_stack_1->GetXaxis()->SetLabelFont(42);
   theta_e_stack_1->GetXaxis()->SetTitleOffset(1);
   theta_e_stack_1->GetXaxis()->SetTitleFont(42);
   theta_e_stack_1->GetYaxis()->SetLabelFont(42);
   theta_e_stack_1->GetYaxis()->SetTitleFont(42);
   theta_e_stack_1->GetZaxis()->SetLabelFont(42);
   theta_e_stack_1->GetZaxis()->SetTitleOffset(1);
   theta_e_stack_1->GetZaxis()->SetTitleFont(42);
   hs->Add(theta_e_stack_1,"hist");
   
   TH1D *theta_e_cut_stack_2 = new TH1D("theta_e_cut_stack_2","",200,0,35);
   theta_e_cut_stack_2->SetBinContent(32,2);
   theta_e_cut_stack_2->SetBinContent(40,2);
   theta_e_cut_stack_2->SetBinContent(46,2);
   theta_e_cut_stack_2->SetBinContent(57,2);
   theta_e_cut_stack_2->SetBinContent(59,2);
   theta_e_cut_stack_2->SetBinContent(64,2);
   theta_e_cut_stack_2->SetBinContent(65,4);
   theta_e_cut_stack_2->SetBinContent(70,2);
   theta_e_cut_stack_2->SetBinContent(72,2);
   theta_e_cut_stack_2->SetBinContent(74,4);
   theta_e_cut_stack_2->SetBinContent(81,4);
   theta_e_cut_stack_2->SetBinContent(89,2);
   theta_e_cut_stack_2->SetBinContent(94,2);
   theta_e_cut_stack_2->SetBinContent(97,2);
   theta_e_cut_stack_2->SetBinContent(101,6);
   theta_e_cut_stack_2->SetBinContent(135,2);
   theta_e_cut_stack_2->SetEntries(42);
   theta_e_cut_stack_2->SetDirectory(nullptr);

   ci = 1195;
   color = new TColor(ci, 0.07058824, 0.07843138, 0.08235294, " ", 0);
   theta_e_cut_stack_2->SetFillColor(ci);

   ci = TColor::GetColor("#0c5da5");
   theta_e_cut_stack_2->SetLineColor(ci);
   theta_e_cut_stack_2->GetXaxis()->SetRange(1,200);
   theta_e_cut_stack_2->GetXaxis()->SetLabelFont(42);
   theta_e_cut_stack_2->GetXaxis()->SetTitleOffset(1);
   theta_e_cut_stack_2->GetXaxis()->SetTitleFont(42);
   theta_e_cut_stack_2->GetYaxis()->SetLabelFont(42);
   theta_e_cut_stack_2->GetYaxis()->SetTitleFont(42);
   theta_e_cut_stack_2->GetZaxis()->SetLabelFont(42);
   theta_e_cut_stack_2->GetZaxis()->SetTitleOffset(1);
   theta_e_cut_stack_2->GetZaxis()->SetTitleFont(42);
   hs->Add(theta_e_cut_stack_2,"hist");
   hs->Draw("nostack");
   c1->Modified();
   c1->SetSelected(c1);
}
