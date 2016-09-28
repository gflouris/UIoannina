#include <iostream>
#include "L1TwinMuxTree.h"
#include "Event.h"

#include "TH1F.h"
#include "TH2I.h"

#include "TFile.h"
#include "TDirectory.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TDirectoryFile.h"
#include "TStyle.h"
#include "TString.h"

//#include "setTDRStyle.C"
using namespace std;



TCanvas *canvas_data_mc(TH1F * mc_xs, TH1F * data_xs, TString canvas, bool Logy, double minx, double maxx,double miny, double maxy, TString Labelx,TString RUN){

  TCanvas *data_mc_canvas = new TCanvas("DATA_MC_"+canvas,"DATA_MC_"+canvas,700,700);
  gStyle->SetPadBorderMode(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  TPad *pad1 = new TPad("pad1","This is pad1",0.,0.40,1.,1.);
  TPad *pad2 = new TPad("pad2","This is pad2",0.,0.,1.,0.40);
  pad1->SetFillColor(kWhite);
  pad2->SetFillColor(kWhite);
  pad1->Draw();
  pad2->Draw();

  pad1->cd();
  gPad->SetBottomMargin(0);
  gPad->SetLeftMargin(0.15); gPad->SetRightMargin(0.03);
  gPad->SetTickx();
  if(Logy) gPad->SetLogy();
  data_xs->SetMarkerStyle(20);
  data_xs->SetMarkerColor(1);                                                                                     
  data_xs->SetLineColor(1);
  data_xs->SetMaximum(4000);
  data_xs->SetMinimum(0.5);
  data_xs->SetMarkerSize(0.4);
  mc_xs->SetMarkerSize(0.4);

  mc_xs->SetMarkerColor(kRed);
  mc_xs->SetLineColor(kRed);

  mc_xs->SetMarkerStyle(4);
  data_xs->SetMarkerStyle(2);

  data_xs->GetYaxis()->SetTitle("#Events");

  data_xs->GetYaxis()->SetTitleOffset(1.5);
  data_xs->GetYaxis()->SetTitleOffset(1.5);

  data_xs->Draw("P");
  mc_xs->Draw("same");
  data_xs->Draw("Psame");
  mc_xs->SetAxisRange(-500,500,"X");
  data_xs->SetAxisRange(-500,500,"X");
  data_xs->GetXaxis()->SetRangeUser(minx,maxx);
  data_xs->GetYaxis()->SetRangeUser(miny,maxy);
  mc_xs->GetXaxis()->SetRangeUser(minx,maxx);

  data_xs->GetYaxis()->SetTitleSize(0.045);

   TLegend *leg;
   leg = new TLegend(0.62,0.62,0.95,0.82);
   leg->AddEntry(data_xs,"#font[62]{CMS Internal}", "");
    leg->AddEntry(data_xs,"Run = "+RUN+"", "");
   leg->AddEntry(data_xs,"Data", "p");
   leg->AddEntry(mc_xs ,"Emulator", "p");
   leg->SetTextFont(42);
   leg->SetFillColor(kWhite);
   leg->SetLineColor(kWhite);
   leg->SetBorderSize(0);
   leg->Draw();


   pad2->cd();
                                                                          
     gPad->SetGrid(); gPad->SetTopMargin(0);gPad->SetBottomMargin(0.2);
   gPad->SetLeftMargin(0.15); gPad->SetRightMargin(0.03);
   gPad->SetTickx(); gPad->SetGrid();

   //Ratio
   TH1F *ratio_histo=(TH1F*)data_xs->Clone();
   ratio_histo->SetTitle("Data/Emulator;"+Labelx+";Data/Emulator");
   ratio_histo->Divide(data_xs,mc_xs,1.,1.,"");

   ratio_histo->GetYaxis()->SetLabelSize(0.06);
   ratio_histo->GetYaxis()->SetTitleOffset(0.70);
   ratio_histo->GetYaxis()->SetTitleSize(0.06);

   //ratio_histo->SetMaximum(2.1);
   //ratio_histo->SetMinimum(-0.5);
   ratio_histo->SetMarkerStyle(2);
   ratio_histo->SetMarkerColor(kBlack);
   ratio_histo->SetLineColor(kBlack);
   ratio_histo->GetXaxis()->SetTitleSize(0.055);
   ratio_histo->GetYaxis()->SetTitleSize(0.055);

   ratio_histo->Draw("P");
   ratio_histo->GetXaxis()->SetRangeUser(minx,maxx);
   ratio_histo->GetYaxis()->SetRangeUser(0.02,2.5);

   return data_mc_canvas;

   }


TCanvas *canvas_data_mc_2d(TH2I *h_2d, TString xlabel,TString ylabel, int minx, int maxx, TString RUN, bool TEXT){
 


    TLegend *leg;
    leg = new TLegend(0.15,0.77,0.38,0.87);
  //  leg = new TLegend(0.15,0.77,0.60,0.87);

    leg->AddEntry(h_2d,"#font[62]{CMS Internal}", "");
    leg->AddEntry(h_2d,"Run = "+RUN+"", "");
//    leg->AddEntry(h_2d,"Inputs Masked: Sector=5 Wheel=-2 ", "");
//    leg->AddEntry(h_2d,"Inputs Masked: Sector=11 Wheel=2 ", "");

    leg->SetTextFont(42);
    leg->SetFillColor(kWhite);
    leg->SetLineColor(kWhite);
    leg->SetBorderSize(0);

    TCanvas *canvas = new TCanvas("canvas"+xlabel,"canvas"+xlabel,700,700);
    canvas->cd();

  //gPad->SetBottomMargin(0);
  //gPad->SetLeftMargin(0.15);
   gPad->SetRightMargin(0.15);
	// gPad->SetTickx();



    h_2d->GetYaxis()->SetTitle(ylabel);
    h_2d->GetXaxis()->SetTitle(xlabel);
    h_2d->GetXaxis()->SetRangeUser(minx,maxx);
    h_2d->GetYaxis()->SetRangeUser(minx,maxx);
    if (TEXT) h_2d->Draw("COLZ TEXT");
    else      h_2d->Draw("COLZ");
    leg->Draw();
 	
 	return canvas;
}

void print_event(L1TwinMuxTree* , L1TwinMuxTree* , Event*);

int emu_vs_hw(){

 	//setTDRStyle();
  	//gStyle->SetPalette(1);
  TString RUN = "281614"; 

    TFile* f1 = new TFile("./Ntuples/Ntuple_l1ttwinmux_data_run"+RUN+".root");
//TFile* f1 = new TFile("/afs/cern.ch/work/g/gflouris/TriggerUpgrade/Ntuples/CMSSW_8_0_2/src/UIoannina/TrUpS/test/Ntuples/Ntuple_BMTF_data_Run"+RUN+".root");
    ///L1Tree    
    TDirectory* dirl1 = (TDirectory*)f1->Get("L1TwinMuxProducer");
    TTree* treel1 = (TTree*)dirl1->Get("L1Tree");

    L1TwinMuxTree l1TC;
    l1TC.Init(treel1);

    ///GENTree    
    TDirectory* dirl2 = (TDirectory*)f1->Get("L1TwinMuxProducerEmulator");
    TTree* emu_tree = (TTree*)dirl2->Get("L1Tree");

    L1TwinMuxTree l1TCEmu;
    l1TCEmu.Init(emu_tree);

    ///EventTree    
    TDirectory* direvt = (TDirectory*)f1->Get("EVRTProducer");
    TTree* evt_tree = (TTree*)direvt->Get("EVRTree");
 
    Event evtc;
    evtc.Init(evt_tree);


    int nentries = l1TC.fChain->GetEntries();
    cout<<"Reading L1Tree with:\t"<<nentries<<"\tentries"<<endl;

    int nentriesemu = l1TCEmu.fChain->GetEntries();
    cout<<"Reading L1TreeEmulator with:\t"<<nentriesemu<<"\tentries"<<endl;

    ///Declare a histogram
    TH1F* h1_bx   = new TH1F("h1bx","h1bx",7,-3,3);
    TH1F* h2_bx_emu   = new TH1F("h2bx","h2bx",7,-3,3);


    TH1F* h_phi   = new TH1F("h_phi","h_phi",256,-1024,1024);
    TH1F* h_phi_emu   = new TH1F("h_phi_emu","h_phi_emu",256,-1024,1024);

    TH1F* h_phib   = new TH1F("h_phib","h_phib",512,-1024,1024);
    TH1F* h_phib_emu   = new TH1F("h_phib_emu","h_phib_emu",512,-1024,1024);

    TH1F* h_qual   = new TH1F("h_qual","h_qual",10,0,10);
    TH1F* h_qual_emu   = new TH1F("h_qual_emu","h_qual_emu",10,0,10);


	  TH2I* h_nmu = new TH2I("h_nmu","h_nmu",100,0,100,100,0,100);
	  

//l1TCEmu.GetEntry(1);
       //cout<<l1TCEmu.emubmtfSize<<endl;
 
   int total_data_mu = 0, total_emu_mu = 0;
   int event_diff_num_mu = 0;
   int event_diff_num_mu_emugtdat = 0;
   int events_with_muons = 0;
   int discrep_tradd = 0;

   for(int i=0; i<nentries; i++){
    //for(int i=0; i<500; i++){

       l1TC.GetEntry(i);
       l1TCEmu.GetEntry(i);
       evtc.GetEntry(i);
       //if(l1TC.bmtfSize!=1) continue;     
       //if(l1TCEmu.emubmtfSize!=1) continue;

       int no_p_emu = 0, no_p_dat = 0;

      bool bprint = false;

       for(int tpe=0; tpe<l1TCEmu.tmSize; tpe++){
          //if(l1TCEmu.tmBx[tpe]>1 ||  l1TCEmu.tmBx[tpe]<-1 || l1TCEmu.tmTs2Tag[tpe]!=0) continue;
          //if(l1TCEmu.tmBx[tpe]!=0 || l1TCEmu.tmTs2Tag[tpe]!=0) continue;
          if(l1TCEmu.tmBx[tpe]!=0 || l1TCEmu.tmTs2Tag[tpe]!=0) continue;

          //if(l1TCEmu.tmTs2Tag[tpe]!=0) continue;
          //if(l1TCEmu.tmBx[tpe]==1 && l1TCEmu.tmRpcBit[tpe]==1) bprint = true;
          h2_bx_emu->Fill(l1TCEmu.tmBx[tpe]);
          h_phi_emu->Fill(l1TCEmu.tmAng[tpe]);
          h_phib_emu->Fill(l1TCEmu.tmBandAng[tpe]);
          h_qual_emu->Fill(l1TCEmu.tmCode[tpe]);
          no_p_emu++;
          total_emu_mu++;
       }

       for(int tp=0; tp<l1TC.tmSize; tp++){

          //if(l1TC.tmCode[tp]!=6 ) continue;
          //if(l1TC.tmBx[tp]>1 || l1TC.tmBx[tp]<-1 ) continue;
          if(l1TC.tmBx[tp]!=0) continue;
         // if(l1TC.tmBx[tp]==1 && l1TC.tmRpcBit[tp]==1) bprint = true;

          h1_bx->Fill(l1TC.tmBx[tp]);
          h_phi->Fill(l1TC.tmAng[tp]);
          h_phib->Fill(l1TC.tmBandAng[tp]);
          h_qual->Fill(l1TC.tmCode[tp]);
          no_p_dat++;
          total_data_mu++;

       }


        h_nmu->Fill(no_p_dat,no_p_emu);
        if(no_p_dat!=0)           events_with_muons++;
        if(no_p_dat>no_p_emu ) {
          event_diff_num_mu++;
          //cout<<"======="<<no_p_emu<<"\t"<<no_p_dat<<endl;
         // print_event(&l1TC, &l1TCEmu,  &evtc); 
        }
        if(no_p_dat<no_p_emu ) {
          event_diff_num_mu_emugtdat++;
          //cout<<"======="<<no_p_emu<<"\t"<<no_p_dat<<endl;
          //print_event(&l1TC, &l1TCEmu,  &evtc); 
        }   
  	if(evtc.event==164148100)print_event(&l1TC, &l1TCEmu,  &evtc);
	//if(bprint) print_event(&l1TC, &l1TCEmu,  &evtc);

//if(evtc.event==220656397) print_event(&l1TC, &l1TCEmu,  &evtc);

    }///End loop of nentries


    cout<<"Number of events= "<<nentries<<endl;
    cout<<"Number of data primitives = "<<total_data_mu<<endl;
    cout<<"Number of emul primitives = "<<total_emu_mu<<endl;
    //cout<<"Number of events with muons = "<<events_with_muons<<endl;

    cout<<"\tMismatches\t Mismatches/Total "<<endl;

   	cout<<"n_mu (dat>emu) = "<<event_diff_num_mu<<"\t\t"<<(float)event_diff_num_mu/(float)events_with_muons<<endl;
    cout<<"n_mu (dat<emu) = "<<event_diff_num_mu_emugtdat<<"\t\t"<<(float)event_diff_num_mu_emugtdat/(float)events_with_muons<<endl;


     TCanvas *c1 = canvas_data_mc( h_phi_emu, h_phi, "phi", true, -1024, 1024, 0.8, 20000, "#phi", RUN);
     TCanvas *c2 = canvas_data_mc(  h_phib_emu, h_phib,"phi_b", true, -512, 512, 0.8, 20000, "#phi_{b}", RUN);
     TCanvas *c3 = canvas_data_mc(  h_qual_emu, h_qual,"quality", true, 0, 10, 0.8, 20000000, "Quality", RUN);
     TCanvas *cbx = canvas_data_mc(  h2_bx_emu, h1_bx,"bx", true, -4, 4, 0.8, 2000000, "bx", RUN);
    
    TCanvas *c7 = canvas_data_mc_2d(h_nmu, "Data # primitives","Emulator # primitives", 0,20, RUN, true); c7->SetLogz();



  TString extrLABEL="";

  c1->SaveAs("Plots_Emulator/emu_data_phi_run"+RUN+extrLABEL+"_tmdaq.png");
	c2->SaveAs("Plots_Emulator/emu_data_phib_run"+RUN+"_tmdaq.png");
	c3->SaveAs("Plots_Emulator/emu_data_qual_run"+RUN+extrLABEL+"_tmdaq.png");
	c7->SaveAs("Plots_Emulator/emu_data_nmu_2d_run"+RUN+extrLABEL+"_tmdaq.png");
  cbx->SaveAs("Plots_Emulator/emu_data_bx_run"+RUN+extrLABEL+"_tmdaq.png");
  return 0;
}


void print_event(L1TwinMuxTree* l1TC, L1TwinMuxTree* l1TCEmu, Event* evtc){
  cout<<"Run = "<<evtc->run<<"\t Event = "<<evtc->event<<"\t Lumi = "<<evtc->lumi<<endl;


     cout<<"Inputs: PhiData"<<endl;
     cout<<"bx wh  ts2  st  sect phi_b phi code"<<endl;
     for(int tp=0; tp<l1TC->phSize; tp++){ 
      if(l1TC->phCode[tp]==7) continue;
         cout<<l1TC->phBx[tp]<<"\t"<<l1TC->phWh[tp]<<"\t"<<l1TC->phTs2Tag[tp]<<"\t"<<l1TC->phSt[tp]<<"\t"<<l1TC->phSe[tp]<<"    "<<l1TC->phBandAng[tp]<<"    "<<l1TC->phAng[tp]<<"    "<<l1TC->phCode[tp]<<endl;
      }


     cout<<"Input RPCData"<<endl;
     cout<<"bx wh  st  sect "<<endl;

      for(int r=0; r<l1TC->rpcSize; r++){
         cout<<l1TC->rpcBx[r]<<"\t"<<l1TC->rpcWh[r]<<"\t"<<l1TC->rpcSt[r]<<"\t"<<(l1TC->rpcSe[r]-1)<<"    "<<endl;
      }



     cout<<"Data: PhiData"<<endl;
     cout<<"bx wh  ts2  st  sect phi_b phi code"<<endl;
     for(int tp=0; tp<l1TC->tmSize; tp++){ 
        if(l1TC->tmCode[tp]==7) continue;
         cout<<l1TC->tmBx[tp]<<"\t"<<l1TC->tmWh[tp]<<"\t"<<l1TC->tmTs2Tag[tp]<<"\t"<<l1TC->tmSt[tp]<<"\t"<<l1TC->tmSe[tp]<<"    "<<l1TC->tmBandAng[tp]<<"    "<<l1TC->tmAng[tp]<<"    "<<l1TC->tmCode[tp]<<"    "<<l1TC->tmRpcBit[tp]<<endl;
      }

     cout<<"Emulator: PhiData"<<endl;
     cout<<"bx wh  ts2  st  sect phi_b phi code"<<endl;
     for(int tp=0; tp<l1TCEmu->tmSize; tp++){ 
        if(l1TCEmu->tmCode[tp]==7) continue;
         cout<<l1TCEmu->tmBx[tp]<<"\t"<<l1TCEmu->tmWh[tp]<<"\t"<<l1TCEmu->tmTs2Tag[tp]<<"\t"<<l1TCEmu->tmSt[tp]<<"\t"<<l1TCEmu->tmSe[tp]<<"    "<<l1TCEmu->tmBandAng[tp]<<"    "<<l1TCEmu->tmAng[tp]<<"    "<<l1TCEmu->tmCode[tp]<<"    "<<l1TCEmu->tmRpcBit[tp]<<endl;
      }

    // cout<<"Inputs: EtaData"<<endl;
    // cout<<"bx wh   st  sect hits"<<endl;
    //  for(int tp=0; tp<l1TC->thSize; tp++){ 
    //      cout<<l1TC->thBx[tp]<<"\t"<<l1TC->thWh[tp]<<"\t"<<l1TC->thSt[tp]<<"\t"<<l1TC->thSe[tp]<<"\t"<<l1TC->thTheta[tp]<<"\t"<<l1TC->thCode[tp]<<endl;
    // }

    cout<<endl<<endl;

}
