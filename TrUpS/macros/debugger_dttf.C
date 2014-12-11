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
using namespace std;


#include "./classes/L1TreeClass.C"
#include "./classes/GENTreeClass.C"
//#include "/home/gflouris/Analysis/setTDRStyle.C"



int debugger_dttf(TString in_file){

  
 // bool upgrade_plots = true;
  
  //setTDRStyle();

  L1TreeClass l1c;
  GENTreeClass genc;

  
  TFile *f = new TFile(in_file);
  TFile *file1 = new TFile(in_file);
  
  TDirectory * dirgen = (TDirectory*)f->Get(in_file+":/GENTProducer");
  TTree *treegen;
  dirgen->GetObject("GENTree",treegen);

  TDirectory * dir = (TDirectory*)file1->Get(in_file+":/L1TProducer");
  TTree *treel1;
  dir->GetObject("L1Tree",treel1);

  l1c.Init(treel1);
  genc.Init(treegen);

  
// float phtf_pt[1700];
// ifstream infile1;
// //for(int i=0; i<17; i++){
// 
// std::stringstream sst; sst<< "./DTTF_up/phtf_output100.txt";
// string name = sst.str();
// infile1.open (name.c_str(), ifstream::in);
// 
//   for(int k=0; k<1700; k++){
//     infile1 >> phtf_pt[k];
//   }
// 
// infile1.close();
//}

  
  
  int nentries = l1c.fChain -> GetEntries();

  float PCKtoPHYS[33] = {-100, 0.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 6.0, 7.0, 8.0, 10., 12., 14., 16., 18., 20., 25., 30., 35., 40., 45., 50., 60., 70., 80., 90., 100., 120., 140.,160.};

float genpt,geneta,genphi, gmtpt,gmteta,gmtphi, dttf_ph_pt;

   
cout<<"Analysing tree with: "<<nentries<<" events"<<endl;

int myints[] = {  49, 2699, 4467, 6020, 6907, 6927, 7477};



int size_myints = sizeof(myints)/sizeof(int);

for(int i=0; i<size_myints; i++){

   l1c.GetEntry(myints[i]);
   genc.GetEntry(myints[i]);
   


		cout<<"Bad event "<<i<<"  "<<myints[i]<<"  "<<endl;
                cout<<"1c.phBxRAW[k]+<<l1c.Ts2Tag[k]<<<l1c.phSize<<<<l1c.phWh[k]<<<<l1c.phSt[k]<<<<l1c.phSe[k]<<<<l1c.phAng[k]<<<<l1c.phBandAng[k]<<<<l1c.phCode[k]"<<endl;

	      for(int k=0; k<l1c.phSize; k++){
                cout<<l1c.phBxRAW[k]<<"\t\t\t"<<l1c.phTs2Tag[k]<<"\t\t\t"<<l1c.phSize<<"\t"<<l1c.phWh[k]<<"\t"<<l1c.phSt[k]<<"\t"<<l1c.phSe[k]<<"\t"<<l1c.phAng[k]<<"\t"<<l1c.phBandAng[k]<<"\t"<<l1c.phCode[k]<<endl;

      }

cout<<endl<<"dttf_ph_pt\t\t\tl1c.trWh\t\t\tl1c.trBx\t\t\tl1c.trTag\t\t\tl1c.trBx"<<endl;
    for(int l=0; l<l1c.trSize; l++){
          int ptpck = l1c.trPtPck[l];
                      dttf_ph_pt = (PCKtoPHYS[ptpck]);
		      std::cout<<dttf_ph_pt<<"\t\t\t"<<l1c.trWh[l]<<"\t\t\t"<<l1c.trBx[l]<<"\t\t\t"<<l1c.trTag[l]<<"\t\t\t"<<l1c.trBx[l]<<std::endl;
    }
    
std::cout<<"Track address"<<std::endl;
for(int kk =0; kk<8; kk++) {std::cout<<l1c.trAddress[kk]<<"  ";	if(kk==3) std::cout<<std::endl;}

std::cout<<std::endl;

}

for(int i=0; i<nentries; i++){
   l1c.GetEntry(i);
bool deb = false;
   if(l1c.trAddress[0]!=l1c.trAddress[4]) deb =true;
   if(l1c.trAddress[1]!=l1c.trAddress[5]) deb =true;
   if(l1c.trAddress[2]!=l1c.trAddress[6]) deb =true;
   if(l1c.trAddress[3]!=l1c.trAddress[7]) deb =true;

if(deb==true){


                cout<<"1c.phBxRAW[k]+<<l1c.Ts2Tag[k]<<<l1c.phSize<<<<l1c.phWh[k]<<<<l1c.phSt[k]<<<<l1c.phSe[k]<<<<l1c.phAng[k]<<<<l1c.phBandAng[k]<<<<l1c.phCode[k]"<<endl;

              for(int k=0; k<l1c.phSize; k++){
                cout<<l1c.phBxRAW[k]<<"\t\t\t"<<l1c.phTs2Tag[k]<<"\t\t\t"<<l1c.phSize<<"\t"<<l1c.phWh[k]<<"\t"<<l1c.phSt[k]<<"\t"<<l1c.phSe[k]<<"\t"<<l1c.phAng[k]<<"\t"<<l1c.phBandAng[k]<<"\t"<<l1c.phCode[k]<<endl;

      }

cout<<endl<<"dttf_ph_pt\t\t\tl1c.trWh\t\t\tl1c.trBx\t\t\tl1c.trTag\t\t\tl1c.trBx"<<endl;
    for(int l=0; l<l1c.trSize; l++){
          int ptpck = l1c.trPtPck[l];
                      dttf_ph_pt = (PCKtoPHYS[ptpck]);
                      std::cout<<dttf_ph_pt<<"\t\t\t"<<l1c.trWh[l]<<"\t\t\t"<<l1c.trBx[l]<<"\t\t\t"<<l1c.trTag[l]<<"\t\t\t"<<l1c.trBx[l]<<std::endl;
    }

std::cout<<"Track address"<<std::endl;
for(int kk =0; kk<8; kk++) {std::cout<<l1c.trAddress[kk]<<"  "; if(kk==3) std::cout<<std::endl;}

std::cout<<std::endl;



}



}

return 0;

}

