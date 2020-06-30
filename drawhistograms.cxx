void setHisto(TH1F* h, int color){
    h->SetLineColor(color);
    h->SetLineWidth(2);
    h->GetXaxis()->SetLabelSize(0.040);
    h->GetXaxis()->SetTitleSize(0.040);
    //h->GetXaxis()->SetRangeUser(0,600);
    h->GetYaxis()->SetLabelSize(0.040);
    h->GetYaxis()->SetTitleOffset(1.4);
}


void drawhistograms(){
    string finname = "output.root";
    TFile* fin = TFile::Open(finname.c_str(), "READ");

    TH1F *hQ1Pt = (TH1F*)fin->Get("hQ1Pt");
    TH1F *hQ2Pt = (TH1F*)fin->Get("hQ2Pt");
    TH1F *hQ1PtMatched = (TH1F*)fin->Get("hQ1PtMatched");
    TH1F *hQ2PtMatched = (TH1F*)fin->Get("hQ2PtMatched");
    TH1F *hQ1PtNoMatched = (TH1F*)fin->Get("hQ1PtNoMatched");
    TH1F *hQ2PtNoMatched = (TH1F*)fin->Get("hQ2PtNoMatched");
    TH1F *SigJ1Pt = (TH1F*)fin->Get("SigJ1Pt");
    TH1F *SigJ2Pt = (TH1F*)fin->Get("SigJ2Pt");
    TH1F *hQ1Eta = (TH1F*)fin->Get("hQ1Eta");
    TH1F *hQ2Eta = (TH1F*)fin->Get("hQ2Eta");
    TH1F *SigJ1Eta = (TH1F*)fin->Get("SigJ1Eta");
    TH1F *SigJ2Eta = (TH1F*)fin->Get("SigJ2Eta");
    TH1F *hdRq1 = (TH1F*)fin->Get("hdRq1");
    TH1F *hdRq2 = (TH1F*)fin->Get("hdRq2");
    TH1F *hdRq1Matched = (TH1F*)fin->Get("hdRq1Matched");
    TH1F *hdRq2Matched = (TH1F*)fin->Get("hdRq2Matched");

    //pt
    setHisto(hQ1Pt,kRed);
    setHisto(SigJ1Pt,kBlue);
    setHisto(hQ2Pt,kRed);
    setHisto(SigJ2Pt,kBlue);
    setHisto(hQ1PtNoMatched,kBlack);
    setHisto(hQ2PtNoMatched,kBlack);
    setHisto(hQ1PtMatched,kBlack);
    setHisto(hQ2PtMatched,kBlack);

    //eta
    setHisto(hQ1Eta,kRed);
    setHisto(SigJ1Eta,kBlue);
    setHisto(hQ2Eta,kRed);
    setHisto(SigJ2Eta,kBlue);

    //dRq
    setHisto(hdRq1,kRed);
    setHisto(hdRq1Matched,kBlack);
    setHisto(hdRq2,kRed);
    setHisto(hdRq2Matched,kBlack);

    //draw histograms
    TCanvas *c1 = new TCanvas("c1", "c1");
    hQ1Pt->Draw("hist");
    SigJ1Pt->Draw("hist sames");
    hQ1PtNoMatched->Draw("hist sames");
    TCanvas *c2 = new TCanvas("c2", "c2");
    hQ2Pt->Draw("hist");
    SigJ2Pt->Draw("hist sames");
    hQ2PtNoMatched->Draw("hist sames");
    TCanvas *c3 = new TCanvas("c3", "c3");
    hQ1Eta->Draw("hist");
    SigJ1Eta->Draw("hist sames");
    TCanvas *c4 = new TCanvas("c4", "c4");
    hQ2Eta->Draw("hist");
    SigJ2Eta->Draw("hist sames");

    c1->Update();
    TPaveStats *st1 = (TPaveStats*)hQ1Pt->FindObject("stats");
    st1->SetTextColor(kRed);
    TPaveStats *st2 = (TPaveStats*)SigJ1Pt->FindObject("stats");
    st2->SetTextColor(kBlue);
    c1->Modified();
    c2->Update();
    TPaveStats *st12 = (TPaveStats*)hQ2Pt->FindObject("stats");
    st12->SetTextColor(kRed);
    TPaveStats *st22 = (TPaveStats*)SigJ2Pt->FindObject("stats");
    st22->SetTextColor(kBlue);
    c2->Modified();

    //0621
    //TLegend *leg = new TLegend(0.7,0.75,0.85,0.85);
    //leg->AddEntry(hQ1Pt,"q1 ","l");
    
    //q1
    TCanvas *c = new TCanvas("c", "c");
    hQ1Pt->Draw("hist");
    hQ1PtMatched->Draw("hist sames");
    SigJ1Pt->Draw("hist sames");
    int nbins = hQ1Pt->GetNbinsX();
    TH1F *hratio1 = new TH1F("hratio1","hratio1",nbins,0,1000);
    std::cout << "nbins = " << nbins << std::endl;
    for(int i = 0;i < nbins;i++) {
        if(hQ1PtMatched->GetBinContent(i) != 0) hratio1->SetBinContent(i,hQ1Pt->GetBinContent(i)/hQ1PtMatched->GetBinContent(i));
    }
    std::cout << "now here " << std::endl;
    setHisto(hratio1,kBlack);   
    hratio1->SetTitle("Q1");
    hratio1->GetXaxis()->SetTitle("p_{T,q1} [GeV]");
    hratio1->GetYaxis()->SetTitle("Q1/Q1Matched");
    hratio1->SetStats(0);
    hratio1->GetYaxis()->SetRangeUser(0,5);
    TCanvas *cratio = new TCanvas("cratio", "cratio");
    hratio1->Draw("C");

    //dRq1
    TCanvas *cdRq1 = new TCanvas("cdRq1", "cdRq1");
    //hdRq1->Rebin(5);
    //hdRq1Matched->Rebin(5);
    hdRq1->Draw("hist");
    hdRq1Matched->Draw("hist sames");
    TH1F *hratiodRq1= new TH1F("hratiodRq1","hratiodRq1",700,0,7);
    int nbinsdRq1 = hdRq1->GetNbinsX();
    std::cout << "bins of dR= " << nbinsdRq1 << std::endl;
    for(int i = 0;i < nbinsdRq1;i++) {
        if(hdRq1Matched->GetBinContent(i) != 0) hratiodRq1->SetBinContent(i,hdRq1->GetBinContent(i)/hdRq1Matched->GetBinContent(i));
    }
    setHisto(hratiodRq1,kBlack);   
    hratiodRq1->SetTitle("Q1");
    hratiodRq1->GetXaxis()->SetTitle("dR_{q1}");
    hratiodRq1->GetYaxis()->SetTitle("Q1/Q1Matched");
    hratiodRq1->SetStats(0);
    hratiodRq1->GetYaxis()->SetRangeUser(0,5);
    TCanvas *cratiodRq1 = new TCanvas("cratiodRq1", "cratiodRq1");
    hratiodRq1->Draw();

    //q2
    TCanvas *cq2 = new TCanvas("cq2", "cq2");
    hQ2Pt->Draw("hist");
    hQ2PtMatched->Draw("hist sames");
    SigJ2Pt->Draw("hist sames");
    int nbins2 = hQ2Pt->GetNbinsX();
    TH1F *hratio2 = new TH1F("hratio2","hratio2",nbins2,0,1000);
    for(int i = 0;i < nbins2;i++) {
        if(hQ2PtMatched->GetBinContent(i) != 0) hratio2->SetBinContent(i,hQ2Pt->GetBinContent(i)/hQ2PtMatched->GetBinContent(i));
    }
    std::cout << "now here " << std::endl;
    setHisto(hratio2,kBlack);   
    hratio2->SetTitle("Q2");
    hratio2->GetXaxis()->SetTitle("p_{T,q1} [GeV]");
    hratio2->GetYaxis()->SetTitle("Q2/Q2Matched");
    hratio2->SetStats(0);
    hratio2->GetYaxis()->SetRangeUser(0,5);
    TCanvas *cratio2 = new TCanvas("cratio2", "cratio2");
    hratio2->Draw("C");


    return;

}
