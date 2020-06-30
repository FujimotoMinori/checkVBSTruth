void setHisto(TH1F* h, int color){
    h->SetLineColor(color);
    h->SetLineWidth(2);
    h->GetYaxis()->SetLabelSize(0.040);
    h->GetYaxis()->SetTitleOffset(1.4);
    h->SetStats(0);
    h->GetXaxis()->SetBinLabel(1, "not matched");
    h->GetXaxis()->SetBinLabel(2, "First jet");
    h->GetXaxis()->SetBinLabel(3, "Second jet");
    h->GetXaxis()->SetBinLabel(4, "Both");
    h->GetXaxis()->SetLabelSize(0.050);
    h->GetXaxis()->SetTitleSize(0.050);
    h->Scale(1/h->GetEntries());
    //h->GetYaxis()->SetRangeUser(0,h->GetBinContent(h->GetMaximumBin())+10000);
    h->GetYaxis()->SetRangeUser(0,1);
}


void drawhistogramstag(){
    string finname = "2LepTest_mc16a_newselection._byeta.root";
    TFile* fin = TFile::Open(finname.c_str(), "READ");

    TH1F *hWZjjflags = (TH1F*)fin->Get("WZjj_llqq_0ptag2pjet_0ptv_SR_matchedflagsSignalJetsRaw");
    TH1F *hWZjjflagsTag = (TH1F*)fin->Get("WZjj_llqq_0ptag2pjet_0ptv_SR_matchedflagsTagJetsRaw");
    TH1F *hZZjjflags = (TH1F*)fin->Get("ZZjj_llqq_0ptag2pjet_0ptv_SR_matchedflagsSignalJetsRaw");
    TH1F *hZZjjflagsTag = (TH1F*)fin->Get("ZZjj_llqq_0ptag2pjet_0ptv_SR_matchedflagsTagJetsRaw");

    setHisto(hWZjjflags,kBlack);
    setHisto(hWZjjflagsTag,kBlack);
    setHisto(hZZjjflags,kBlack);
    setHisto(hZZjjflagsTag,kBlack);

    hWZjjflags->SetTitle("WZjj_SR_SignalJets2"); 
    hWZjjflagsTag->SetTitle("WZjj_SR_TagJets2"); 
    hZZjjflags->SetTitle("ZZjj_SR_SignalJets2"); 
    hZZjjflagsTag->SetTitle("ZZjj_SR_TagJets2"); 

    TCanvas *c1 = new TCanvas("c1", "c1");
    hWZjjflags->Draw("hist text0");
    c1->Print("WZjjSR2.pdf");
    TCanvas *c2 = new TCanvas("c2", "c2");
    hZZjjflags->Draw("hist text0");
    c2->Print("ZZjjSR2.pdf");
    TCanvas *c3 = new TCanvas("c3", "c3");
    hWZjjflagsTag->Draw("hist text0");
    c3->Print("WZjjTagSR2.pdf");
    TCanvas *c4 = new TCanvas("c4", "c4");
    hZZjjflagsTag->Draw("hist text0");
    c4->Print("ZZjjTagSR2.pdf");

    return;

}
