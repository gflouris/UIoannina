//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Aug  9 17:32:16 2016 by ROOT version 6.06/01
// from TTree L1Tree/L1Tree
// found on file: Ntuples/Ntuple_l1ttwinmux_data_run278459.root
//////////////////////////////////////////////////////////

#ifndef L1BMTF_h
#define L1BMTF_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "UIoannina/TrUpS/interface/L1AnalysisBMTFDataFormat.h"

class L1BMTF {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
 //TrUpS::L1AnalysisBMTFDataFormat *BMTF;
   Int_t           phSize;
   vector<int>     phBx;
   vector<int>     phWh;
   vector<int>     phSe;
   vector<int>     phSt;
   vector<float>   phAng;
   vector<double>  phGlobPhi;
   vector<float>   phBandAng;
   vector<int>     phCode;
   vector<float>   phX;
   vector<float>   phY;
   vector<int>     phBxRAW;
   vector<int>     phTs2Tag;
   vector<int>     phRpcBit;
   Int_t           thSize;
   vector<int>     thBx;
   vector<int>     thWh;
   vector<int>     thSe;
   vector<int>     thSt;
   vector<float>   thX;
   vector<float>   thY;
   vector<int>     thTheta;
   vector<int>     thCode;
   Int_t           bmtfSize;
   vector<int>     bmtfPt;
   vector<int>     bmtfEta;
   vector<int>     bmtfPhi;
   vector<int>     bmtfqual;
   vector<int>     bmtfch;
   vector<int>     bmtfbx;
   vector<int>     bmtfprocessor;
   vector<int>     bmtftrAddress;
   vector<int>     bmtfwh;
   vector<int>     bmtfFineBit;

   // List of branches
   TBranch        *b_BMTF_phSize;   //!
   TBranch        *b_BMTF_phBx;   //!
   TBranch        *b_BMTF_phWh;   //!
   TBranch        *b_BMTF_phSe;   //!
   TBranch        *b_BMTF_phSt;   //!
   TBranch        *b_BMTF_phAng;   //!
   TBranch        *b_BMTF_phGlobPhi;   //!
   TBranch        *b_BMTF_phBandAng;   //!
   TBranch        *b_BMTF_phCode;   //!
   TBranch        *b_BMTF_phX;   //!
   TBranch        *b_BMTF_phY;   //!
   TBranch        *b_BMTF_phBxRAW;   //!
   TBranch        *b_BMTF_phTs2Tag;   //!
   TBranch        *b_BMTF_phRpcBit;   //!
   TBranch        *b_BMTF_thSize;   //!
   TBranch        *b_BMTF_thBx;   //!
   TBranch        *b_BMTF_thWh;   //!
   TBranch        *b_BMTF_thSe;   //!
   TBranch        *b_BMTF_thSt;   //!
   TBranch        *b_BMTF_thX;   //!
   TBranch        *b_BMTF_thY;   //!
   TBranch        *b_BMTF_thTheta;   //!
   TBranch        *b_BMTF_thCode;   //!
   TBranch        *b_BMTF_bmtfSize;   //!
   TBranch        *b_BMTF_bmtfPt;   //!
   TBranch        *b_BMTF_bmtfEta;   //!
   TBranch        *b_BMTF_bmtfPhi;   //!
   TBranch        *b_BMTF_bmtfqual;   //!
   TBranch        *b_BMTF_bmtfch;   //!
   TBranch        *b_BMTF_bmtfbx;   //!
   TBranch        *b_BMTF_bmtfprocessor;   //!
   TBranch        *b_BMTF_bmtftrAddress;   //!
   TBranch        *b_BMTF_bmtfwh;   //!
   TBranch        *b_BMTF_bmtfFineBit;   //!

   L1BMTF(TTree *tree=0);
   virtual ~L1BMTF();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   //virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};


L1BMTF::L1BMTF(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   // if (tree == 0) {
   //    TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Ntuples/Ntuple_l1ttwinmux_data_run278459.root");
   //    if (!f || !f->IsOpen()) {
   //       f = new TFile("Ntuples/Ntuple_l1ttwinmux_data_run278459.root");
   //    }
   //    TDirectory * dir = (TDirectory*)f->Get("Ntuples/Ntuple_l1ttwinmux_data_run278459.root:/L1TProducer");
   //    dir->GetObject("L1Tree",tree);

   // }
   // Init(tree);
}

L1BMTF::~L1BMTF()
{
   if (!fChain) return;
   //delete fChain->GetCurrentFile();
}

Int_t L1BMTF::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t L1BMTF::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void L1BMTF::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("phSize", &phSize, &b_BMTF_phSize);
   fChain->SetBranchAddress("phBx", &phBx, &b_BMTF_phBx);
   fChain->SetBranchAddress("phWh", &phWh, &b_BMTF_phWh);
   fChain->SetBranchAddress("phSe", &phSe, &b_BMTF_phSe);
   fChain->SetBranchAddress("phSt", &phSt, &b_BMTF_phSt);
   fChain->SetBranchAddress("phAng", &phAng, &b_BMTF_phAng);
   fChain->SetBranchAddress("phGlobPhi", &phGlobPhi, &b_BMTF_phGlobPhi);
   fChain->SetBranchAddress("phBandAng", &phBandAng, &b_BMTF_phBandAng);
   fChain->SetBranchAddress("phCode", &phCode, &b_BMTF_phCode);
   fChain->SetBranchAddress("phX", &phX, &b_BMTF_phX);
   fChain->SetBranchAddress("phY", &phY, &b_BMTF_phY);
   fChain->SetBranchAddress("phBxRAW", &phBxRAW, &b_BMTF_phBxRAW);
   fChain->SetBranchAddress("phTs2Tag", &phTs2Tag, &b_BMTF_phTs2Tag);
   fChain->SetBranchAddress("phRpcBit", &phRpcBit, &b_BMTF_phRpcBit);
   fChain->SetBranchAddress("thSize", &thSize, &b_BMTF_thSize);
   fChain->SetBranchAddress("thBx", &thBx, &b_BMTF_thBx);
   fChain->SetBranchAddress("thWh", &thWh, &b_BMTF_thWh);
   fChain->SetBranchAddress("thSe", &thSe, &b_BMTF_thSe);
   fChain->SetBranchAddress("thSt", &thSt, &b_BMTF_thSt);
   fChain->SetBranchAddress("thX", &thX, &b_BMTF_thX);
   fChain->SetBranchAddress("thY", &thY, &b_BMTF_thY);
   fChain->SetBranchAddress("thTheta", &thTheta, &b_BMTF_thTheta);
   fChain->SetBranchAddress("thCode", &thCode, &b_BMTF_thCode);
   fChain->SetBranchAddress("bmtfSize", &bmtfSize, &b_BMTF_bmtfSize);
   fChain->SetBranchAddress("bmtfPt", &bmtfPt, &b_BMTF_bmtfPt);
   fChain->SetBranchAddress("bmtfEta", &bmtfEta, &b_BMTF_bmtfEta);
   fChain->SetBranchAddress("bmtfPhi", &bmtfPhi, &b_BMTF_bmtfPhi);
   fChain->SetBranchAddress("bmtfqual", &bmtfqual, &b_BMTF_bmtfqual);
   fChain->SetBranchAddress("bmtfch", &bmtfch, &b_BMTF_bmtfch);
   fChain->SetBranchAddress("bmtfbx", &bmtfbx, &b_BMTF_bmtfbx);
   fChain->SetBranchAddress("bmtfprocessor", &bmtfprocessor, &b_BMTF_bmtfprocessor);
   fChain->SetBranchAddress("bmtftrAddress", &bmtftrAddress, &b_BMTF_bmtftrAddress);
   fChain->SetBranchAddress("bmtfwh", &bmtfwh, &b_BMTF_bmtfwh);
   fChain->SetBranchAddress("bmtfFineBit", &bmtfFineBit, &b_BMTF_bmtfFineBit);
   Notify();
}

Bool_t L1BMTF::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void L1BMTF::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t L1BMTF::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef L1BMTF_cxx
