#include <iostream>
#include <sstream>
#include <istream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>
#include <functional>
#include <vector>
#include <cassert>
#include <algorithm>
#include <sstream>

#include "TH1F.h"
#include "TString.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TDirectory.h"
#include "TFile.h"
#include "TLegend.h"
#include "TFrame.h"

using namespace std;


#include "./classes/L1ClassDTBM.C"
#include "./classes/GenClass.C"


int bmtf_reader(){
TString in_file="../test/Tree_from_RAW_200events_locally_cmssw_LUTS_lin.root";

//TString in_file="../test/Tree_SingleMuPt5To140_Eta01_Flat_NoAntiparticle_NonLinear.root";

  L1ClassDTBM l1c;
  GenClass genc;

  TFile *file1 = new TFile(in_file);
  TDirectory * dir = (TDirectory*)file1->Get(in_file+":/L1TProducer");
  TTree *treel1;
  dir->GetObject("L1Tree",treel1);
  l1c.Init(treel1);

    
  TDirectory * gendir = (TDirectory*)file1->Get(in_file+":/GENTProducer");
  TTree *gentreel1;
  gendir->GetObject("GENTree",gentreel1);
  genc.Init(gentreel1);

  
  int nentries = l1c.fChain->GetEntries();

  double PCKtoPHYS[31] = {0.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 6.0, 7.0, 8.0, 10., 12., 14., 16., 18., 20., 25., 30., 35., 40., 45., 50., 60., 70., 80., 90., 100., 120., 140.};

   
cout<<"Analysing tree with: "<<nentries<<" events"<<endl;

 TH2D *emu_old_vs_new_pt;
 emu_old_vs_new_pt = new TH2D("emu_old_vs_new_pt","emu_old_vs_new_pt",30,PCKtoPHYS,280,0,140);
 //emu_old_vs_new_pt = new TH2D("emu_old_vs_new_pt","emu_old_vs_new_pt",30,PCKtoPHYS,30,PCKtoPHYS);

 TH1D *emu_old_vs_new_pt_th1d;
 emu_old_vs_new_pt_th1d = new TH1D("emu_old_vs_new_pt_th1d","emu_old_vs_new_pt_th1d",140,-140,140);

 TH1D *res_new_luts;
 res_new_luts = new TH1D("res_new_luts","res_new_luts",50,-1,1);

 TH1D *res_old_luts;
 res_old_luts = new TH1D("res_old_luts","res_old_luts",50,-1,1);


for(int i=0; i<nentries; i++){

    l1c.GetEntry(i);
    genc.GetEntry(i);


    for(int l=0; l<l1c.trSize; l++){
          int ptpck_old = l1c.trPtPck[l];
	  int ptpck_new = l1c.trmbPtPck[l];
///New linear LUTs
	  emu_old_vs_new_pt->Fill(PCKtoPHYS[ptpck_old-1],ptpck_new/2.);
	  emu_old_vs_new_pt_th1d->Fill(PCKtoPHYS[ptpck_old-1] - ptpck_new/2.);
///New non-linear LUTs
	  //emu_old_vs_new_pt->Fill(PCKtoPHYS[ptpck_old-1],PCKtoPHYS[ptpck_old-1]);
	  //emu_old_vs_new_pt_th1d->Fill(PCKtoPHYS[ptpck_old-1] - PCKtoPHYS[ptpck_old-1]);
			

    }
    int ptpck_new = l1c.trmbPtPck[0];
    int ptpck_old = l1c.trPtPck[0];

    res_new_luts->Fill( ( ptpck_new/2. - genc.genPt_Mu[0] ) / genc.genPt_Mu[0]);
    
    res_old_luts->Fill( ( PCKtoPHYS[ptpck_old-1] - genc.genPt_Mu[0] ) / genc.genPt_Mu[0]);

    //double 
    //cout <<l1c.trSize<<endl;
    
 //   genpt = genc.genPt_Mu[0];
 //  cout<<genc.gen_muons<<endl;

}
 
 

 
 TCanvas *canvas3;
 canvas3= new TCanvas("Canvas 3", "Canvas 3",800,800);
 canvas3->cd();
 gPad->SetTopMargin(0.1);
 gPad->SetBottomMargin(0.14);
 gPad->SetRightMargin(0.15);
 gStyle->SetOptStat(0);

 canvas3->GetFrame()->SetFillColor(21);
 canvas3->GetFrame()->SetBorderSize(12);
 canvas3->SetLogz();
 canvas3->cd();
 emu_old_vs_new_pt->SetTitle("BMTF Emulator");
 emu_old_vs_new_pt->GetYaxis()->SetTitle("BMTF p_{T} (GeV) - New LUTs");
 emu_old_vs_new_pt->GetXaxis()->SetTitle("DTTF p_{T} (GeV) - Old LUTs");
 //emu_old_vs_new_pt->GetYaxis()->SetTitle("BMTF p_{T} (GeV)");
 //emu_old_vs_new_pt->GetYaxis()->SetTitleOffset(1.2);
 //emu_old_vs_new_pt->GetXaxis()->SetTitle("DTTF p_{T} (GeV)");
 emu_old_vs_new_pt->GetYaxis()->SetRangeUser(0,140);
 emu_old_vs_new_pt->GetXaxis()->SetRangeUser(0,140);
 emu_old_vs_new_pt->Draw("COLZ");
 canvas3->SaveAs("c3.png");
 
 
  TCanvas *canvas1;
 canvas1= new TCanvas("Canvas 1", "Canvas 1",800,800);
 canvas1->cd();
 gPad->SetTopMargin(0.1);
 gPad->SetBottomMargin(0.14);
 gPad->SetRightMargin(0.15);
 gStyle->SetOptStat(0);

 canvas1->GetFrame()->SetFillColor(21);
 canvas1->GetFrame()->SetBorderSize(12);
 canvas1->SetLogz();
 canvas1->cd();
 emu_old_vs_new_pt_th1d->SetTitle("BMTF Old - New LUTs");
 emu_old_vs_new_pt_th1d->GetXaxis()->SetTitleOffset(1.5);
 emu_old_vs_new_pt_th1d->GetXaxis()->SetTitle("p_{T}(DTTF - Old LUTs) - p_{T}(BMTF - New LUTs) ");
 emu_old_vs_new_pt_th1d->Draw("");
 canvas1->SaveAs("c1.png");

 
   TCanvas *canvas2;
 canvas2= new TCanvas("Canvas 2", "Canvas 2",800,800);
 canvas2->cd();
 gPad->SetTopMargin(0.1);
 gPad->SetBottomMargin(0.14);
 gPad->SetRightMargin(0.15);
 gStyle->SetOptStat(0);

 canvas2->GetFrame()->SetFillColor(21);
 canvas2->GetFrame()->SetBorderSize(12);
 canvas2->SetLogz();
 canvas2->cd();
 res_new_luts->SetTitle("BMTF Resolution");
 res_new_luts->GetXaxis()->SetTitleOffset(1.5);
 res_new_luts->GetXaxis()->SetTitle("#frac{p_{T}(BMTF - New LUTs) - p_{T}(GEN)}{p_{T}(GEN)} ");
 res_new_luts->Fit("gaus","","",-0.1,0.3);
 gStyle->SetOptFit(1111);
 res_new_luts->Draw("");
 canvas2->SaveAs("c2.png");

 
    TCanvas *canvas4;
 canvas4= new TCanvas("Canvas 4", "Canvas 4",800,800);
 canvas4->cd();
 gPad->SetTopMargin(0.1);
 gPad->SetBottomMargin(0.14);
 gPad->SetRightMargin(0.15);
 gStyle->SetOptStat(0);

 canvas4->GetFrame()->SetFillColor(21);
 canvas4->GetFrame()->SetBorderSize(12);
 canvas4->SetLogz();
 canvas4->cd();
 res_old_luts->SetTitle("DTTF Resolution");
 res_old_luts->GetXaxis()->SetTitleOffset(1.5);
 res_old_luts->GetXaxis()->SetTitle("#frac{p_{T}(DTTF - Old LUTs) - p_{T}(GEN)}{p_{T}(GEN)} ");
 res_old_luts->Fit("gaus","","",-0.2,0.3);
 gStyle->SetOptFit(1111);
 res_old_luts->Draw("");
 canvas4->SaveAs("c4.png");

 res_old_luts->Draw();
return 0;

}


