#include <iostream>
#include "L1Data.h"
#include "L1Emulator.h"
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


float local_2_global_phi(int local_phi, int processor){

float global_phi = -1000;
if(local_phi>=0 && local_phi<=30)
  global_phi = local_phi + processor*30.;
if(local_phi<0)
  global_phi = 30-local_phi + (processor-1)*30.;
if(local_phi>30)
  global_phi = local_phi-30 + (processor+1)*30.;

return global_phi;

}


float global_eta(int local_eta){

return local_eta*0.010875;

}

TCanvas *canvas_data_mc(TH1F * data_xs, TH1F * mc_xs, TString canvas, bool Logy, double minx, double maxx,double miny, double maxy, TString Labelx,TString RUN){

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
   leg->AddEntry(mc_xs,"Data", "p");
   leg->AddEntry(data_xs,"Emulator", "p");
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
int emu_vs_hw(){

 	//setTDRStyle();
  	//gStyle->SetPalette(1);
  TString RUN = "268754_1";  //"268536";

    TFile* f1 = new TFile("../../test/Ntuple_BMTF_data_Run"+RUN+".root");

    ///L1Tree    
    TDirectory* dirl1 = (TDirectory*)f1->Get("L1TProducer");
    TTree* treel1 = (TTree*)dirl1->Get("L1Tree");

    L1Data l1TC;
    l1TC.Init(treel1);

    ///GENTree    
    TDirectory* dirl2 = (TDirectory*)f1->Get("L1TProducerEmulator");
    TTree* emu_tree = (TTree*)dirl2->Get("L1Tree");

    L1Emulator l1TCEmu;
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
    TH1F* h2_bx   = new TH1F("h2bx","h2bx",7,-3,3);

	TH2I* h_nmu = new TH2I("h_nmu","h_nmu",10,0,10,10,0,10);
	TH2I* h_qual = new TH2I("h_qual","h_qual",20,0,20,20,0,20);


    TH1F* h1   = new TH1F("h1","h1",280,0,280);
    TH1F* h2   = new TH1F("h2","h2",280,0,280);
	TH2I* h_pt = new TH2I("h_pt","h_pt",280,0,280,280,0,280);


    TH1F* h1_phi = new TH1F("h1_phi","h1_phi",81,-20,60);
    TH1F* h2_phi = new TH1F("h2_phi","h2_phi",81,-20,60);
	 TH2I* h_phi  = new TH2I("h_phi","h_phi",64,-8,55,64,-8,55);

    TH1F* h1_eta = new TH1F("h1_eta","h1_eta",461,-230,230);
    TH1F* h2_eta = new TH1F("h2_eta","h2_eta",461,-230,230);
	  TH2I* h_eta  = new TH2I("h_eta","h_eta",461,-230,230,461,-230,230);


  TH2I* h_eta_phi_data  = new TH2I("h_eta_phi_data","h_eta_phi_data",360,0,360,200,-2.,2.);
  TH1F* h_global_phi  = new TH1F("h_global_phi","h_global_phi",36,0,360);
  TH1F* h_global_phi_emu  = new TH1F("h_global_phi_emu","h_global_phi_emu",36,0,360);

  TH2I* h_sec_wh_data_1  = new TH2I("h_sec_wh_data_1","h_sec_wh_data_1",12,0,12, 11, -5,5);
  TH2I* h_sec_wh_data_2  = new TH2I("h_sec_wh_data_2","h_sec_wh_data_2",12,0,12, 11, -5,5);
  TH2I* h_sec_wh_data_3  = new TH2I("h_sec_wh_data_3","h_sec_wh_data_3",12,0,12, 11, -5,5);
  TH2I* h_sec_wh_data_4  = new TH2I("h_sec_wh_data_4","h_sec_wh_data_4",12,0,12, 11, -5,5);

//l1TCEmu.GetEntry(1);
       //cout<<l1TCEmu.emubmtfSize<<endl;
 
   int discrep_pt = 0, discrep_phi = 0, discrep_eta = 0, discrep_qual=0;
   int total_mu = 0;
   int event_diff_num_mu = 0;

   const int SECTOR=2;

    for(int i=0; i<nentries; i++){
       l1TC.GetEntry(i);
       l1TCEmu.GetEntry(i);
       evtc.GetEntry(i);
       if(l1TC.bmtfSize!=1) continue;     
       if(l1TCEmu.emubmtfSize!=1) continue;
       h_nmu->Fill(l1TC.bmtfSize,l1TCEmu.emubmtfSize);
       ///Read size and loop over GEN
       //cout<<l1TCEmu.emubmtfSize<<endl;
        for(int mu=0; mu<l1TCEmu.emubmtfSize; mu++){
                //if ( l1TCEmu.emubmtfprocessor[mu]!=SECTOR ) continue;

                //Fill the histogram
        	     	h1_bx->Fill(l1TCEmu.emubmtfbx[mu]);
                h1->Fill(l1TCEmu.emubmtfPt[mu]);
                h1_phi->Fill(l1TCEmu.emubmtfPhi[mu]);
                h1_eta->Fill(l1TCEmu.emubmtfEta[mu]);


                float global_phi = local_2_global_phi(l1TCEmu.emubmtfPhi[mu],l1TCEmu.emubmtfprocessor[mu]);
                 
                h_global_phi_emu->Fill(global_phi);
        }///End of reading GEN  


       ///Read size and loop over BMTF
       //cout<<l1TC.bmtfSize<<endl;
        for(int mu=0; mu<l1TC.bmtfSize; mu++){
                //if ( l1TC.bmtfprocessor[mu]!=SECTOR ) continue;

                //cout<<"Pt = "<<l1TC.bmtfPt[mu]<<endl;
                //Fill the histogram
        		    h2_bx->Fill(l1TC.bmtfbx[mu]);
                h2->Fill(l1TC.bmtfPt[mu]);
                h2_phi->Fill(l1TC.bmtfPhi[mu]);
                h2_eta->Fill(l1TC.bmtfEta[mu]);

        }///End of reading BMTF 


        //cout<<l1TC.bmtfEta[0]<<"\t"<<l1TCEmu.emubmtfEta[0]<<endl;

    if(l1TCEmu.emubmtfSize!=l1TC.bmtfSize) {
    	event_diff_num_mu++;
    	//cout<<i<<endl;
    	//cout<<"#Emu = "<<l1TCEmu.emubmtfSize<<endl;
    	//cout<<"#Data = "<<l1TC.bmtfSize<<endl;

    }
   
    int index_disc = -1;
    //if( i == 31928) {index_disc = i; cout<<i<<endl;}
    //if(evtc.event== 44708) {index_disc = i; cout<<i<<endl;}
    //if (l1TCEmu.emubmtfSize!=l1TC.bmtfSize) {
//      index_disc = i;
    //}

    if(l1TCEmu.emubmtfSize==l1TC.bmtfSize) {


    	for(int mu=0; mu<l1TC.bmtfSize; mu++){
        //if ( l1TC.bmtfprocessor[mu]!=SECTOR ) continue;
        //if(l1TC.bmtfbx[mu]!=0) continue;
        //if(l1TC.bmtfPhi[mu]==45 && l1TCEmu.emubmtfPhi[mu]==0) {index_disc = i; }
        if(l1TC.bmtfEta[mu]==66 && l1TCEmu.emubmtfEta[mu]==43) {index_disc = i; }
         total_mu++;



    		h_pt->Fill(l1TC.bmtfPt[mu],l1TCEmu.emubmtfPt[mu]);
    		h_phi->Fill(l1TC.bmtfPhi[mu],l1TCEmu.emubmtfPhi[mu]);
    		h_eta->Fill(l1TC.bmtfEta[mu],l1TCEmu.emubmtfEta[mu]);
    		h_qual->Fill(l1TC.bmtfqual[mu],l1TCEmu.emubmtfqual[mu]);

        //}


    		if(l1TC.bmtfPt[mu]!=l1TCEmu.emubmtfPt[mu]) discrep_pt++;
    		if(l1TC.bmtfPhi[mu]!=l1TCEmu.emubmtfPhi[mu]) discrep_phi++;
        float hwphi = l1TC.bmtfPhi[mu];
        float emuphi = l1TCEmu.emubmtfPhi[mu];
      
       if( i==index_disc ) {
        //if( l1TC.bmtfEta[mu]==-51 && l1TCEmu.emubmtfEta[mu]!=-51 && l1TCEmu.emubmtfwh[mu]<0 ){
        //  index_disc = i;
            cout<<i<<"\t Data mu# "<<mu<<"\t bx"<<l1TC.bmtfbx[mu]<<endl;
            cout<<"Phi \t"<<l1TC.bmtfPhi[mu]<<endl;
            cout<<"Pt \t"<<l1TC.bmtfPt[mu]<<endl;
            cout<<"Eta \t"<<l1TC.bmtfEta[mu]<<endl;
            cout<<"Fine Bit \t"<<l1TC.bmtfFineBit[mu]<<endl;
            cout<<"Q \t"<<l1TC.bmtfqual[mu]<<endl;
            cout<<"W \t"<<l1TC.bmtfwh[mu]<<endl;
            cout<<"TA \t"<<l1TC.bmtftrAddress[(mu*4)+0]<<"-"<<l1TC.bmtftrAddress[(mu*4)+1]<<"-"<<l1TC.bmtftrAddress[(mu*4)+2]<<"-"<<l1TC.bmtftrAddress[(mu*4)+3]<<endl;
            cout<<"Proc: \t"<<l1TC.bmtfprocessor[mu]<<endl;

            cout<<endl;
        }
        //}


    		if(l1TC.bmtfEta[mu]!=l1TCEmu.emubmtfEta[mu]) discrep_eta++;
    		if(l1TC.bmtfqual[mu]!=l1TCEmu.emubmtfqual[mu]) discrep_qual++;

        }///End of reading BMTF 

        for(int mu=0; mu<l1TCEmu.emubmtfSize; mu++){

               if( i==index_disc ) {
          //index_disc = i;
            cout<<i<<"\t Emulator mu# "<<mu<<"\t bx"<<l1TCEmu.emubmtfbx[mu]<<endl;
            cout<<"Phi \t"<<l1TCEmu.emubmtfPhi[mu]<<endl;
            cout<<"Pt \t"<<l1TCEmu.emubmtfPt[mu]<<endl;
            cout<<"Eta \t"<<l1TCEmu.emubmtfEta[mu]<<endl;
            cout<<"Fine Eta \t"<<l1TCEmu.emubmtfFineBit[mu]<<endl;
            cout<<"Q \t"<<l1TCEmu.emubmtfqual[mu]<<endl;
            cout<<"W \t"<<l1TCEmu.emubmtfwh[mu]<<endl;
            cout<<"TA \t"<<l1TCEmu.emubmtftrAddress[(mu*4)+0]<<"-"<<l1TCEmu.emubmtftrAddress[(mu*4)+1]<<"-"<<l1TCEmu.emubmtftrAddress[(mu*4)+2]<<"-"<<l1TCEmu.emubmtftrAddress[(mu*4)+3]<<endl;
            cout<<"Proc: \t"<<l1TCEmu.emubmtfprocessor[mu]<<endl;

            cout<<endl;
            }
        }
        if(i==index_disc){
            cout<<"Run = "<<evtc.run<<"\t Event = "<<evtc.event<<"\t Lumi = "<<evtc.lumi<<endl;

        }

    }
      if( i==index_disc ){

     cout<<"Inputs: PhiData"<<endl;
     cout<<"bx wh  ts2  st  sect phi_b phi code"<<endl;
     }
     for(int tp=0; tp<l1TC.phSize; tp++){ 

      if(l1TC.phSt[tp] == 1)
        h_sec_wh_data_1->Fill(l1TC.phSe[tp], l1TC.phWh[tp]);
      if(l1TC.phSt[tp] == 2)
        h_sec_wh_data_2->Fill(l1TC.phSe[tp], l1TC.phWh[tp]);

      if(l1TC.phSt[tp] == 3)
        h_sec_wh_data_3->Fill(l1TC.phSe[tp], l1TC.phWh[tp]);

      if(l1TC.phSt[tp] == 4)
        h_sec_wh_data_4->Fill(l1TC.phSe[tp], l1TC.phWh[tp]);

      //if( i==918 ) {
      if( i==index_disc ){
          cout<<l1TC.phBxRAW[tp]<<"\t"<<l1TC.phWh[tp]<<"\t"<<l1TC.phTs2Tag[tp]<<"\t"<<l1TC.phSt[tp]<<"\t"<<l1TC.phSe[tp]<<"    "<<l1TC.phBandAng[tp]<<"    "<<l1TC.phAng[tp]<<"    "<<l1TC.phCode[tp]<<endl;
        }


    }
      if( i==index_disc ){

      cout<<"Inputs: EtaData"<<endl;
      cout<<"bx wh   st  sect hits"<<endl;
}
     for(int tp=0; tp<l1TC.thSize; tp++){ 

      if( i==index_disc ){

          cout<<l1TC.thBx[tp]<<"\t"<<l1TC.thWh[tp]<<"\t"<<l1TC.thSt[tp]<<"\t"<<l1TC.thSe[tp]<<"\t"<<l1TC.thTheta[tp]<<endl;
        }


    }
if( i==index_disc ) cout<<endl<<endl;
      for(int mu=0; mu<l1TC.bmtfSize; mu++){
          //if ( l1TC.bmtfprocessor[mu]!=SECTOR ) continue;
          float global_phi = local_2_global_phi(l1TC.bmtfPhi[mu],l1TC.bmtfprocessor[mu]);
          float global_etav = global_eta(l1TC.bmtfEta[mu]);
          h_eta_phi_data->Fill(global_phi, global_etav);
          h_global_phi->Fill(global_phi);
     }

    }///End loop of nentries


    cout<<"Number of events= "<<nentries<<endl;
    cout<<"Number of muons = "<<total_mu<<endl;

    cout<<"\tMismatches\t Mismatches/Total "<<endl;

   	cout<<"n_mu = "<<event_diff_num_mu<<"\t\t"<<(float)event_diff_num_mu/(float)nentries<<endl;

    cout<<"pt = "<<discrep_pt<<"\t\t"<<(float)discrep_pt/(float)total_mu<<endl;
	cout<<"phi = "<<discrep_phi<<"\t\t"<<(float)discrep_phi/(float)total_mu<<endl;
	cout<<"eta = "<<discrep_eta<<"\t\t"<<(float)discrep_eta/(float)total_mu<<endl;
	cout<<"quality = "<<discrep_qual<<"\t\t"<<(float)discrep_qual/(float)total_mu<<endl;



    TCanvas *c1 = canvas_data_mc( h1, h2, "pt", true, 0, 280, 0.8, 2000000, "p_{T}", RUN);
    TCanvas *c2 = canvas_data_mc( h1_phi, h2_phi, "phi", true, -20, 60, 0.8, 2000000, "#phi", RUN);
    TCanvas *c3 = canvas_data_mc( h1_eta, h2_eta, "eta", true, -230, 230, 0.8, 2000000, "#eta", RUN);
    TCanvas *cbx = canvas_data_mc( h1_bx, h2_bx, "bx", true, -3, 3, 0.8, 2000000, "bx", RUN);
    TCanvas *cphi = canvas_data_mc( h_global_phi_emu, h_global_phi, "global #phi", true, 0, 360, 0.8, 2000000, "global #phi", RUN);

  
    TCanvas *c4 = canvas_data_mc_2d(h_pt, "Data p_{T}","Emulator p_{T}", 0,280, RUN, false); c4->SetLogz();
    TCanvas *c5 = canvas_data_mc_2d(h_phi, "Data #phi_","Emulator #phi", -8,55, RUN, false); c5->SetLogz();
    TCanvas *c6 = canvas_data_mc_2d(h_eta, "Data #eta","Emulator #eta", -100,100, RUN, false); c6->SetLogz();
    TCanvas *c7 = canvas_data_mc_2d(h_nmu, "Data # muons","Emulator # muons", 0,10, RUN, true); c7->SetLogz();
    TCanvas *c8 = canvas_data_mc_2d(h_qual, "Data Quality","Emulator Quality", 0,20, RUN, true); c8->SetLogz();

    TCanvas *c9 = canvas_data_mc_2d(h_eta_phi_data, "Data #phi","Data #eta", -360,360, RUN, false); c9->SetLogz();
    TCanvas *c10 = canvas_data_mc_2d(h_sec_wh_data_1, "Sector - St1", "Wheel - St1", -15,15, RUN, true); c10->SetLogz();
    TCanvas *c11 = canvas_data_mc_2d(h_sec_wh_data_2, "Sector - St2", "Wheel - St2", -15,15, RUN, true); c11->SetLogz();
    TCanvas *c12 = canvas_data_mc_2d(h_sec_wh_data_3, "Sector - St3", "Wheel - St3", -15,15, RUN, true); c12->SetLogz();
    TCanvas *c13 = canvas_data_mc_2d(h_sec_wh_data_4, "Sector - St4", "Wheel - St4", -15,15, RUN, true); c13->SetLogz();



  TString extrLABEL="";
/*
  c1->SaveAs("emu_data_pt_run"+RUN+extrLABEL+".png");
	//c2->SaveAs("emu_data_phi_run"+RUN+".png");
	c3->SaveAs("emu_data_eta_run"+RUN+extrLABEL+".png");
	cbx->SaveAs("emu_data_bx_run"+RUN+extrLABEL+".png");
	c4->SaveAs("emu_data_pt_2d_run"+RUN+extrLABEL+".png");
	c5->SaveAs("emu_data_phi_2d_run"+RUN+extrLABEL+".png");
	  c6->SaveAs("emu_data_eta_2d_run"+RUN+extrLABEL+".png");
	c7->SaveAs("emu_data_nmu_2d_run"+RUN+extrLABEL+".png");
	c8->SaveAs("emu_data_qual_2d_run"+RUN+extrLABEL+".png");
  
 //  c9->SaveAs("data_eta_phi_2d_run"+RUN+".png");

  c10->Update();
  c10->SaveAs("data_sec_wh_st1_run"+RUN+extrLABEL+".png");
  c11->SaveAs("data_sec_wh_st2_run"+RUN+extrLABEL+".png");
  c12->SaveAs("data_sec_wh_st3_run"+RUN+extrLABEL+".png");
  c13->SaveAs("data_sec_wh_st4_run"+RUN+extrLABEL+".png");*/

  return 0;
}
