void setHisto(TH1F* h, int color){
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
    h->Scale(1/h->GetEntries());
    h->GetYaxis()->SetRangeUser(0,1);
}

void drawHist0630Merged(){

  string finname = "ZZjj.root";
  TFile* f1 = TFile::Open(finname.c_str(), "READ");
  string finname2 = "WZjj.root";
  TFile* f2 = TFile::Open(finname2.c_str(), "READ");
  std::string savefilename = "memo_numberOfV_Merged.txt";
  ofstream savefile;
  savefile.open(savefilename.c_str());

  std::vector<TString> hnames;
  //for(auto key : *f1->GetListOfKeys()){
  //   TString n = key->GetName();
  //   hnames.push_back(n);
  //}
  hnames.push_back("ZZjj_llqq_0ptag1pfat0pjet_0ptv_All_numberOfV");
  hnames.push_back("ZZjj_llqq_0ptag1pfat0pjet_0ptv_Common_numberOfV");

  hnames.push_back("ZZjj_llqq_0ptag2pjet_0ptv_MergedCommon_numberOfV");
  hnames.push_back("ZZjj_llqq_0ptag2pjet_0ptv_SR_2Var_numberOfV");
  hnames.push_back("ZZjj_llqq_0ptag2pjet_0ptv_SRVBS_2Var_numberOfV");
  std::vector<TString> hnames2;
  hnames2.push_back("WZjj_llqq_0ptag1pfat0pjet_0ptv_All_numberOfV");
  hnames2.push_back("WZjj_llqq_0ptag1pfat0pjet_0ptv_Common_numberOfV");

  hnames2.push_back("WZjj_llqq_0ptag2pjet_0ptv_MergedCommon_numberOfV");
  hnames2.push_back("WZjj_llqq_0ptag2pjet_0ptv_SR_2Var_numberOfV");
  hnames2.push_back("WZjj_llqq_0ptag2pjet_0ptv_SRVBS_2Var_numberOfV");
  std::vector<TString> names;
  names.push_back("All_numberOfV");
  names.push_back("Common_numberOfV");
  names.push_back("MergedCommon_numberOfV");
  names.push_back("SR_numberOfV");
  names.push_back("SRVBS_numberOfV");

  //make graphs
  //TGraph* gZZjj = new TGraph("gZZjj","");

  TCanvas* c; 
  int nNames = hnames.size();
  for(int i =0;i < nNames;i++){
     std::cout << hnames.at(i) << std::endl;
     std::cout << hnames2.at(i) << std::endl;
     c = new TCanvas(hnames.at(i),hnames.at(i),850,650);
     TH1F* t1 = (TH1F*)f1->Get(hnames.at(i));    
     TH1F* t2 = (TH1F*)f2->Get(hnames2.at(i));    

     setHisto(t1,kBlue);
     setHisto(t2,kRed);
     t1->SetTitle(names.at(i));
     t2->SetTitle(names.at(i));
     std::cout << "ratio of 3-bosons ZZjj  " << t1->GetBinContent(4) << std::endl;
     std::cout << "ratio of 3-bosons WZjj  " << t2->GetBinContent(4) << std::endl;
     savefile <<  t1->GetBinContent(4);
     savefile <<  " " << t2->GetBinContent(4) << std::endl;

     TLegend *leg = new TLegend(0.80,0.80,0.95,0.90);
     leg->AddEntry(t1,"ZZjj","l");
     leg->AddEntry(t2,"WZjj","l");
     leg->SetTextSize(0.035);
     leg->SetBorderSize(0);
     leg->SetFillStyle(0);

     c->cd();
     gStyle->SetPaintTextFormat("5.2f");
     t2->Draw("hist text0");
     t1->Draw("hist text0 same");
     leg->Draw();
     c->Update();
     c->Print(names.at(i)+"_leadpt.pdf"); 
  }

  savefile.close();
  return;

}
