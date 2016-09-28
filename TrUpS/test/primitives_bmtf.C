#include <iostream>
#include "L1TwinMuxTree.h"
#include "Event.h"
#include "L1BMTF.h"


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

void print_event(L1TwinMuxTree* , Event* );
void print_event(L1TwinMuxTree* l1TC, L1BMTF* l1bmf, Event* evtc);

int primitives_bmtf(){

 	//setTDRStyle();
  	//gStyle->SetPalette(1);
     TString RUN = "280992"; 
    TString LABEL = "";




   TFile* f = new TFile("./Ntuples/Ntuple_l1ttwinmux_data_run"+RUN+".root");
   TDirectory* dirl1 = (TDirectory*)f->Get("L1TwinMuxProducer");
   TTree* l1_tree = (TTree*)dirl1->Get("L1Tree");


   L1TwinMuxTree l1TC;
   l1TC.Init(l1_tree);

   ///EventTree    
    TDirectory* direvt = (TDirectory*)f->Get("EVRTProducer");
    TTree* evt_tree = (TTree*)direvt->Get("EVRTree");
 
    Event evtc;
    evtc.Init(evt_tree);

    ///BMTFTree    
    TDirectory* dirbmtf = (TDirectory*)f->Get("L1TProducer");
    TTree* bmtf_tree = (TTree*)dirbmtf->Get("L1Tree");
 
    L1BMTF bmtfc;
    bmtfc.Init(bmtf_tree);


    int nentries = l1TC.fChain->GetEntries();
    cout<<"Reading L1Tree with:\t"<<nentries<<"\tentries"<<endl;



    //int nentriesemu = l1TCEmu.fChain->GetEntries();
    //cout<<"Reading L1TreeEmulator with:\t"<<nentriesemu<<"\tentries"<<endl;

    ///Declare a histogram
    TH1F* h1_bx   = new TH1F("h1bx","h1bx",12,-6,6);
    TH1F* h2_bx   = new TH1F("h2bx","h2bx",12,-6,6);
    TH1F* h3_bx   = new TH1F("h3_bx","h3_bx",12,-6,6);
    TH1F* h4_bx   = new TH1F("h4_bx","h4_bx",12,-6,6);

    TH1F* hrpc_bx   = new TH1F("hrpc_bx","hrpc_bx",6,-3,3);

    TH1F* h1_bx_in   = new TH1F("h1bx_in","h1bx_in",6,-3,3);

    TH1F* h1_code   = new TH1F("h1_code","h1_code",10,0,10);
    TH1F* h1_quality1   = new TH1F("h1_quality1","h1_quality1",8,0,8);
    TH1F* h1_quality2   = new TH1F("h1_quality22","h1_quality2",8,0,8);

    TH2I *phi_dt_rpc_2d = new TH2I("phi_dt_rpc_2d","phi_dt_rpc_2d",2048,-2048,2048, 2048,-2048,2048);

  TH2I* h_sec_wh_data_1  = new TH2I("h_sec_wh_data_1","h_sec_wh_data_1",12,0,12, 11, -5,5);
  TH2I* h_sec_wh_data_2  = new TH2I("h_sec_wh_data_2","h_sec_wh_data_2",12,0,12, 11, -5,5);
  TH2I* h_sec_wh_data_3  = new TH2I("h_sec_wh_data_3","h_sec_wh_data_3",12,0,12, 11, -5,5);
  TH2I* h_sec_wh_data_4  = new TH2I("h_sec_wh_data_4","h_sec_wh_data_4",12,0,12, 11, -5,5);

  TH2I* h_sec_wh_data_1_rpc  = new TH2I("h_sec_wh_data_1_rpc","h_sec_wh_data_1_rpc",12,0,12, 11, -5,5);
  TH2I* h_sec_wh_data_2_rpc  = new TH2I("h_sec_wh_data_2_rpc","h_sec_wh_data_2_rpc",12,0,12, 11, -5,5);
  TH2I* h_sec_wh_data_3_rpc  = new TH2I("h_sec_wh_data_3_rpc","h_sec_wh_data_3_rpc",12,0,12, 11, -5,5);
  TH2I* h_sec_wh_data_4_rpc  = new TH2I("h_sec_wh_data_4_rpc","h_sec_wh_data_4_rpc",12,0,12, 11, -5,5);

  TH2I* h_nin_nout  = new TH2I("h_nin_nout","h_nin_nout",50,0,50, 50, 0,50);
const int SECTOR = 9;
   for(int i=0; i<nentries; i++){
    //for(int i=0; i<50; i++){

       l1TC.GetEntry(i);
       //l1TCEmu.GetEntry(i);
       evtc.GetEntry(i);
       bmtfc.GetEntry(i);

      int no_in = 0, no_out = 0;

       //h_nin_nout->Fill(l1TC.phSize, bmtfc.phSize);
       ////RPC Plots
      for(int r=0; r<l1TC.rpcSize; r++){
          // if ( (l1TC.rpcSe[r] - 1)!=SECTOR ) continue;

          //if(l1TC.rpcStrip[r]==42) cout<<l1TC.rpcSe[r]<<"\t"<<l1TC.rpcSt[r]<<"\t"<<l1TC.rpcWh[r]<<endl;
          //if(l1TC.rpcStrip[r]==42 && l1TC.rpcSe[r]==12 && l1TC.rpcSt[r]==3 && l1TC.rpcWh[r]==2) continue;
          hrpc_bx->Fill(l1TC.rpcBx[r]);

      if(l1TC.rpcSt[r] == 1)
        h_sec_wh_data_1_rpc->Fill(l1TC.rpcSe[r] - 1, l1TC.rpcWh[r]);
      if(l1TC.rpcSt[r] == 2)
        h_sec_wh_data_2_rpc->Fill(l1TC.rpcSe[r] - 1, l1TC.rpcWh[r]);

      if(l1TC.rpcSt[r] == 3)
        h_sec_wh_data_3_rpc->Fill(l1TC.rpcSe[r] - 1, l1TC.rpcWh[r]);

      if(l1TC.rpcSt[r] == 4)
        h_sec_wh_data_4_rpc->Fill(l1TC.rpcSe[r] - 1, l1TC.rpcWh[r]);

      }
      ///DT/Twinmux inputs
     for(int tp=0; tp<l1TC.phSize; tp++){ 
      if(l1TC.phCode[tp]>=7 ) continue;

           //if ( l1TC.phSe[tp]==SECTOR || l1TC.phSe[tp]==SECTOR+1 || l1TC.phSe[tp]==SECTOR-1 ) {


        if( l1TC.phBx[tp]==0 || l1TC.phBx[tp]==-1 ||l1TC.phBx[tp]==1 ) {
        
        h1_bx_in->Fill(l1TC.phBx[tp]);   

      if(l1TC.phSt[tp] == 1 && l1TC.phBx[tp]==0)
        h_sec_wh_data_1->Fill(l1TC.phSe[tp], l1TC.phWh[tp]);
      if(l1TC.phSt[tp] == 2&& l1TC.phBx[tp]==0)
        h_sec_wh_data_2->Fill(l1TC.phSe[tp], l1TC.phWh[tp]);

      if(l1TC.phSt[tp] == 3 && l1TC.phBx[tp]==0)
        h_sec_wh_data_3->Fill(l1TC.phSe[tp], l1TC.phWh[tp]);

      if(l1TC.phSt[tp] == 4 && l1TC.phBx[tp]==0)
        h_sec_wh_data_4->Fill(l1TC.phSe[tp], l1TC.phWh[tp]);

        no_in++;

      }
      //}
      }//end for tps
      ///TwinMux/BTMF Inputs
      int phi_dt = -999, phi_rpc = -999;
      int phi_dt2 = -999, phi_rpc2 = -999;

     for(int tp=0; tp<bmtfc.phSize; tp++){ 
      //cout<<l1TC.tmCode[tp]<<endl;
      if(bmtfc.phCode[tp]>=7) continue;
      //if ( bmtfc.phSe[tp]==SECTOR || bmtfc.phSe[tp]==SECTOR+1 || bmtfc.phSe[tp]==SECTOR-1) {

      if(  bmtfc.phBxRAW[tp] == 0 || bmtfc.phBxRAW[tp] == 1 || bmtfc.phBxRAW[tp] == -1) {

      h1_bx->Fill(bmtfc.phBxRAW[tp]);

      if(bmtfc.phRpcBit[tp]==1)
        h2_bx->Fill(bmtfc.phBxRAW[tp]);

      if(bmtfc.phRpcBit[tp]==0)
        h3_bx->Fill(bmtfc.phBxRAW[tp]);
      if(bmtfc.phRpcBit[tp]==2)
        h4_bx->Fill(bmtfc.phBxRAW[tp]);

      if(bmtfc.phRpcBit[tp]==1){
        h1_quality1->Fill(bmtfc.phCode[tp]);
      }
      if(bmtfc.phRpcBit[tp]==2){
        h1_quality2->Fill(bmtfc.phCode[tp]);
      }
      no_out++;
      
      }
      //}
      if(bmtfc.phRpcBit[tp]==2 && bmtfc.phSt[tp]==1 && bmtfc.phSe[tp]==SECTOR && bmtfc.phWh[tp]==-2 && bmtfc.phBxRAW[tp]==0) phi_rpc = bmtfc.phAng[tp];
      if(bmtfc.phRpcBit[tp]==0 && bmtfc.phSt[tp]==1 && bmtfc.phSe[tp]==SECTOR && bmtfc.phWh[tp]==-2 && bmtfc.phBxRAW[tp]==0) phi_dt  = bmtfc.phAng[tp];

      if(bmtfc.phRpcBit[tp]==2 && bmtfc.phSt[tp]==2 && bmtfc.phSe[tp]==SECTOR && bmtfc.phWh[tp]==-2 && bmtfc.phBxRAW[tp]==0) phi_rpc2 = bmtfc.phAng[tp];
      if(bmtfc.phRpcBit[tp]==0 && bmtfc.phSt[tp]==2 && bmtfc.phSe[tp]==SECTOR && bmtfc.phWh[tp]==-2 && bmtfc.phBxRAW[tp]==0) phi_dt2  = bmtfc.phAng[tp];

      }//end for tps
      if(phi_rpc!=-999 && phi_dt!=-999){
        //print_event(&l1TC, &bmtfc,&evtc);
        //cout<<phi_rpc<<"\t"<<phi_dt<<endl;
        phi_dt_rpc_2d->Fill(phi_dt, phi_rpc);
      }
    if(phi_rpc2!=-999 && phi_dt2!=-999){
        //print_event(&l1TC, &bmtfc,&evtc);
        //cout<<phi_rpc<<"\t"<<phi_dt<<endl;
        phi_dt_rpc_2d->Fill(phi_dt2, phi_rpc2);
      }
      h_nin_nout->Fill(no_in, no_out);

      if( evtc.event==536947) print_event(&l1TC, &bmtfc,&evtc);
      //if( evtc.event==14963) print_event(&l1TC, &evtc);
      if(no_in < no_out) print_event(&l1TC, &bmtfc,&evtc);
      //if(no_in != no_out) print_event(&l1TC, &evtc);
      //if(l1TC.phSize != l1TC.tmSize) print_event(&l1TC, &evtc);
      //hrpc_bx->Scale(0.01);

    }///End loop of nentries


  //gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

    TCanvas *c1d_phib = new TCanvas("c1d_phib","c1d_phib",800,600);
    h1_bx->GetXaxis()->SetTitle("BMTF Input bx");
    h1_bx->GetYaxis()->SetTitleOffset(1.3);
    h1_bx->SetLineColor(kBlack);
    h1_bx->Draw();
    h2_bx->SetLineColor(kRed);
    h2_bx->Draw("same");
    h3_bx->SetLineColor(kBlue);
    h3_bx->Draw("same");
    h4_bx->SetLineColor(kGreen);
    h4_bx->Draw("same");   

   TLegend *leg;
   leg = new TLegend(0.62,0.62,0.95,0.82);
   leg->AddEntry(h1_bx,"BMTF Input", "l");
    leg->AddEntry(h2_bx,"RPC bit==1", "l");
   leg->AddEntry(h3_bx,"RPC bit==0", "l");
   leg->AddEntry(h4_bx ,"RPC bit==2", "l");
   leg->SetTextFont(42);
   leg->SetFillColor(kWhite);
   leg->SetLineColor(kWhite);
   leg->SetBorderSize(0);
   leg->Draw();


    c1d_phib->SaveAs("Plots/twinmux_output_bx_run"+RUN+LABEL+".png");


    TCanvas *c2d_phib = new TCanvas("c2d_phib","c2d_phib",800,600);
    h1_bx->GetXaxis()->SetTitle("TM Output bx");
    h1_bx->GetYaxis()->SetTitleOffset(1.3);
    h1_bx->SetLineColor(kRed);
    h1_bx->Draw();
    h1_bx_in->SetLineColor(kBlack);
    h1_bx_in->Draw("same");
    //hrpc_bx->SetLineColor(kGreen);
    //hrpc_bx->Draw("same");

     TLegend *leg1;
   leg1 = new TLegend(0.62,0.62,0.95,0.82);
   leg1->AddEntry(h1_bx,"TM Output", "l");
    leg1->AddEntry(h1_bx_in,"TM Input", "l");
   leg1->SetTextFont(42);
   leg1->SetFillColor(kWhite);
   leg1->SetLineColor(kWhite);
   leg1->SetBorderSize(0);
   leg1->Draw();
 
   c2d_phib->SaveAs("Plots/twinmux_io_bx_run"+RUN+LABEL+".png");





    TCanvas *c2d_rpcbx = new TCanvas("c2d_rpcbx","c2d_rpcbx",800,600);
    hrpc_bx->GetXaxis()->SetTitle("RPC Input bx");
    hrpc_bx->GetYaxis()->SetTitleOffset(1.3);
    hrpc_bx->SetLineColor(kRed);
    hrpc_bx->Draw();

     TLegend *leg11;
   leg11 = new TLegend(0.62,0.62,0.95,0.82);
   leg11->AddEntry(hrpc_bx,"RPC BX Input", "l");
   leg11->SetTextFont(42);
   leg11->SetFillColor(kWhite);
   leg11->SetLineColor(kWhite);
   leg11->SetBorderSize(0);
   leg11->Draw();
 
   c2d_rpcbx->SaveAs("Plots/twinmux_rpc_inbx_run"+RUN+LABEL+".png");


    TCanvas *c3d_phib = new TCanvas("c3d_phib","c3d_phib",800,600);
    h1_quality1->GetXaxis()->SetTitle("TM Out - Quality RPC bit == 1 ");
    h1_quality1->GetYaxis()->SetTitleOffset(1.3);
    h1_quality1->Draw();
    c3d_phib->SaveAs("Plots/twinmux_quality_rpcbit1_st1_run"+RUN+LABEL+".png");

    TCanvas *c4d_phib = new TCanvas("c4d_phib","c4d_phib",800,600);
    h1_quality2->GetXaxis()->SetTitle("TM Out - Quality RPC bit == 2 ");
    h1_quality2->GetYaxis()->SetTitleOffset(1.3);
    h1_quality2->Draw();
    c4d_phib->SaveAs("Plots/twinmux_quality_rpcbit2_st1_run"+RUN+LABEL+".png");

    //TCanvas *c5d_phib = new TCanvas("c5d_phib","c5d_phib",800,600);
    //phib_int_out_2d->Draw("COLZ");
    //phib_int_out_2d->SaveAs("Plots/twinmux_quality_rpcbit2.png");


    TCanvas *c10 = canvas_data_mc_2d(h_sec_wh_data_1, "Wedge - St1", "Wheel - St1", -15,15, RUN, true); c10->SetLogz();
    TCanvas *c11 = canvas_data_mc_2d(h_sec_wh_data_2, "Wedge - St2", "Wheel - St2", -15,15, RUN, true); c11->SetLogz();
    TCanvas *c12 = canvas_data_mc_2d(h_sec_wh_data_3, "Wedge - St3", "Wheel - St3", -15,15, RUN, true); c12->SetLogz();
    TCanvas *c13 = canvas_data_mc_2d(h_sec_wh_data_4, "Wedge - St4", "Wheel - St4", -15,15, RUN, true); c13->SetLogz();


    TCanvas *c14 = canvas_data_mc_2d(h_sec_wh_data_1_rpc, "RPC Wedge - St1", "RPC Wheel - St1", -15,15, RUN, true); c14->SetLogz();
    TCanvas *c15 = canvas_data_mc_2d(h_sec_wh_data_2_rpc, "RPC Wedge - St2", "RPC Wheel - St2", -15,15, RUN, true); c15->SetLogz();
    TCanvas *c16 = canvas_data_mc_2d(h_sec_wh_data_3_rpc, "RPC Wedge - St3", "RPC Wheel - St3", -15,15, RUN, true); c16->SetLogz();
    TCanvas *c17 = canvas_data_mc_2d(h_sec_wh_data_4_rpc, "RPC Wedge - St4", "RPC Wheel - St4", -15,15, RUN, true); c17->SetLogz();
    TCanvas *c18 = canvas_data_mc_2d(h_nin_nout, "#DT Input", "#BMTF Input", 0,20, RUN, false); c18->SetLogz();

    TCanvas *c19 = canvas_data_mc_2d(phi_dt_rpc_2d, "DT #phi", "RPC #phi", -2048,-2048, RUN, false); c19->SetLogz();



    c10->SaveAs("Plots/twinmux_dt_st1_run"+RUN+LABEL+".png");
    c11->SaveAs("Plots/twinmux_dt_st2_run"+RUN+LABEL+".png");
    c12->SaveAs("Plots/twinmux_dt_st3_run"+RUN+LABEL+".png");
    c13->SaveAs("Plots/twinmux_dt_st4_run"+RUN+LABEL+".png");
    c14->SaveAs("Plots/twinmux_rpc_st1_run"+RUN+LABEL+".png");
    c15->SaveAs("Plots/twinmux_rpc_st2_run"+RUN+LABEL+".png");
    c16->SaveAs("Plots/twinmux_rpc_st3_run"+RUN+LABEL+".png");
    c17->SaveAs("Plots/twinmux_rpc_st4_run"+RUN+LABEL+".png");
    c18->SaveAs("Plots/twinmux_io_run"+RUN+LABEL+".png");
    c19->SaveAs("Plots/twinmux_rpc_dt_phi_st1_2_run"+RUN+LABEL+".png");

    // hrpc_wh->SetLineColor(kGreen);
    // hrpc_wh->Draw();
  return 0;
}



void print_event(L1TwinMuxTree* l1TC, Event* evtc){
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

     cout<<"TwinMux Output: PhiData"<<endl;
     cout<<"bx wh  ts2  st  sect phi_b phi code"<<endl;
     for(int tp=0; tp<l1TC->tmSize; tp++){ 
        if(l1TC->tmCode[tp]==7) continue;
         cout<<l1TC->tmBx[tp]<<"\t"<<l1TC->tmWh[tp]<<"\t"<<l1TC->tmTs2Tag[tp]<<"\t"<<l1TC->tmSt[tp]<<"\t"<<l1TC->tmSe[tp]<<"    "<<l1TC->tmBandAng[tp]<<"    "<<l1TC->tmAng[tp]<<"    "<<l1TC->tmCode[tp]<<"    "<<l1TC->tmRpcBit[tp]<<endl;
      }



    cout<<endl<<endl;

}


void print_event(L1TwinMuxTree* l1TC, L1BMTF* l1bmf, Event* evtc){
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


     cout<<"TwinMux Output: PhiData"<<endl;
     cout<<"bx wh  ts2  st  sect phi_b phi code"<<endl;
     for(int tp=0; tp<l1TC->tmSize; tp++){ 
        if(l1TC->tmCode[tp]==7) continue;
         cout<<l1TC->tmBx[tp]<<"\t"<<l1TC->tmWh[tp]<<"\t"<<l1TC->tmTs2Tag[tp]<<"\t"<<l1TC->tmSt[tp]<<"\t"<<l1TC->tmSe[tp]<<"    "<<l1TC->tmBandAng[tp]<<"    "<<l1TC->tmAng[tp]<<"    "<<l1TC->tmCode[tp]<<"    "<<l1TC->tmRpcBit[tp]<<endl;
      }
     cout<<"BMTF Input: PhiData"<<endl;
     cout<<"bx wh  ts2  st  sect phi_b phi code rpcbit"<<endl;
     for(int tp=0; tp<l1bmf->phSize; tp++){ 
        if(l1bmf->phCode[tp]==7) continue;
         cout<<l1bmf->phBxRAW[tp]<<"\t"<<l1bmf->phWh[tp]<<"\t"<<l1bmf->phTs2Tag[tp]<<"\t"<<l1bmf->phSt[tp]<<"\t"<<l1bmf->phSe[tp]<<"    "<<l1bmf->phBandAng[tp]<<"    "<<l1bmf->phAng[tp]<<"    "<<l1bmf->phCode[tp]<<"    "<<l1bmf->phRpcBit[tp]<<endl;
      }



    cout<<endl<<endl;

}
