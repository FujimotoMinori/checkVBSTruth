void setHisto(TH1* h, int color){
    h->SetLineColor(color);
    h->SetLineWidth(2);
    h->GetYaxis()->SetLabelSize(0.040);
    h->GetYaxis()->SetTitleOffset(1.45);
    h->SetStats(0);
    h->GetXaxis()->SetLabelSize(0.040);
    h->GetXaxis()->SetTitleSize(0.040);
    h->GetXaxis()->SetTitle("costheta");
    //h->Scale(1/h->GetEntries());
    h->GetYaxis()->SetRangeUser(0,6000);
    h->Rebin(2);
}



void drawHist0827(){

  string finname = "../polZZTruth1.root";
  TFile* f1 = TFile::Open(finname.c_str(), "READ");
  string finname2 = "../polZZtTruth1.root";
  TFile* f2 = TFile::Open(finname2.c_str(), "READ");
  string finname3 = "../polZtZtTruth1.root";
  TFile* f3 = TFile::Open(finname3.c_str(), "READ");

  std::vector<TString> hnames;
  //for(auto key : *f1->GetListOfKeys()){
  //   TString n = key->GetName();
  //   hnames.push_back(n);
  //}
  hnames.push_back("hCosThetaStar");
  hnames.push_back("hCosThetaStarLep");

  TCanvas* c; 
  for(auto i : hnames){
     c = new TCanvas(i,i,850,650);
     TH1* t1 = (TH1*)f1->Get(i);    
     TH1* t2 = (TH1*)f2->Get(i);    
     TH1* t3 = (TH1*)f3->Get(i);    

     setHisto(t1,kBlack);
     setHisto(t2,kBlue);
     setHisto(t3,kRed);
     t1->SetTitle(i);
     t2->SetTitle(i);
     t3->SetTitle(i);
     //t2->Scale(t1->Integral()/t2->Integral());
     //t3->Scale(t1->Integral()/t3->Integral());
     TLegend *leg = new TLegend(0.68,0.77,0.93,0.87);
     leg->AddEntry(t1,"(i)   Z_L, Z_L","l");
     leg->AddEntry(t2,"(ii)  Z_T, Z_L","l");
     leg->AddEntry(t3,"(iii) Z_T, Z_T","l");
     leg->SetTextSize(0.035);
     leg->SetBorderSize(0);
     leg->SetFillStyle(0);

     c->cd();
     gStyle->SetPaintTextFormat("5.2f");
     t2->Draw("hist same");
     t1->Draw("hist same");
     t3->Draw("hist same");
     leg->Draw();
     c->Update();
     c->Print(i+".pdf"); 
  }

  return;

}
