void plotAsimov_simultaneous(TString channel) {

    gSystem->Load("libHiggsAnalysisCombinedLimit.so");

    using namespace std;
    using namespace RooFit;
  
    TString tchannel;

    if (channel=="1") { tchannel="4mu"; }
    if (channel=="2") { tchannel="4e"; }
    if (channel=="3") { tchannel="2e2mu"; }

    TFile::Open("higgsCombine1D_refit_2nd.MultiDimFit.mH125.clean.root");

    RooWorkspace *wpre = gFile->Get("w");
    RooAbsData * data = wpre->data("toy_asimov");

    cout<<"load snap shot"<<endl;
    wpre->loadSnapshot("clean");

    const RooSimultaneous *sim_orig  = dynamic_cast<const RooSimultaneous *>(wpre->pdf("model_s"));
    RooAbsPdf *pdfi_orig  = sim_orig->getPdf("hzz4l_13TeV_"+channel);

    RooProduct* ggh_orig = wpre->function("n_exp_final_binhzz4l_13TeV_"+channel+"_proc_ggH_hzz");
    RooProduct* qqh_orig = wpre->function("n_exp_final_binhzz4l_13TeV_"+channel+"_proc_qqH_hzz");
    RooProduct* wh_orig = wpre->function("n_exp_final_binhzz4l_13TeV_"+channel+"_proc_WH_hzz");
    RooProduct* zh_orig = wpre->function("n_exp_final_binhzz4l_13TeV_"+channel+"_proc_ZH_hzz");
    RooProduct* tth_orig = wpre->function("n_exp_final_binhzz4l_13TeV_"+channel+"_proc_ttH_hzz");

    RooProduct* ggzz_orig = wpre->function("n_exp_binhzz4l_13TeV_"+channel+"_proc_bkg_ggzz");
    RooProduct* qqzz_orig = wpre->function("n_exp_binhzz4l_13TeV_"+channel+"_proc_bkg_qqzz");
    RooProduct* zjets_orig = wpre->function("n_exp_binhzz4l_13TeV_"+channel+"_proc_bkg_zjets");

    double n_trueH_orig = ggh_orig->getVal()+qqh_orig->getVal()+wh_orig->getVal()+zh_orig->getVal()+tth_orig->getVal();
    double n_zz_orig = ggzz_orig->getVal()+qqzz_orig->getVal();
    double n_zjets_orig = zjets_orig->getVal();

    cout<<"load snap shot"<<endl;
    TFile::Open("higgsCombine1D_refit_2nd.MultiDimFit.mH125.root");
    RooWorkspace *w = gFile->Get("w");

    w->loadSnapshot("MultiDimFit");

    const RooSimultaneous *sim  = dynamic_cast<const RooSimultaneous *>(w->pdf("model_s"));
    RooAbsPdf *pdfi  = sim->getPdf("hzz4l_13TeV_"+channel);
    //pdf_binhzz4l_13TeV_4mu

    RooProduct* ggh = w->function("n_exp_final_binhzz4l_13TeV_"+channel+"_proc_ggH_hzz");
    RooProduct* qqh = w->function("n_exp_final_binhzz4l_13TeV_"+channel+"_proc_qqH_hzz");
    RooProduct* wh = w->function("n_exp_final_binhzz4l_13TeV_"+channel+"_proc_WH_hzz");
    RooProduct* zh = w->function("n_exp_final_binhzz4l_13TeV_"+channel+"_proc_ZH_hzz");
    RooProduct* tth = w->function("n_exp_final_binhzz4l_13TeV_"+channel+"_proc_ttH_hzz");
    
    RooProduct* ggzz = w->function("n_exp_binhzz4l_13TeV_"+channel+"_proc_bkg_ggzz");
    RooProduct* qqzz = w->function("n_exp_binhzz4l_13TeV_"+channel+"_proc_bkg_qqzz");
    RooProduct* zjets = w->function("n_exp_binhzz4l_13TeV_"+channel+"_proc_bkg_zjets");

    double n_trueH = ggh->getVal()+qqh->getVal()+wh->getVal()+zh->getVal()+tth->getVal();

    double n_zz = ggzz->getVal()+qqzz->getVal();
    double n_zjets = zjets->getVal();

    RooRealVar* CMS_zz4l_mass = w->var("CMS_zz4l_mass");
    RooCategory* CMS_channel = w->cat("CMS_channel");
    RooPlot *mass = w->var("CMS_zz4l_mass")->frame(RooFit::Bins(70));

    data = data->reduce(Cut("CMS_channel==CMS_channel::hzz4l_13TeV_"+channel));
    data->plotOn(mass,RooFit::Cut("CMS_channel==CMS_channel::hzz4l_13TeV_"+channel));

    TString bin = "hzz4l_13TeV_"; bin = bin+channel; 
    pdfi->plotOn(mass, LineColor(kRed),
                       Components("pdf_bin"+bin+"_nuis"), 
                       Slice(*CMS_channel,bin), 
                       ProjWData(*CMS_channel, *data, kTRUE) );


    pdfi->plotOn(mass, LineColor(kMagenta), 
                       Components("shapeBkg_bkg_zjets_"+bin+",shapeBkg_bkg_ggzz_"+bin+",shapeBkg_bkg_qqzz_"+bin), 
                       Slice(*CMS_channel,bin),
                       ProjWData(*CMS_channel, *data, kTRUE) );
    pdfi->plotOn(mass, LineColor(kAzure-3), 
                       Components("shapeBkg_bkg_zjets_"+bin+",shapeBkg_bkg_ggzz_"+bin+",shapeBkg_bkg_qqzz_"+bin), 
                       Slice(*CMS_channel,bin),
                       ProjWData(*CMS_channel, *data, kTRUE) );

    pdfi->plotOn(mass, LineColor(kGreen-3), RooFit::Components("shapeBkg_bkg_zjets_"+bin),
                       Slice(*CMS_channel,bin),
                       ProjWData(*CMS_channel, *data, kTRUE) );


    pdfi_orig->plotOn(mass, LineColor(kBlack),LineStyle(2),
                       Components("pdf_bin"+bin+"_nuis"),
                       Slice(*CMS_channel,bin),
                       ProjWData(*CMS_channel, *data, kTRUE) );

    pdfi_orig->plotOn(mass, LineColor(kBlack),LineStyle(2),
                       Components("shapeBkg_bkg_zjets_"+bin+",shapeBkg_bkg_ggzz_"+bin+",shapeBkg_bkg_qqzz_"+bin),
                       Slice(*CMS_channel,bin),
                       ProjWData(*CMS_channel, *data, kTRUE) );
    pdfi_orig->plotOn(mass, LineColor(kBlack),LineStyle(2),
                       Components("shapeBkg_bkg_zjets_"+bin+",shapeBkg_bkg_ggzz_"+bin+",shapeBkg_bkg_qqzz_"+bin),
                       Slice(*CMS_channel,bin),
                       ProjWData(*CMS_channel, *data, kTRUE) );

    pdfi_orig->plotOn(mass, LineColor(kBlack),LineStyle(2), 
                       Components("shapeBkg_bkg_zjets_"+bin),
                       Slice(*CMS_channel,bin),
                       ProjWData(*CMS_channel, *data, kTRUE) );

    gStyle->SetOptStat(0);

    TCanvas *c = new TCanvas("c","c",1150,950);
    c->cd();

    TH1D* dummy = new TH1D("","",1,105,140);
    dummy->SetBinContent(1,2);
    dummy->SetFillColor(0); dummy->SetLineColor(0); dummy->SetLineWidth(0); dummy->SetMarkerSize(0); dummy->SetMarkerColor(0); 
    dummy->GetYaxis()->SetTitle("Events / (0.5 GeV)");

    if (channel=="1") dummy->GetXaxis()->SetTitle("m_{4#mu} (GeV)");
    if (channel=="2") dummy->GetXaxis()->SetTitle("m_{4e} (GeV)");
    if (channel=="3") dummy->GetXaxis()->SetTitle("m_{2e2#mu} (GeV)");
    dummy->SetMaximum(0.6);
    if(channel=="4e") dummy->SetMaximum(0.2);
    dummy->SetMinimum(0.0);
    dummy->Draw();

    TH1D* dummy_trueH = new TH1D("dummy_trueH","",1,105,140); dummy_trueH->SetLineColor(kRed);
    TH1D* dummy_zz = new TH1D("dummy_zz","",1,105,140); dummy_zz->SetLineColor(kAzure-3);
    TH1D* dummy_zjets = new TH1D("dummy_zjets","",1,105,140); dummy_zjets->SetLineColor(kGreen-3);

    TLegend *leg = new TLegend(0.7,0.3,0.9,0.7);
    leg->SetBorderSize(0);
    leg->SetFillColor(0);
    leg->AddEntry(dummy_trueH, "trueH","L");
    leg->AddEntry(dummy_zz, "ZZ","L");
    leg->AddEntry(dummy_zjets, "Z+Jets","L");

    leg->Draw("same");

    mass->Draw("same");

    TLatex *latex = new TLatex();
    latex->SetNDC();
    latex->SetTextSize(0.6*c->GetTopMargin());
    latex->SetTextFont(42);
    latex->SetTextAlign(11);
    latex->DrawLatex(0.14, 0.92, "CMS Preliminary");
    latex->SetTextSize(0.6*c->GetTopMargin());
    latex->SetTextFont(42);
    latex->DrawLatex(0.22, 0.85, "Asimov Data");
    latex->SetTextSize(0.4*c->GetTopMargin());
    latex->SetTextFont(42);

    char line [200];

    sprintf(line,"N_{right sig.}^{fit} = %.2f (%.2f)",n_trueH, n_trueH_orig);
    latex->DrawLatex(0.22, 0.70, line);

    sprintf(line,"N_{ZZ}^{fit} = %.2f (%.2f)",n_zz, n_zz_orig);
    latex->DrawLatex(0.22, 0.60, line);
    sprintf(line,"N_{Z+X}^{fit} = %.2f (%.2f)",n_zjets, n_zjets_orig);
    latex->DrawLatex(0.22, 0.50, line);

    latex->SetTextSize(0.035);
    latex->SetTextFont(42);
    latex->SetTextAlign(31);
    latex->DrawLatex(0.87,0.92, "#sqrt{s} = 13 TeV, L=2.7 fb^{-1}");

    c->SaveAs("fitresult_"+bin+"_simultaneous_1Drefit.pdf");
    c->SaveAs("fitresult_"+bin+"_simultaneous_1Drefit.png");

}
