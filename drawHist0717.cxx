void setHisto(TH1F* h, int color){
    h->SetLineColor(color);
    h->SetLineWidth(2);
    h->GetYaxis()->SetLabelSize(0.040);
    h->GetYaxis()->SetTitleOffset(1.45);
    h->SetStats(0);
    h->GetXaxis()->SetLabelSize(0.040);
    h->GetXaxis()->SetTitleSize(0.040);
    //h->Scale(1/h->GetEntries());
    //h->GetYaxis()->SetRangeUser(0,1);
}

void drawHist0717(){

  string finname = "../2LepTest_mc16a_angle.root";
  TFile* f1 = TFile::Open(finname.c_str(), "READ");

  std::vector<TString> hnames;
  std::vector<TString> hnames2;
  //for(auto key : *f1->GetListOfKeys()){
  //   TString n = key->GetName();
  //   hnames.push_back(n);
  //}
  std::vector<TString> names;
  names.push_back("numberOfTop");
  names.push_back("xiVRes");
  names.push_back("MFullSystem");
  names.push_back("DeltaEtaTagResJets");
  names.push_back("DeltaEtaSignalJets");
  names.push_back("DeltaRSignalJets");
  names.push_back("NBJets");
  names.push_back("MTagResJets");
  names.push_back("MVHadRes");
  names.push_back("WidthSignalJet1");
  names.push_back("WidthTagResJet1");
  names.push_back("mNBjets_sigJ");
  names.push_back("ZeppRes");
  names.push_back("ZeppVRes");
  names.push_back("ZeppZRes");
  names.push_back("ZeppZVRes");
  names.push_back("nVBosons");
  names.push_back("xiVMer");
  names.push_back("Mlljj");
  names.push_back("Phi1");
  names.push_back("Phi2");
  names.push_back("cosTheta");
  names.push_back("cosTheta1");
  names.push_back("cosTheta2");
  for (auto name : names){
      hnames.push_back( "ZZjj_llqq_0ptag2pjet_0ptv_SRVBS_" + name);
      hnames2.push_back( "WZjj_llqq_0ptag2pjet_0ptv_SRVBS_" + name);
  }

  TCanvas* c; 
  int nNames = hnames.size();
  for(int i =0;i < nNames;i++){
     c = new TCanvas(hnames.at(i),hnames.at(i),850,650);
     TH1F* t1 = (TH1F*)f1->Get(hnames.at(i));    
     TH1F* t2 = (TH1F*)f1->Get(hnames2.at(i));    
     t2->Scale(t1->Integral()/t2->Integral());

     setHisto(t1,kBlue);
     setHisto(t2,kRed);
     t1->SetTitle(names.at(i));
     t2->SetTitle(names.at(i));

     TLegend *leg = new TLegend(0.75,0.80,0.90,0.90);
     leg->AddEntry(t1,"ZZjj","l");
     leg->AddEntry(t2,"WZjj","l");
     leg->SetTextSize(0.035);
     leg->SetBorderSize(0);
     leg->SetFillStyle(0);

     c->cd();
     gStyle->SetPaintTextFormat("5.2f");
     if(t1->GetMaximum() > t2->GetMaximum()){
         t1->Draw("hist same");
         t2->Draw("hist same");
     } else {
         t2->Draw("hist same");
         t1->Draw("hist same");
     }
     leg->Draw();
     c->Update();
     c->Print(names.at(i)+".pdf"); 
  }

  return;

}
