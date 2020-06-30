void setHisto(TH1* h, int color){
    h->SetLineColor(color);
    h->SetLineWidth(2);
    h->GetYaxis()->SetLabelSize(0.040);
    h->GetYaxis()->SetTitleOffset(1.45);
    h->SetStats(0);
    //h->GetXaxis()->SetBinLabel(1, "not matched");
    //h->GetXaxis()->SetBinLabel(2, "First jet");
    //h->GetXaxis()->SetBinLabel(3, "Second jet");
    //h->GetXaxis()->SetBinLabel(4, "Both");
    h->GetXaxis()->SetLabelSize(0.040);
    h->GetXaxis()->SetTitleSize(0.040);
    //h->Scale(1/h->GetEntries());
    //h->GetYaxis()->SetRangeUser(0,1);
    h->Rebin(5);
}



void drawHist(){

  string finname = "output.root";
  TFile* f1 = TFile::Open(finname.c_str(), "READ");
  string finname2 = "WZjjoutput.root";
  TFile* f2 = TFile::Open(finname2.c_str(), "READ");

  std::vector<TString> hnames;
  for(auto key : *f1->GetListOfKeys()){
     TString n = key->GetName();
     hnames.push_back(n);
  }
  //hnames.push_back("hflag");

  TCanvas* c; 
  for(auto i : hnames){
     c = new TCanvas(i,i,850,650);
     TH1* t1 = (TH1*)f1->Get(i);    
     TH1* t2 = (TH1*)f2->Get(i);    

     setHisto(t1,kBlue);
     setHisto(t2,kRed);
     t2->Scale(t1->Integral()/t2->Integral());
     TLegend *leg = new TLegend(0.80,0.80,0.95,0.90);
     leg->AddEntry(t1,"ZZjj","l");
     leg->AddEntry(t2,"WZjj","l");
     leg->SetTextSize(0.035);
     leg->SetBorderSize(0);
     leg->SetFillStyle(0);

     c->cd();
     gStyle->SetPaintTextFormat("5.2f");
     t2->Draw("hist ");
     t1->Draw("hist same");
     leg->Draw();
     c->Update();
     c->Print(i+"original.pdf"); 
  }

  return;

}
