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
    //h->Scale(1/h->GetEntries());
    //h->GetYaxis()->SetRangeUser(0,h->GetBinContent(h->GetMaximumBin())+10000);
    //h->GetYaxis()->SetRangeUser(0,1);
    //h->GetXaxis()->SetRangeUser(0,3);
    h->Rebin(2);
}


void drawhistogramsnTruthMatchJets(){
    string finname = "2LepTest_mc16a_checkTruth.root";
    TFile* fin = TFile::Open(finname.c_str(), "READ");
    std::cout << "opened file" << std::endl;

    TH1F *hWZjjpt = (TH1F*)fin->Get("WZjj_llqq_0ptag2pjet_0ptv_ResolvedCommon_sRVqqTruthJetPt");
    TH1F *hZZjjpt = (TH1F*)fin->Get("ZZjj_llqq_0ptag2pjet_0ptv_ResolvedCommon_sRVqqTruthJetPt");
    TH1F *hWZjj = (TH1F*)fin->Get("WZjj_llqq_0ptag2pjet_0ptv_ResolvedCommon_sRVqqTruthJetEta");
    TH1F *hZZjj = (TH1F*)fin->Get("ZZjj_llqq_0ptag2pjet_0ptv_ResolvedCommon_sRVqqTruthJetEta");

    setHisto(hWZjjpt,kRed);
    setHisto(hZZjjpt,kBlue);
    setHisto(hWZjj,kRed);
    setHisto(hZZjj,kBlue);
    hZZjj->Scale(hWZjj->Integral()/hZZjj->Integral());
    hZZjjpt->Scale(hWZjjpt->Integral()/hZZjjpt->Integral());

    hWZjjpt->SetTitle(""); 
    hZZjjpt->SetTitle(""); 
    hWZjjpt->GetXaxis()->SetTitle("pt [GeV]"); 
    hWZjj->GetXaxis()->SetTitle("eta"); 

    TLegend *leg = new TLegend(0.80,0.80,0.95,0.90);
    leg->AddEntry(hZZjj,"ZZjj","l");
    leg->AddEntry(hWZjj,"WZjj","l");
    leg->SetTextSize(0.035);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);

    TCanvas *c1 = new TCanvas("c1", "c1");
    hWZjj->Draw("hist ");
    hZZjj->Draw("hist same");
    leg->Draw();
    TCanvas *c2 = new TCanvas("c2", "c2");
    hWZjjpt->Draw("hist ");
    hZZjjpt->Draw("hist same");
    leg->Draw();

    return;

}
