#ifdef __CLING__
#pragma cling optimize(0)
#endif
void p_e()
{
//=========Macro generated from canvas: c1/
//=========  (Wed Apr 30 13:46:10 2025) by ROOT version 6.34.08
   TCanvas *c1 = new TCanvas("c1", "",0,0,800,600);
   c1->SetHighLightColor(2);
   c1->Range(-1.736842,-32.66053,12.73684,239.5105);
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
   hs_stack_1->SetMaximum(206.85);
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
   p_e_stack_1->SetBinContent(113,197);
   p_e_stack_1->SetEntries(197);
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
   p_e_cut_stack_2->SetBinContent(113,197);
   p_e_cut_stack_2->SetEntries(197);
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
