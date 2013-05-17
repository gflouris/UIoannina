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
#include "TMath.h"
using namespace std;
#include "TStyle.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TGraphAsymmErrors.h"
#include "TAxis.h"
#include "TFrame.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TFile.h"
#include "TDirectoryFile.h"
#include "TH1D.h"
#include "TApplication.h"
#include "TMatrixD.h"
#include "TF1.h"
#include "TRootCanvas.h"
#include "TH2F.h"
#include "TH2Poly.h"
#include "TLine.h"
#include "TTree.h"
#include <algorithm>

//#include "/mnt/storage/shared/PATClass.C"
#include "./classes/GENClass.C"
#include "./classes/L1TClass.C"


// tdrGrid: Turns the grid lines on (true) or off (false)

// void tdrGrid(bool gridOn) {
//   TStyle *tdrStyle;
//   tdrStyle->SetPadGridX(gridOn);
//   tdrStyle->SetPadGridY(gridOn);
// }


// fixOverlay: Redraws the axis

void fixOverlay() {
  gPad->RedrawAxis();
}


void setTDRStyle() {
  TStyle *tdrStyle = new TStyle("tdrStyle","Style for P-TDR");

// For the canvas:
  tdrStyle->SetCanvasBorderMode(0);
  tdrStyle->SetCanvasColor(kWhite);
  tdrStyle->SetCanvasDefH(600); //Height of canvas
  tdrStyle->SetCanvasDefW(600); //Width of canvas
  tdrStyle->SetCanvasDefX(0);   //POsition on screen
  tdrStyle->SetCanvasDefY(0);

// For the Pad:
  tdrStyle->SetPadBorderMode(0);
  // tdrStyle->SetPadBorderSize(Width_t size = 1);
  tdrStyle->SetPadColor(kWhite);
  tdrStyle->SetPadGridX(false);
  tdrStyle->SetPadGridY(false);
  tdrStyle->SetGridColor(0);
  tdrStyle->SetGridStyle(3);
  tdrStyle->SetGridWidth(1);

// For the frame:
  tdrStyle->SetFrameBorderMode(0);
  tdrStyle->SetFrameBorderSize(1);
  tdrStyle->SetFrameFillColor(0);
  tdrStyle->SetFrameFillStyle(0);
  tdrStyle->SetFrameLineColor(1);
  tdrStyle->SetFrameLineStyle(1);
  tdrStyle->SetFrameLineWidth(1);




// For the histo:
  // tdrStyle->SetHistFillColor(1);
  // tdrStyle->SetHistFillStyle(0);
  tdrStyle->SetHistLineColor(1);
  tdrStyle->SetHistLineStyle(0);
  tdrStyle->SetHistLineWidth(1);
  // tdrStyle->SetLegoInnerR(Double_t rad = 0.5);
  // tdrStyle->SetNumberContours(Int_t number = 20);

  tdrStyle->SetEndErrorSize(2);
//**  tdrStyle->SetErrorMarker(20);
  tdrStyle->SetErrorX(0.5);
  
  tdrStyle->SetMarkerStyle(20);

//For the fit/function:
  tdrStyle->SetOptFit(1);
  tdrStyle->SetFitFormat("5.4g");
  tdrStyle->SetFuncColor(2);
  tdrStyle->SetFuncStyle(1);
  tdrStyle->SetFuncWidth(1);

//For the date:
  tdrStyle->SetOptDate(0);
  // tdrStyle->SetDateX(Double_t x = 0.01);
  // tdrStyle->SetDateY(Double_t y = 0.01);

// For the statistics box:
  tdrStyle->SetOptFile(0);
  tdrStyle->SetOptStat(0); // To display the mean and RMS:   SetOptStat("mr");
  tdrStyle->SetStatColor(kWhite);
  tdrStyle->SetStatFont(42);
  tdrStyle->SetStatFontSize(0.025);
  tdrStyle->SetStatTextColor(1);
  tdrStyle->SetStatFormat("6.4g");
  tdrStyle->SetStatBorderSize(1);
  tdrStyle->SetStatH(0.1);
  tdrStyle->SetStatW(0.15);
  // tdrStyle->SetStatStyle(Style_t style = 1001);
  // tdrStyle->SetStatX(Double_t x = 0);
  // tdrStyle->SetStatY(Double_t y = 0);

// Margins:
  tdrStyle->SetPadTopMargin(0.05);
  tdrStyle->SetPadBottomMargin(0.13);
  tdrStyle->SetPadLeftMargin(0.16);
  tdrStyle->SetPadRightMargin(0.02);

// For the Global title:

  tdrStyle->SetOptTitle(0);
  tdrStyle->SetTitleFont(42);
  tdrStyle->SetTitleColor(1);
  tdrStyle->SetTitleTextColor(1);
  tdrStyle->SetTitleFillColor(10);
  tdrStyle->SetTitleFontSize(0.05);
  // tdrStyle->SetTitleH(0); // Set the height of the title box
  // tdrStyle->SetTitleW(0); // Set the width of the title box
  // tdrStyle->SetTitleX(0); // Set the position of the title box
  // tdrStyle->SetTitleY(0.985); // Set the position of the title box
  // tdrStyle->SetTitleStyle(Style_t style = 1001);
  // tdrStyle->SetTitleBorderSize(2);

// For the axis titles:

  tdrStyle->SetTitleColor(1, "XYZ");
  tdrStyle->SetTitleFont(42, "XYZ");
  tdrStyle->SetTitleSize(0.06, "XYZ");
  // tdrStyle->SetTitleXSize(Double_t size = 0.02); // Another way to set the size?
  // tdrStyle->SetTitleYSize(Double_t size = 0.02);
  tdrStyle->SetTitleXOffset(0.9);
  tdrStyle->SetTitleYOffset(1.25);
  // tdrStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset

// For the axis labels:

  tdrStyle->SetLabelColor(1, "XYZ");
  tdrStyle->SetLabelFont(42, "XYZ");
  tdrStyle->SetLabelOffset(0.007, "XYZ");
  tdrStyle->SetLabelSize(0.05, "XYZ");

// For the axis:

  tdrStyle->SetAxisColor(1, "XYZ");
  tdrStyle->SetStripDecimals(kTRUE);
  tdrStyle->SetTickLength(0.03, "XYZ");
  tdrStyle->SetNdivisions(510, "XYZ");
  tdrStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  tdrStyle->SetPadTickY(1);

// Change for log plots:
  tdrStyle->SetOptLogx(0);
  tdrStyle->SetOptLogy(0);
  tdrStyle->SetOptLogz(0);

// Postscript options:
  tdrStyle->SetPaperSize(20.,20.);
  // tdrStyle->SetLineScalePS(Double_t scale = 3);
  // tdrStyle->SetLineStyleString(Int_t i, const char* text);
  // tdrStyle->SetHeaderPS(const char* header);
  // tdrStyle->SetTitlePS(const char* pstitle);

  // tdrStyle->SetBarOffset(Double_t baroff = 0.5);
  // tdrStyle->SetBarWidth(Double_t barwidth = 0.5);
  // tdrStyle->SetPaintTextFormat(const char* format = "g");
  // tdrStyle->SetPalette(Int_t ncolors = 0, Int_t* colors = 0);
  // tdrStyle->SetTimeOffset(Double_t toffset);
  // tdrStyle->SetHistMinimumZero(kTRUE);

  tdrStyle->cd();


}



void gmtdttf(){
L1TClass l1c;
GENClass genc;

      TFile *f ;
      f = new TFile("../test/Tree_from_RAW.root");//Tree_from_RAW.root");
      f->cd("../test/Tree_from_RAW.root:/l1NtupleProducer");
      TTree *tree;
      tree = (TTree*)gDirectory->Get("L1Tree");
      l1c.Init(tree);

      f->cd("../test/Tree_from_RAW.root:/GENTProducer");
      TTree *tree1;
      tree1 = (TTree*)gDirectory->Get("GENTree");
//       dir->GetObject("GENTree",tree);
//       f->cd("../test/Tree_from_RAW.root:/l1NtupleProducer");
//       tree = (TTree*)gDirectory->Get("L1Tree");
      genc.Init(tree1);

  TH2F *gmt_dttf = new TH2F("GMT VS DTTF Pt Histogram", "GMT Vs DTTF - Pt", 40,0,160, 35,0,35);
  TH2F *gmt_gen = new TH2F("GMT VS GEN Pt Histogram", "GMT Vs GEN - Pt", 40,0,160, 80,0,400);

  TH1F *gmtpt_histo = new TH1F("GMT Pt Histogramm", "GMTPH", 32,0,160);
  TH1F *dttfrank_histo = new TH1F("DTTF RANK Histogramm", "DTTFPH", 32,0,32);
  TH1F *genandgmt_histo = new TH1F("GEN AND GMT RANK Histogramm", "GENANDGMT", 80,0,400);
  TH1F *genpt_histo = new TH1F("Gen Pt Histogramm", "GENPH", 80,0,400);


int nentries = l1c.fChain -> GetEntries();
//int nentriesr = genc.fChain -> GetEntries();

float gmt_pt, dttf_pt, gen_pt;
//bool tight_dttfo;

vector<float> pt_gmt, pt_dttf, eta_dttf, eta_gmt, phi_gmt, phi_dttf, eta_gen, phi_gen, pt_gen;;
//bool tight;
int equal = 0, unequal = 0;

for(int i=0; i<nentries; i++){
	if(i%10000==0) std::cout<<i<<std::endl;
	int sizeg =0;
	int passed_gmt = 0, passed_dttf = 0, passed_gen=0;

	l1c.GetEntry(i);
	genc.GetEntry(i);

	sizeg = l1c.N;
        pt_gmt.clear();
        eta_gmt.clear();
        phi_gmt.clear();
 
 /////Fill GMT Variables 
		for(int j=0; j<sizeg; j++){
			gmt_pt=0;
			gmt_pt = l1c.Pt[j];
			//tight = l1c.
			if((l1c.CandBx[j]==0 )&&gmt_pt>20){ 
				gmtpt_histo->Fill(gmt_pt);
				pt_gmt.push_back(gmt_pt);
				////GMT Phi 0-6.28 after studies I found out that 0-3.14 --> 0-3.14 and 3.14-6.28 --> -3.14-0
				if(l1c.Phi[j]<3.14) phi_gmt.push_back(l1c.Phi[j]);
				else	phi_gmt.push_back(l1c.Phi[j]-6.28);
				eta_gmt.push_back(l1c.Eta[j]);
				phi_gmt.push_back(l1c.Phi[j]);
				passed_gmt++;
			}

		}


////Fill DTTF Variables

	int sized = 0;
	sized = l1c.trSize;
	pt_dttf.clear();
	eta_dttf.clear();	
	phi_dttf.clear();
		for(int j=0; j<sized; j++){
			dttf_pt=0;
			dttf_pt = l1c.trPtPck[j];
			if(l1c.trBx[j]==1 && l1c.trQual[j]==7){
			pt_dttf.push_back(dttf_pt);
			dttfrank_histo->Fill(dttf_pt);		
			passed_dttf++;
		}


		}
////Fill GEN Variables

	int sizegen = 0;
	sizegen = genc.gen_muons;
	pt_gen.clear();
	eta_gen.clear();
	phi_gen.clear();
		for(int j=0; j<sizegen; j++){
			gen_pt=0;
			gen_pt = genc.genPt_Mu[j];
			if(gen_pt>5.&& genc.genEta_Mu[j]<1.2 && genc.genEta_Mu[j]>-1.2){
			eta_gen.push_back(genc.genEta_Mu[j]);
			phi_gen.push_back(genc.genPhi_Mu[j]);
			pt_gen.push_back(gen_pt);
			genpt_histo->Fill(gen_pt);		
			passed_gen++;
		}


		}
////Match GEN to GMT 
	if(passed_gen>=1){
		
		float dr[20][20];  for(int kk=0; kk<20;kk++){for(int jj=0; jj<20;jj++){dr[kk][jj]=500; }}
		  for(int j=0; j<passed_gen; j++){
			for(int k=0; k<passed_gmt; k++){
			////Fill an array with all dr's
			dr[j][k]=sqrt(pow((eta_gen[j]-eta_gmt[j]),2)+pow((phi_gen[j]-phi_gmt[j]),2));
			}
		  }
		float mindr=0.5;
		bool matched_gen = false;
		for(int ii=0; ii<passed_gen; ii++){
		int posj=100, posk=100;
		  for(int j=0; j<passed_gen; j++){
			for(int k=0; k<passed_gmt; k++){
				//if(k==skipk || j==skipj) continue;
				if(dr[j][k]<mindr) {
					////Select the best match
					mindr=dr[j][k]; matched_gen = true;
					posj = j; posk = k;
					
				}			
			}
		  }
		for(int l=0; l<20; l++) {dr[l][posk]=500; dr[posj][l]=500;} ////"Delete" all elements row-column of best match
		if(matched_gen) genandgmt_histo->Fill(pt_gen[ii]);
		}
	

	}

	if((passed_gmt==passed_dttf)&&passed_gmt!=0) {
		for(int j=0; j<sized; j++) gmt_dttf->Fill(pt_gmt[j],pt_dttf[j]);
		equal++;
	}
	if((passed_gmt==passed_gen)&&passed_gmt!=0) {
		for(int j=0; j<sizeg; j++) gmt_gen->Fill(pt_gmt[j],pt_gen[j]);
		equal++;
	}
 }

cout<<"equal mu's = "<<equal<<"  gmt greater than gen = "<<unequal<<endl;

TFile h1("./ROOTFiles/dttf_analyzed_gmpt20_noqual_dr05_geneta12.root", "NEW");
gmt_dttf->Write();
gmtpt_histo->Write();
dttfrank_histo->Write();
genpt_histo->Write();
gmt_gen->Write();
genandgmt_histo->Write();

  TH1F *gmteff_histo = new TH1F("Efficiency", "Eff", 80,0,400);

float num, den, ratio[80];
	for(int k=0; k<80; k++){
	num = genandgmt_histo->GetBinContent(k+1);
	den = genpt_histo->GetBinContent(k+1);
	ratio[k] = 0;
        if(den!=0){
        ratio[k] = num/den;
	}
	gmteff_histo->SetBinContent(k+1,ratio[k]);
	cout<<ratio[k]<<endl;
	}
	
		
gmteff_histo->Write();

}

void effgraphs(){
TFile *f1 = TFile::Open("./ROOTFiles/dttf_analyzed_gmpt20_noqual_dr05_geneta12.root");
TH1F *genandgmt_histo = (TH1F*)f1->Get("GEN AND GMT RANK Histogramm");
TH1F *genpt_histo = (TH1F*)f1->Get("Gen Pt Histogramm");
  ////fit function
  TF1 *fitEff = new TF1("fitEff","0.5+0.5*TMath::Erf([0]*x-[1])",0,1000);
  fitEff->SetParameters(0.01,10);

  //fitEff->Draw();
  double e=0.99;
  TLatex l;
  char ltx[100];

int p=0;
float num, den, ratio[80], pt[80],eyl[80], eyh[80], exl[80], exh[80];
//int p = 0;
	for(int k=0; k<80; k++){
	num = genandgmt_histo->GetBinContent(k+1);
	den = genpt_histo->GetBinContent(k+1);
	if(den!=0){	
	//ratio[p] = -10;
        pt[p] = (Double_t)k*5.;
        ratio[p] = num/den;
        if(num==0){eyl[p]=0; eyh[p]=0; exl[p]=0; exh[p]=0;}
        else{
        float a = ratio[p] + (1/(2*den)) ;
        float b = sqrt( ratio[p]*(1-ratio[p])/den +0.25/(den*den) );
        float c = (1+(1/den));
        eyl[p] = ratio[p]-(a-b)/c;
        eyh[p] = (a+b)/c-ratio[p];

        exl[p]=2.5;
        exh[p]=2.5;
       }

	}

	else continue;
	p+=1;

	}

TGraphAsymmErrors *eff =new TGraphAsymmErrors(p,pt,ratio,exl,exh,eyl,eyh);
TCanvas *c1;
c1 = new TCanvas("c1", "Trigger Eff.", 800, 600);
c1->cd();
 eff->SetTitle("Trigger Efficiency;Muon p_{T} (GeV);Efficiency");
  eff->SetMaximum(2);
  eff->SetMinimum(0);

eff->SetMarkerStyle(3);
eff->Draw("AP");

  eff->Fit("fitEff","","",5,250);
  double a20_1=fitEff->GetParameter(0);
  double b20_1=fitEff->GetParameter(1);
  double x20_1=(TMath::ErfInverse(2*e-1)+b20_1)/a20_1;
  
  l.SetTextAlign(12);
  l.SetTextSize(0.045);
  l.DrawLatex(100.,1.74,"Trigger GMT");
  sprintf(ltx,"Turn on Point:%.0f GeV",x20_1);
  l.DrawLatex(100.,1.64,ltx);



}
