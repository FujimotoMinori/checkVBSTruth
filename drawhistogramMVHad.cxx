void setHisto(TH1F* h, int color){
    h->SetLineColor(color);
    h->SetLineWidth(2);
    h->GetYaxis()->SetLabelSize(0.040);
    h->GetYaxis()->SetTitleOffset(1.4);
    h->SetStats(0);
    h->GetXaxis()->SetLabelSize(0.040);
    h->GetXaxis()->SetTitleSize(0.040);
    h->GetXaxis()->SetTitle("MVHadRes");
}


void drawhistogramMVHad(){
    string finname = "2LepTest_mc16a_bugfixed.root";
    TFile* fin = TFile::Open(finname.c_str(), "READ");

    TH1F *hWZjjMVHadRes0 = (TH1F*)fin->Get("WZjj_llqq_0ptag2pjet_0ptv_SR_MVHadResflag0");
    TH1F *hWZjjMVHadRes1 = (TH1F*)fin->Get("WZjj_llqq_0ptag2pjet_0ptv_SR_MVHadResflag1");
    TH1F *hWZjjMVHadRes2 = (TH1F*)fin->Get("WZjj_llqq_0ptag2pjet_0ptv_SR_MVHadResflag2");
    TH1F *hWZjjMVHadRes3 = (TH1F*)fin->Get("WZjj_llqq_0ptag2pjet_0ptv_SR_MVHadResflag3");
    TH1F *hZZjjMVHadRes0 = (TH1F*)fin->Get("ZZjj_llqq_0ptag2pjet_0ptv_SR_MVHadResflag0");
    TH1F *hZZjjMVHadRes1 = (TH1F*)fin->Get("ZZjj_llqq_0ptag2pjet_0ptv_SR_MVHadResflag1");
    TH1F *hZZjjMVHadRes2 = (TH1F*)fin->Get("ZZjj_llqq_0ptag2pjet_0ptv_SR_MVHadResflag2");
    TH1F *hZZjjMVHadRes3 = (TH1F*)fin->Get("ZZjj_llqq_0ptag2pjet_0ptv_SR_MVHadResflag3");

    setHisto(hWZjjMVHadRes0,kBlack);
    setHisto(hWZjjMVHadRes1,kBlack);
    setHisto(hWZjjMVHadRes2,kBlack);
    setHisto(hWZjjMVHadRes3,kBlack);
    setHisto(hZZjjMVHadRes0,kBlack);
    setHisto(hZZjjMVHadRes1,kBlack);
    setHisto(hZZjjMVHadRes2,kBlack);
    setHisto(hZZjjMVHadRes3,kBlack);

    hWZjjMVHadRes0->SetTitle("WZjj_SR_notmatched"); 
    hWZjjMVHadRes1->SetTitle("WZjj_SR_FirstJet"); 
    hWZjjMVHadRes2->SetTitle("WZjj_SR_SecondJet"); 
    hWZjjMVHadRes3->SetTitle("WZjj_SR_Both"); 
    hZZjjMVHadRes0->SetTitle("ZZjj_SR_notmatched"); 
    hZZjjMVHadRes1->SetTitle("ZZjj_SR_FirstJet"); 
    hZZjjMVHadRes2->SetTitle("ZZjj_SR_SecondJet"); 
    hZZjjMVHadRes3->SetTitle("ZZjj_SR_Both"); 

    TCanvas *c1 = new TCanvas("c1", "c1");
    hWZjjMVHadRes0->Draw("hist");
    c1->Print("WZjjnoB.pdf");
    TCanvas *c2 = new TCanvas("c2", "c2");
    hWZjjMVHadRes1->Draw("hist");
    c2->Print("WZjj1B.pdf");
    TCanvas *c3 = new TCanvas("c3", "c3");
    hWZjjMVHadRes2->Draw("hist");
    c3->Print("WZjj2B.pdf");
    TCanvas *c4 = new TCanvas("c4", "c4");
    hWZjjMVHadRes3->Draw("hist");
    c4->Print("WZjj3B.pdf");



    return;

}
