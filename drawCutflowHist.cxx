void setHisto(TH1D* h, int color){
    h->SetLineColor(color);
    h->SetLineWidth(2);
    h->GetYaxis()->SetLabelSize(0.035);
    h->GetYaxis()->SetTitleOffset(1.45);
    h->SetStats(0);
    h->GetXaxis()->SetLabelSize(0.035);
    h->GetXaxis()->SetTitleSize(0.035);
}

void drawCutflowHist(){
  std::string finname = "../2LepTest_mc16a_checkTruthOrg.root";
  std::string cutflowDirectoryName = "CutFlow_Dilep/Nominal";
  TFile* f1 = TFile::Open(finname.c_str(), "READ");
  TDirectory *cutflowDirectory = f1->GetDirectory(cutflowDirectoryName.c_str());

  TH1D* histToShow;
  TString hname = "WZjj_CutsSeqMerged";
  cutflowDirectory->GetObject(hname, histToShow);

  TH1D* histToShowTop;
  TString hnameTop = "WZjj_CutsSeqwTopMerged";
  cutflowDirectory->GetObject(hnameTop, histToShowTop);

  TH1D* histToShowZZ;
  TString hnameZZ = "ZZjj_CutsSeqMerged";
  cutflowDirectory->GetObject(hnameZZ, histToShowZZ);

  TH1D* histToShowTopZZ;
  TString hnameTopZZ = "ZZjj_CutsSeqwTopMerged";
  cutflowDirectory->GetObject(hnameTopZZ, histToShowTopZZ);

  TLegend *leg = new TLegend(0.75,0.80,0.95,0.90);
  leg->AddEntry(histToShow,"all","l");
  leg->AddEntry(histToShowTop,"w/ Top","l");
  leg->SetTextSize(0.035);
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);

  TCanvas* c = new TCanvas(hname,hname,850,650);
  setHisto(histToShow,kBlue);
  setHisto(histToShowTop,kRed);
  histToShow->Draw("hist text00");
  histToShowZZ->Draw("hist text00");
  histToShowTop->Draw("hist same text00");
  //histToShowTopZZ->Draw("hist same text00");
  leg->Draw();

  int nBins = histToShow->GetNbinsX();
  std::cout << nBins << std::endl;
  int cutN = 8; //7 in resolved
  TH1D* ratio = new TH1D("ratio","ratio",nBins-cutN,0,nBins-cutN);
  TH1D* ratioZZ = new TH1D("ratioZZ","ratioZZ",nBins-cutN,0,nBins-cutN);
  for(int i = cutN; i < nBins-1; i++){
      float r = 0;
      float rZZ = 0;
      if(histToShow->GetBinContent(i) != 0) {
          r = histToShowTop->GetBinContent(i)/histToShow->GetBinContent(i);
          rZZ = histToShowTopZZ->GetBinContent(i)/histToShowZZ->GetBinContent(i);
      }
      ratio->SetBinContent(i-cutN+1, r);
      ratioZZ->SetBinContent(i-cutN+1, rZZ);
      std::cout << histToShow->GetXaxis()->GetBinLabel(i) << std::endl;
      ratio->GetXaxis()->SetBinLabel(i-cutN+1, histToShow->GetXaxis()->GetBinLabel(i));
      ratioZZ->GetXaxis()->SetBinLabel(i-cutN+1, histToShowZZ->GetXaxis()->GetBinLabel(i));
  }
  TLegend *legZZ = new TLegend(0.75,0.80,0.95,0.90);
  legZZ->AddEntry(ratioZZ,"ZZjj","l");
  legZZ->AddEntry(ratio,"WZjj","l");
  legZZ->SetTextSize(0.035);
  legZZ->SetBorderSize(0);
  legZZ->SetFillStyle(0);
  TCanvas* cr = new TCanvas("ratio","ratio",850,650);
  gStyle->SetPaintTextFormat("5.2f");
  setHisto(ratio,kBlue);
  setHisto(ratioZZ,kBlue);
  ratio->GetYaxis()->SetRangeUser(0.,1.0);
  ratioZZ->GetYaxis()->SetRangeUser(0.,1.0);
  ratio->SetTitle("ratio of events with Top");
  ratio->Draw("hist text00");
  //ratioZZ->Draw("hist same text00");
  //legZZ->Draw();

  return;
}
