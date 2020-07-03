void setHisto(TH1F* h, int color, float total){
    h->SetLineColor(color);
    h->SetLineWidth(2);
    h->GetYaxis()->SetLabelSize(0.040);
    h->GetYaxis()->SetTitleOffset(1.45);
    h->SetStats(0);
    h->GetXaxis()->SetLabelSize(0.040);
    h->GetXaxis()->SetTitleSize(0.040);
    //h->Scale(1/total);
    //h->GetYaxis()->SetRangeUser(0,1);
}

void drawHist0702_ratio(){

  string finname = "../2LepTest_mc16a_checkTruth2.root";
  TFile* f1 = TFile::Open(finname.c_str(), "READ");

  std::vector<TString> hnames;
  std::vector<TString> hnames2;
  std::vector<TString> names;
  TString prefix;
  prefix = "_numberOfZ";
  names.push_back("_0ptag1pfat0pjet_0ptv_All");
  names.push_back("_0ptag1pfat0pjet_0ptv_Common");
  names.push_back("_0ptag2pjet_0ptv_ResolvedCommon");
  names.push_back("_0ptag2pjet_0ptv_SR");
  names.push_back("_0ptag2pjet_0ptv_SRVBS");
  for(auto name : names){
      hnames.push_back("ZZjj_llqq"+ name + prefix);
      hnames2.push_back("WZjj_llqq"+ name + prefix);
  }

  TString savefilename = "memo2"+prefix+"_org.txt";
  ofstream savefile;
  savefile.open(savefilename/*.c_str()*/);

  //make graphs
  //TGraph* gZZjj = new TGraph("gZZjj","");

  TCanvas* c; 
  int nNames = hnames.size();
  for(int i =0;i < nNames;i++){
     std::cout << hnames.at(i) << std::endl;
     std::cout << hnames2.at(i) << std::endl;
     c = new TCanvas(hnames.at(i),hnames.at(i),850,650);
     TH1F* t1 = (TH1F*)f1->Get(hnames.at(i));    
     TH1F* t2 = (TH1F*)f1->Get(hnames2.at(i));    

     t1->SetTitle("c"+prefix+names.at(i));
     t2->SetTitle("c"+prefix+names.at(i));
     std::cout << "ratio of 3-bosons ZZjj  " << t1->GetBinContent(4) << std::endl;
     std::cout << "ratio of 3-bosons WZjj  " << t2->GetBinContent(4) << std::endl;
     savefile <<  t1->GetBinContent(4);
     savefile <<  " " << t2->GetBinContent(4) << std::endl;
     int nbins = t1->GetNbinsX();
     float total = 0;
     float total2 = 0;
     for(int j = 0;j < nbins; j++){
         total += t1->GetBinContent(j);
         total2 += t2->GetBinContent(j);
     }
     std::cout << "total= " << total << std::endl;
     std::cout << "total2= " << total2 << std::endl;
     setHisto(t1,kBlue,total);
     setHisto(t2,kRed,total2);

     TLegend *leg = new TLegend(0.80,0.80,0.95,0.90);
     leg->AddEntry(t1,"ZZjj","l");
     leg->AddEntry(t2,"WZjj","l");
     leg->SetTextSize(0.035);
     leg->SetBorderSize(0);
     leg->SetFillStyle(0);

     c->cd();
     gStyle->SetPaintTextFormat("5.2f");
     //t2->Draw("hist text0");
     t1->Draw("hist text0 same");
     t2->Draw("hist text0 same");
     leg->Draw();
     c->Update();
     c->Print("c"+prefix+names.at(i)+"_org.pdf"); 
  }

  savefile.close();
  return;

}
