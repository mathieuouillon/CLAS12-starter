#ifdef __CLING__
#pragma cling optimize(0)
#endif
void theta_e()
{
//=========Macro generated from canvas: c1/
//=========  (Tue Mar 25 10:52:00 2025) by ROOT version 6.34.04
   TCanvas *c1 = new TCanvas("c1", "",0,0,800,600);
   gStyle->SetOptFit(1);
   c1->SetHighLightColor(2);
   c1->Range(-5.526316,-0.4973684,40.52632,3.647368);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetTickx(1);
   c1->SetTicky(1);
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
   hs_stack_4->SetMaximum(3.15);
   hs_stack_4->SetDirectory(nullptr);
   hs_stack_4->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hs_stack_4->SetLineColor(ci);
   hs_stack_4->SetLineWidth(0);
   hs_stack_4->GetXaxis()->SetTitle("#theta_{e} [deg.]");
   hs_stack_4->GetXaxis()->SetNdivisions(505);
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
   theta_e_stack_1->SetBinContent(32,1);
   theta_e_stack_1->SetBinContent(37,1);
   theta_e_stack_1->SetBinContent(40,1);
   theta_e_stack_1->SetBinContent(41,2);
   theta_e_stack_1->SetBinContent(46,3);
   theta_e_stack_1->SetBinContent(48,1);
   theta_e_stack_1->SetBinContent(49,1);
   theta_e_stack_1->SetBinContent(51,2);
   theta_e_stack_1->SetBinContent(53,3);
   theta_e_stack_1->SetBinContent(54,2);
   theta_e_stack_1->SetBinContent(56,1);
   theta_e_stack_1->SetBinContent(57,2);
   theta_e_stack_1->SetBinContent(59,3);
   theta_e_stack_1->SetBinContent(61,2);
   theta_e_stack_1->SetBinContent(64,1);
   theta_e_stack_1->SetBinContent(65,3);
   theta_e_stack_1->SetBinContent(69,1);
   theta_e_stack_1->SetBinContent(70,2);
   theta_e_stack_1->SetBinContent(72,1);
   theta_e_stack_1->SetBinContent(74,2);
   theta_e_stack_1->SetBinContent(75,1);
   theta_e_stack_1->SetBinContent(78,1);
   theta_e_stack_1->SetBinContent(81,2);
   theta_e_stack_1->SetBinContent(84,1);
   theta_e_stack_1->SetBinContent(89,1);
   theta_e_stack_1->SetBinContent(90,1);
   theta_e_stack_1->SetBinContent(94,1);
   theta_e_stack_1->SetBinContent(97,2);
   theta_e_stack_1->SetBinContent(101,3);
   theta_e_stack_1->SetBinContent(102,1);
   theta_e_stack_1->SetBinContent(105,1);
   theta_e_stack_1->SetBinContent(118,1);
   theta_e_stack_1->SetBinContent(119,1);
   theta_e_stack_1->SetBinContent(135,1);
   theta_e_stack_1->SetBinError(32,1);
   theta_e_stack_1->SetBinError(37,1);
   theta_e_stack_1->SetBinError(40,1);
   theta_e_stack_1->SetBinError(41,1.414214);
   theta_e_stack_1->SetBinError(46,1.732051);
   theta_e_stack_1->SetBinError(48,1);
   theta_e_stack_1->SetBinError(49,1);
   theta_e_stack_1->SetBinError(51,1.414214);
   theta_e_stack_1->SetBinError(53,1.732051);
   theta_e_stack_1->SetBinError(54,1.414214);
   theta_e_stack_1->SetBinError(56,1);
   theta_e_stack_1->SetBinError(57,1.414214);
   theta_e_stack_1->SetBinError(59,1.732051);
   theta_e_stack_1->SetBinError(61,1.414214);
   theta_e_stack_1->SetBinError(64,1);
   theta_e_stack_1->SetBinError(65,1.732051);
   theta_e_stack_1->SetBinError(69,1);
   theta_e_stack_1->SetBinError(70,1.414214);
   theta_e_stack_1->SetBinError(72,1);
   theta_e_stack_1->SetBinError(74,1.414214);
   theta_e_stack_1->SetBinError(75,1);
   theta_e_stack_1->SetBinError(78,1);
   theta_e_stack_1->SetBinError(81,1.414214);
   theta_e_stack_1->SetBinError(84,1);
   theta_e_stack_1->SetBinError(89,1);
   theta_e_stack_1->SetBinError(90,1);
   theta_e_stack_1->SetBinError(94,1);
   theta_e_stack_1->SetBinError(97,1.414214);
   theta_e_stack_1->SetBinError(101,1.732051);
   theta_e_stack_1->SetBinError(102,1);
   theta_e_stack_1->SetBinError(105,1);
   theta_e_stack_1->SetBinError(118,1);
   theta_e_stack_1->SetBinError(119,1);
   theta_e_stack_1->SetBinError(135,1);
   theta_e_stack_1->SetEntries(53);
   theta_e_stack_1->SetDirectory(nullptr);

   ci = 1195;
   color = new TColor(ci, 0.07058824, 0.07843138, 0.08235294, " ", 0);
   theta_e_stack_1->SetFillColor(ci);

   ci = TColor::GetColor("#121415");
   theta_e_stack_1->SetLineColor(ci);
   theta_e_stack_1->GetXaxis()->SetRange(1,200);
   theta_e_stack_1->GetXaxis()->SetNdivisions(505);
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
   theta_e_cut_stack_2->SetBinContent(32,1);
   theta_e_cut_stack_2->SetBinContent(40,1);
   theta_e_cut_stack_2->SetBinContent(41,1);
   theta_e_cut_stack_2->SetBinContent(46,1);
   theta_e_cut_stack_2->SetBinContent(56,1);
   theta_e_cut_stack_2->SetBinContent(57,1);
   theta_e_cut_stack_2->SetBinContent(59,1);
   theta_e_cut_stack_2->SetBinContent(64,1);
   theta_e_cut_stack_2->SetBinContent(65,2);
   theta_e_cut_stack_2->SetBinContent(70,1);
   theta_e_cut_stack_2->SetBinContent(72,1);
   theta_e_cut_stack_2->SetBinContent(74,2);
   theta_e_cut_stack_2->SetBinContent(81,2);
   theta_e_cut_stack_2->SetBinContent(89,1);
   theta_e_cut_stack_2->SetBinContent(94,1);
   theta_e_cut_stack_2->SetBinContent(97,2);
   theta_e_cut_stack_2->SetBinContent(101,3);
   theta_e_cut_stack_2->SetBinContent(119,1);
   theta_e_cut_stack_2->SetBinContent(135,1);
   theta_e_cut_stack_2->SetBinError(32,1);
   theta_e_cut_stack_2->SetBinError(40,1);
   theta_e_cut_stack_2->SetBinError(41,1);
   theta_e_cut_stack_2->SetBinError(46,1);
   theta_e_cut_stack_2->SetBinError(56,1);
   theta_e_cut_stack_2->SetBinError(57,1);
   theta_e_cut_stack_2->SetBinError(59,1);
   theta_e_cut_stack_2->SetBinError(64,1);
   theta_e_cut_stack_2->SetBinError(65,1.414214);
   theta_e_cut_stack_2->SetBinError(70,1);
   theta_e_cut_stack_2->SetBinError(72,1);
   theta_e_cut_stack_2->SetBinError(74,1.414214);
   theta_e_cut_stack_2->SetBinError(81,1.414214);
   theta_e_cut_stack_2->SetBinError(89,1);
   theta_e_cut_stack_2->SetBinError(94,1);
   theta_e_cut_stack_2->SetBinError(97,1.414214);
   theta_e_cut_stack_2->SetBinError(101,1.732051);
   theta_e_cut_stack_2->SetBinError(119,1);
   theta_e_cut_stack_2->SetBinError(135,1);
   theta_e_cut_stack_2->SetEntries(25);
   theta_e_cut_stack_2->SetDirectory(nullptr);

   ci = 1195;
   color = new TColor(ci, 0.07058824, 0.07843138, 0.08235294, " ", 0);
   theta_e_cut_stack_2->SetFillColor(ci);

   ci = TColor::GetColor("#0c5da5");
   theta_e_cut_stack_2->SetLineColor(ci);
   theta_e_cut_stack_2->GetXaxis()->SetRange(1,200);
   theta_e_cut_stack_2->GetXaxis()->SetNdivisions(505);
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
