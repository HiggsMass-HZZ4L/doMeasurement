
#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <map>
#include <utility>
#include <iterator>

#include "TROOT.h"
#include "TFile.h"
#include "TString.h"
#include "TH1.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TLegend.h"
#include "TMultiGraph.h"
#include "THStack.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TMath.h"
#include "TTree.h"
#include "TTreeIndex.h"
#include "TH2F.h"
#include "TLatex.h"
#include "TLine.h"
#include "TGraphAsymmErrors.h"
#include "Math/QuantFuncMathCore.h"

#include "TSystem.h"
#include "TStyle.h"
#include "TPaveText.h"

#include "TPaveLabel.h"
#include "TLegend.h"

#include "TLorentzRotation.h"
#include "TVector3.h"
#include "TLorentzVector.h"
//
#include <vector>
#include <fstream>
//
#include "TRandom3.h"
  
#include "RooRealVar.h"
#include "RooArgSet.h"
#include "RooGaussian.h"
#include "RooBreitWigner.h"
#include "RooProdPdf.h"
#include "RooDataSet.h"
#include "RooGlobalFunc.h"
#include "RooDataHist.h"
#include "RooHistPdf.h"
#include "RooCBShape.h"
#include "RooMinuit.h"
#include "RooFormulaVar.h"
#include "RooAddPdf.h"
#include "RooGenericPdf.h"

#include "RooPlot.h"

// customized PDF
//#include "ZmassConstraintLinkDef.h"
//#include "include/HZZ2L2QRooPdfs.cc"
#include "RooClassFactory.h"
#ifndef __CINT__
#include "MyRooDoubleCBShape.h"
#endif

#include "RooSimultaneous.h"

#include <algorithm>

//#include "loader.C"
using namespace std;

/////////////////////

void setAddresses(TTree* tree);
void ReadTree(TTree* tree, TTree* & newtree);

bool debug_;

TString filename;

// For HRes Reweighting

using namespace RooFit;
using namespace std;

// tree content

  float mass4lErrREFIT, mass4lREFIT;

  float mass4l, mass4lErr, massZ1, massZ2;
  float mass4e, mass4mu, mass2e2mu;
  float GENmassZ1, GENmassZ2;
  
  float dataMCWeight;

  int mH;

  float pTL1, pTL2; 
  int idL1, idL3;  

  ///////

  int fsState;
  double eventMCWeight;

  bool passedTrig;
  bool passedFullSelection; bool passedQCDcut;

  const int ngroups_mm = 6;
  double errranges[ngroups_mm+1];


int main(int argc, char *argv[])
{    
     
  gStyle->SetOptStat(0000);
  //gStyle->SetOptTitle(0);
     
  using namespace std;
     
  if(argc != 3)  {
      cout<<argv[0]<<" filename "<<argv[1]<<" mH "<<argv[2]<<endl;
      return -1;
    }

  gStyle->SetOptStat(0000);
  //gStyle->SetOptTitle(0);
  //gSystem->Load("$CMSSW_BASE/lib/slc5_amd64_gcc462/libHiggsAnalysisCombinedLimit.so");
  //gSystem->Load("$CMSSW_BASE/lib/slc5_amd64_gcc462/pluginUFHZZAnalysis8TeVUFHZZ4LAna.so");

  // control ALL txt format
  debug_ =   true;

  /////////////////////

  TString filename = argv[1];
/*
  TString fs = argv[2];

  if(fs!="2e2mu" && fs!="2e2mu" && fs!="2e2mu+2mu2e" && fs!="4e" && fs!="4mu")
  cout<<"fs has to be 2e2mu, 2mu2e or 2e2mu+2mu2e, 4e, 4mu"<<endl;
*/

  /////////////////////
  TString path = "/scratch/osg/dsperka/Run2/HZZ4l/SubmitArea_13TeV/rootfiles_Run1Fid_20160222/";

  TString mH_TString = argv[2];
  mH = atoi(argv[2]);

  TFile* infile = new TFile(path+filename+".root");

  TTree* tree; 

  if(infile) tree = (TTree*) infile->Get("Ana/passedEvents");
  if(!tree) { cout<<"ERROR could not find the tree for "<<filename<<endl; return -1;}

  // read tree     
  cout<<"start reading tree"<<endl;

  TString name = "mH_"+mH_TString;

  TFile* tmpFile =  new TFile(name+".root","RECREATE");

  setAddresses(tree);
  TTree* newtree = tree->CloneTree(0);

  ReadTree(tree, newtree);

  cout<<"end reading tree"<<endl;

  tmpFile->cd();

  newtree->Write("passedEvents",TObject::kOverwrite);

  tmpFile->Write();

  tmpFile->Close(); 



}



void ReadTree(TTree* tree, TTree* & newtree){
//        newtree->SetBranchAddress("mH",&mH);

        for(int mcfmEvt_HZZ=0; mcfmEvt_HZZ < tree->GetEntries(); mcfmEvt_HZZ++) { //event loop
            tree->GetEntry(mcfmEvt_HZZ);
            if(!(passedFullSelection && passedTrig)) continue;

            TString fstmp = "";
/*
            if(abs(idL1)==11 && abs(idL3)==13) fstmp = "2e2mu";
            if(abs(idL1)==13 && abs(idL3)==11) fstmp = "2mu2e";
            if(abs(idL1)==11 && abs(idL3)==11) fstmp = "4e";
            if(abs(idL1)==13 && abs(idL3)==13) fstmp = "4mu";

            if((fs=="2e2mu+2mu2e" || fs=="2mu2e+2e2mu")){
                if(fstmp!="2e2mu" && fstmp!="2mu2e") continue;
            }
            else{
                if(fs!=fstmp) continue; 
            }
*/

//            if(mass4l>150) continue; 

//            cout<<"fill"<<endl; 

            newtree->Fill();
        }

}


void setAddresses(TTree* tree){

    //tree->SetBranchAddress("Event",&Event);

    tree->SetBranchStatus("*",0);
    tree->SetBranchStatus("passedFullSelection",1);
    tree->SetBranchStatus("passedTrig",1);
    tree->SetBranchStatus("mass4l",1);
    tree->SetBranchStatus("mass4mu",1);
    tree->SetBranchStatus("mass4e",1);
    tree->SetBranchStatus("mass2e2mu",1);
    tree->SetBranchStatus("mass4lErr",1);
    tree->SetBranchStatus("mass4lREFIT",1);
    tree->SetBranchStatus("mass4lErrREFIT",1);
    tree->SetBranchStatus("dataMCWeight",1);
    tree->SetBranchStatus("idL1",1);
    tree->SetBranchStatus("idL3",1);

    tree->SetBranchAddress("passedFullSelection",&passedFullSelection);
    tree->SetBranchAddress("passedTrig",&passedTrig);

    tree->SetBranchAddress("mass4l",&mass4l);
    tree->SetBranchAddress("mass4mu",&mass4mu);
    tree->SetBranchAddress("mass4e",&mass4e);
    tree->SetBranchAddress("mass2e2mu",&mass2e2mu);
    tree->SetBranchAddress("mass4lErr",&mass4lErr);
    tree->SetBranchAddress("idL1",&idL1);
    tree->SetBranchAddress("idL3",&idL3);

    tree->SetBranchAddress("mass4lREFIT",&mass4lREFIT);
    tree->SetBranchAddress("mass4lErrREFIT",&mass4lErrREFIT);

    tree->SetBranchAddress("dataMCWeight",&dataMCWeight);
}

void DeterminRanges(double mH, vector<double> massErr, int nbins, double* ranges){

        vector<double> vmre;
        cout<<"size "<<massErr.size()<<endl;

        for(unsigned int i=0; i<massErr.size(); i++) {
                vmre.push_back(massErr[i]/mH);
        }
        cout<<"sorting"<<endl;
        sort(vmre.begin(), vmre.end());
        ranges[0] = vmre[0];
        cout<<"ranges[0]="<<ranges[0]<<endl;
        for(int i=1; i<nbins; i++){
                ranges[i] = vmre[int(massErr.size()/nbins)*i];
                cout<<"ranges["<<i<<"]="<<ranges[i]<<endl;
        }
        ranges[nbins] = vmre[vmre.size()-1];
        cout<<"ranges["<<nbins<<"]="<<ranges[nbins]<<endl;
}

