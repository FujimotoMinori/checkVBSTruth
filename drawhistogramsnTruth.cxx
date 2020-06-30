void setHisto(TH1F* h, int color){
    h->SetLineColor(color);
    h->SetLineWidth(2);
    h->GetYaxis()->SetLabelSize(0.040);
    h->GetYaxis()->SetTitleOffset(1.4);
    h->SetStats(0);
    //h->GetXaxis()->SetBinLabel(1, "not matched");
    //h->GetXaxis()->SetBinLabel(2, "First jet");
    //h->GetXaxis()->SetBinLabel(3, "Second jet");
    //h->GetXaxis()->SetBinLabel(4, "Both");
    h->GetXaxis()->SetLabelSize(0.040);
    h->GetXaxis()->SetTitleSize(0.040);
    h->Scale(1/h->GetEntries());
    //h->GetYaxis()->SetRangeUser(0,h->GetBinContent(h->GetMaximumBin())+10000);
    h->GetYaxis()->SetRangeUser(0,1);
    h->GetXaxis()->SetRangeUser(0,3);
    h->GetXaxis()->SetTitle("nVqqTruth");
}


void drawhistogramsnTruth(){
    string finname = "2LepTest_mc16a_checkTruth.root";
    TFile* fin = TFile::Open(finname.c_str(), "READ");

    //TH1F *hWZjjnTruth = (TH1F*)fin->Get("WZjj_llqq_0ptag2pjet_0ptv_SRVBS_nTruthJets");
    //TH1F *hZZjjnTruth = (TH1F*)fin->Get("ZZjj_llqq_0ptag2pjet_0ptv_SRVBS_nTruthJets");
    TH1F *hWZjjnTruth = (TH1F*)fin->Get("WZjj_llqq_0ptag1pfat0pjet_0ptv_All_nTruthJets");
    TH1F *hZZjjnTruth = (TH1F*)fin->Get("ZZjj_llqq_0ptag1pfat0pjet_0ptv_All_nTruthJets");

    setHisto(hWZjjnTruth,kRed);
    setHisto(hZZjjnTruth,kBlue);

    hWZjjnTruth->SetTitle("ALL_nTruth"); 

    TLegend *leg = new TLegend(0.80,0.80,0.95,0.90);
    leg->AddEntry(hZZjjnTruth,"ZZjj","l");
    leg->AddEntry(hWZjjnTruth,"WZjj","l");
    leg->SetTextSize(0.035);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);

    TCanvas *c1 = new TCanvas("c1", "c1");
    hWZjjnTruth->Draw("hist text0");
    //TCanvas *c2 = new TCanvas("c2", "c2");
    hZZjjnTruth->Draw("hist text0 same");
    leg->Draw();

    return;

}
