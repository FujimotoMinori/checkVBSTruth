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
  //std::string finname = "../2LepTest_mc16a_checkTruthOrg.root";
  //std::string finname = "../2LepTest_mc16a_BvetowTopinfo.root";
  std::string finname = "../2LepTest_mc16a_newBVeto2.root";
  std::string cutflowDirectoryName = "CutFlow_Dilep/Nominal";
  TFile* f1 = TFile::Open(finname.c_str(), "READ");
  TDirectory *cutflowDirectory = f1->GetDirectory(cutflowDirectoryName.c_str());

  TH1D* histToShow;
  TString hname = "WZjj_CutsSeqResolved";
  cutflowDirectory->GetObject(hname, histToShow);

  TH1D* histToShowTop;
  TString hnameTop = "WZjj_CutsSeqwTopResolved";
  cutflowDirectory->GetObject(hnameTop, histToShowTop);

  TH1D* histToShowZZ;
  TString hnameZZ = "ZZjj_CutsSeqResolved";
  cutflowDirectory->GetObject(hnameZZ, histToShowZZ);

  TH1D* histToShowTopZZ;
  TString hnameTopZZ = "ZZjj_CutsSeqwTopResolved";
  cutflowDirectory->GetObject(hnameTopZZ, histToShowTopZZ);

  TLegend *leg = new TLegend(0.75,0.80,0.95,0.90);
  leg->AddEntry(histToShow,"all","l");
  leg->AddEntry(histToShowTop,"w/ Top","l");
  leg->SetTextSize(0.035);
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);

  TCanvas* c = new TCanvas(hname,hname,850,650);
  setHisto(histToShow,kBlue);
  setHisto(histToShowTop,kBlue);
  histToShow->Draw("hist text00");
  //histToShowZZ->Draw("hist text00");
  histToShowTop->Draw("hist same text00");
  //histToShowTopZZ->Draw("hist same text00");
  leg->Draw();

  int nBins = histToShow->GetNbinsX();
  int cutN = 7; //4 in fiducial, 7 in resolved, 8 in merged
  TH1D* ratio = new TH1D("ratio","ratio",nBins-cutN+1,0,nBins-cutN+1);
  TH1D* ratioZZ = new TH1D("ratioZZ","ratioZZ",nBins-cutN+1,0,nBins-cutN+1);
  TH1D* rehisto = new TH1D("CutsSeqResolved","CutsSeqResolved",nBins-cutN+1,0,nBins-cutN+1);
  TH1D* rehistoZZ = new TH1D("CutsSeqResolvedZZ","CutsSeqResolvedZZ",nBins-cutN+1,0,nBins-cutN+1);
  std::cout << nBins << std::endl;
  for(int i = 0; i < nBins+1; i++){ //fiducial +1
      float r = 0;
      float rZZ = 0;
      if(histToShow->GetBinContent(i) != 0) {
          r = histToShowTop->GetBinContent(i)/histToShow->GetBinContent(i);
          rZZ = histToShowTopZZ->GetBinContent(i)/histToShowZZ->GetBinContent(i);
      }
      ratio->SetBinContent(i-cutN+1, r);
      if(i == 18) ratio->SetBinContent(i-cutN+1, histToShowTop->GetBinContent(i)/histToShow->GetBinContent(i+1));
      ratioZZ->SetBinContent(i-cutN+1, rZZ);
      rehisto->SetBinContent(i-cutN+1, histToShow->GetBinContent(i));
      rehistoZZ->SetBinContent(i-cutN+1, histToShowZZ->GetBinContent(i));
      std::cout << "bin number= " << i << std::endl;
      std::cout << "set bin number= " << i-cutN+1 << std::endl;
      std::cout << histToShow->GetXaxis()->GetBinLabel(i) << std::endl;
      ratio->GetXaxis()->SetBinLabel(i-cutN+1, histToShow->GetXaxis()->GetBinLabel(i));
      if(i == 18) ratio->GetXaxis()->SetBinLabel(i-cutN+1, histToShow->GetXaxis()->GetBinLabel(i+1));
      ratioZZ->GetXaxis()->SetBinLabel(i-cutN+1, histToShowZZ->GetXaxis()->GetBinLabel(i));
      rehisto->GetXaxis()->SetBinLabel(i-cutN+1, histToShow->GetXaxis()->GetBinLabel(i));
      //if(i == 18) ratio->GetXaxis()->SetBinLabel(i-cutN+1, "BJetveto");
  }
  setHisto(rehisto,kBlue);
  setHisto(rehistoZZ,kBlue);
  rehisto->GetYaxis()->SetRangeUser(0,800);
  TLegend *legZZ = new TLegend(0.75,0.80,0.95,0.90);
  //legZZ->AddEntry(rehistoZZ,"ZZjj","l");
  legZZ->AddEntry(rehisto,"WZjj","l");
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
  legZZ->Draw();

  TCanvas* re = new TCanvas("CutsSeqResolved","CutsSeqResolved",850,650);
  rehisto->Draw("hist text00");
  //rehistoZZ->Draw("hist same text00");
  legZZ->Draw();

  return;
}

