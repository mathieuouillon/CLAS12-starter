#ifdef __CLING__
#pragma cling optimize(0)
#endif
void p_e()
{
//=========Macro generated from canvas: c1/
//=========  (Wed Apr 30 11:50:49 2025) by ROOT version 6.34.08
   TCanvas *c1 = new TCanvas("c1", "",0,0,800,600);
   c1->SetHighLightColor(2);
   c1->Range(-1.736842,-1.657895,12.73684,12.15789);
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
   
   TH1F *hs_stack_1 = new TH1F("hs_stack_1","",200,0,11);
   hs_stack_1->SetMinimum(0);
   hs_stack_1->SetMaximum(10.5);
   hs_stack_1->SetDirectory(nullptr);
   hs_stack_1->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hs_stack_1->SetLineColor(ci);
   hs_stack_1->SetLineWidth(0);
   hs_stack_1->GetXaxis()->SetTitle("p_{e} [GeV/c]");
   hs_stack_1->GetXaxis()->SetLabelFont(42);
   hs_stack_1->GetXaxis()->SetTitleSize(0.05);
   hs_stack_1->GetXaxis()->SetTitleOffset(0.8);
   hs_stack_1->GetXaxis()->SetTitleFont(42);
   hs_stack_1->GetYaxis()->SetLabelFont(42);
   hs_stack_1->GetYaxis()->SetTitleFont(42);
   hs_stack_1->GetZaxis()->SetLabelFont(42);
   hs_stack_1->GetZaxis()->SetTitleOffset(1);
   hs_stack_1->GetZaxis()->SetTitleFont(42);
   hs->SetHistogram(hs_stack_1);
   
   
   TH1D *p_e_stack_1 = new TH1D("p_e_stack_1","",200,0,11);
   p_e_stack_1->SetBinContent(20,2);
   p_e_stack_1->SetBinContent(23,2);
   p_e_stack_1->SetBinContent(24,2);
   p_e_stack_1->SetBinContent(27,2);
   p_e_stack_1->SetBinContent(29,2);
   p_e_stack_1->SetBinContent(32,2);
   p_e_stack_1->SetBinContent(34,2);
   p_e_stack_1->SetBinContent(40,2);
   p_e_stack_1->SetBinContent(41,2);
   p_e_stack_1->SetBinContent(44,2);
   p_e_stack_1->SetBinContent(49,2);
   p_e_stack_1->SetBinContent(52,2);
   p_e_stack_1->SetBinContent(63,2);
   p_e_stack_1->SetBinContent(65,4);
   p_e_stack_1->SetBinContent(67,2);
   p_e_stack_1->SetBinContent(68,2);
   p_e_stack_1->SetBinContent(70,2);
   p_e_stack_1->SetBinContent(71,2);
   p_e_stack_1->SetBinContent(74,2);
   p_e_stack_1->SetBinContent(78,2);
   p_e_stack_1->SetBinContent(82,4);
   p_e_stack_1->SetBinContent(88,2);
   p_e_stack_1->SetBinContent(89,2);
   p_e_stack_1->SetBinContent(90,8);
   p_e_stack_1->SetBinContent(93,2);
   p_e_stack_1->SetBinContent(94,2);
   p_e_stack_1->SetBinContent(95,2);
   p_e_stack_1->SetBinContent(111,2);
   p_e_stack_1->SetBinContent(113,2);
   p_e_stack_1->SetBinContent(114,2);
   p_e_stack_1->SetBinContent(116,2);
   p_e_stack_1->SetBinContent(119,2);
   p_e_stack_1->SetBinContent(120,2);
   p_e_stack_1->SetBinContent(122,4);
   p_e_stack_1->SetBinContent(124,2);
   p_e_stack_1->SetBinContent(127,2);
   p_e_stack_1->SetBinContent(128,10);
   p_e_stack_1->SetBinContent(135,2);
   p_e_stack_1->SetBinContent(143,2);
   p_e_stack_1->SetBinContent(144,2);
   p_e_stack_1->SetBinContent(150,2);
   p_e_stack_1->SetBinContent(172,2);
   p_e_stack_1->SetBinContent(176,2);
   p_e_stack_1->SetEntries(106);
   p_e_stack_1->SetDirectory(nullptr);

   ci = 1195;
   color = new TColor(ci, 0.07058824, 0.07843138, 0.08235294, " ", 0);
   p_e_stack_1->SetFillColor(ci);

   ci = TColor::GetColor("#121415");
   p_e_stack_1->SetLineColor(ci);
   p_e_stack_1->GetXaxis()->SetRange(1,200);
   p_e_stack_1->GetXaxis()->SetLabelFont(42);
   p_e_stack_1->GetXaxis()->SetTitleOffset(1);
   p_e_stack_1->GetXaxis()->SetTitleFont(42);
   p_e_stack_1->GetYaxis()->SetLabelFont(42);
   p_e_stack_1->GetYaxis()->SetTitleFont(42);
   p_e_stack_1->GetZaxis()->SetLabelFont(42);
   p_e_stack_1->GetZaxis()->SetTitleOffset(1);
   p_e_stack_1->GetZaxis()->SetTitleFont(42);
   hs->Add(p_e_stack_1,"hist");
   
   TH1D *p_e_cut_stack_2 = new TH1D("p_e_cut_stack_2","",200,0,11);
   p_e_cut_stack_2->SetBinContent(24,2);
   p_e_cut_stack_2->SetBinContent(29,2);
   p_e_cut_stack_2->SetBinContent(34,2);
   p_e_cut_stack_2->SetBinContent(41,2);
   p_e_cut_stack_2->SetBinContent(49,2);
   p_e_cut_stack_2->SetBinContent(63,2);
   p_e_cut_stack_2->SetBinContent(65,4);
   p_e_cut_stack_2->SetBinContent(68,2);
   p_e_cut_stack_2->SetBinContent(71,2);
   p_e_cut_stack_2->SetBinContent(74,2);
   p_e_cut_stack_2->SetBinContent(89,2);
   p_e_cut_stack_2->SetBinContent(90,2);
   p_e_cut_stack_2->SetBinContent(93,2);
   p_e_cut_stack_2->SetBinContent(94,2);
   p_e_cut_stack_2->SetBinContent(95,2);
   p_e_cut_stack_2->SetBinContent(113,2);
   p_e_cut_stack_2->SetBinContent(124,2);
   p_e_cut_stack_2->SetBinContent(128,4);
   p_e_cut_stack_2->SetBinContent(144,2);
   p_e_cut_stack_2->SetEntries(42);
   p_e_cut_stack_2->SetDirectory(nullptr);

   ci = 1195;
   color = new TColor(ci, 0.07058824, 0.07843138, 0.08235294, " ", 0);
   p_e_cut_stack_2->SetFillColor(ci);

   ci = TColor::GetColor("#0c5da5");
   p_e_cut_stack_2->SetLineColor(ci);
   p_e_cut_stack_2->GetXaxis()->SetRange(1,200);
   p_e_cut_stack_2->GetXaxis()->SetLabelFont(42);
   p_e_cut_stack_2->GetXaxis()->SetTitleOffset(1);
   p_e_cut_stack_2->GetXaxis()->SetTitleFont(42);
   p_e_cut_stack_2->GetYaxis()->SetLabelFont(42);
   p_e_cut_stack_2->GetYaxis()->SetTitleFont(42);
   p_e_cut_stack_2->GetZaxis()->SetLabelFont(42);
   p_e_cut_stack_2->GetZaxis()->SetTitleOffset(1);
   p_e_cut_stack_2->GetZaxis()->SetTitleFont(42);
   hs->Add(p_e_cut_stack_2,"hist");
   hs->Draw("nostack");
   c1->Modified();
   c1->SetSelected(c1);
}
