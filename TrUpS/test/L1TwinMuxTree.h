//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Aug  2 19:22:51 2016 by ROOT version 6.04/02
// from TTree L1Tree/L1Tree
// found on file: Ntuple_l1ttwinmux_data_run278063.root
//////////////////////////////////////////////////////////

#ifndef L1TwinMuxTree_h
#define L1TwinMuxTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class L1TwinMuxTree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
 //TrUpS::L1AnalysisTwinMuxDataFormat *TwinMux;
   Int_t           phSize;
   vector<int>     phBx;
   vector<int>     phWh;
   vector<int>     phSe;
   vector<int>     phSt;
   vector<float>   phAng;
   vector<float>   phBandAng;
   vector<int>     phCode;
   vector<int>     phTs2Tag;
   Int_t           thSize;
   vector<int>     thBx;
   vector<int>     thWh;
   vector<int>     thSe;
   vector<int>     thSt;
   vector<int>     thTheta;
   vector<int>     thCode;
   Int_t           rpcSize;
   vector<int>     rpcBx;
   vector<int>     rpcWh;
   vector<int>     rpcSe;
   vector<int>     rpcSt;
   vector<int>     rpcLayer;
   vector<int>     rpcStrip;
   Int_t           tmSize;
   vector<int>     tmBx;
   vector<int>     tmWh;
   vector<int>     tmSe;
   vector<int>     tmSt;
   vector<float>   tmAng;
   vector<float>   tmBandAng;
   vector<int>     tmCode;
   vector<int>     tmTs2Tag;
   vector<int>     tmRpcBit;

   // List of branches
   TBranch        *b_TwinMux_phSize;   //!
   TBranch        *b_TwinMux_phBx;   //!
   TBranch        *b_TwinMux_phWh;   //!
   TBranch        *b_TwinMux_phSe;   //!
   TBranch        *b_TwinMux_phSt;   //!
   TBranch        *b_TwinMux_phAng;   //!
   TBranch        *b_TwinMux_phBandAng;   //!
   TBranch        *b_TwinMux_phCode;   //!
   TBranch        *b_TwinMux_phTs2Tag;   //!
   TBranch        *b_TwinMux_thSize;   //!
   TBranch        *b_TwinMux_thBx;   //!
   TBranch        *b_TwinMux_thWh;   //!
   TBranch        *b_TwinMux_thSe;   //!
   TBranch        *b_TwinMux_thSt;   //!
   TBranch        *b_TwinMux_thTheta;   //!
   TBranch        *b_TwinMux_thCode;   //!
   TBranch        *b_TwinMux_rpcSize;   //!
   TBranch        *b_TwinMux_rpcBx;   //!
   TBranch        *b_TwinMux_rpcWh;   //!
   TBranch        *b_TwinMux_rpcSe;   //!
   TBranch        *b_TwinMux_rpcSt;   //!
   TBranch        *b_TwinMux_rpcLayer;   //!
   TBranch        *b_TwinMux_rpcStrip;   //!
   TBranch        *b_TwinMux_tmSize;   //!
   TBranch        *b_TwinMux_tmBx;   //!
   TBranch        *b_TwinMux_tmWh;   //!
   TBranch        *b_TwinMux_tmSe;   //!
   TBranch        *b_TwinMux_tmSt;   //!
   TBranch        *b_TwinMux_tmAng;   //!
   TBranch        *b_TwinMux_tmBandAng;   //!
   TBranch        *b_TwinMux_tmCode;   //!
   TBranch        *b_TwinMux_tmTs2Tag;   //!
   TBranch        *b_TwinMux_tmRpcBit;   //!

   L1TwinMuxTree(TTree *tree=0);
   virtual ~L1TwinMuxTree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   //virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};


L1TwinMuxTree::L1TwinMuxTree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   // if (tree == 0) {
   //    TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Ntuple_l1ttwinmux_data_run278063.root");
   //    if (!f || !f->IsOpen()) {
   //       f = new TFile("Ntuple_l1ttwinmux_data_run278063.root");
   //    }
   //    TDirectory * dir = (TDirectory*)f->Get("Ntuple_l1ttwinmux_data_run278063.root:/L1TwinMuxProducer");
   //    dir->GetObject("L1Tree",tree);

   // }
   Init(tree);
}

L1TwinMuxTree::~L1TwinMuxTree()
{
   //if (!fChain) return;
   //delete fChain->GetCurrentFile();
}

Int_t L1TwinMuxTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t L1TwinMuxTree::LoadTree(Long64_t entry)
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

void L1TwinMuxTree::Init(TTree *tree)
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

   fChain->SetBranchAddress("phSize", &phSize, &b_TwinMux_phSize);
   fChain->SetBranchAddress("phBx", &phBx, &b_TwinMux_phBx);
   fChain->SetBranchAddress("phWh", &phWh, &b_TwinMux_phWh);
   fChain->SetBranchAddress("phSe", &phSe, &b_TwinMux_phSe);
   fChain->SetBranchAddress("phSt", &phSt, &b_TwinMux_phSt);
   fChain->SetBranchAddress("phAng", &phAng, &b_TwinMux_phAng);
   fChain->SetBranchAddress("phBandAng", &phBandAng, &b_TwinMux_phBandAng);
   fChain->SetBranchAddress("phCode", &phCode, &b_TwinMux_phCode);
   fChain->SetBranchAddress("phTs2Tag", &phTs2Tag, &b_TwinMux_phTs2Tag);
   fChain->SetBranchAddress("thSize", &thSize, &b_TwinMux_thSize);
   fChain->SetBranchAddress("thBx", &thBx, &b_TwinMux_thBx);
   fChain->SetBranchAddress("thWh", &thWh, &b_TwinMux_thWh);
   fChain->SetBranchAddress("thSe", &thSe, &b_TwinMux_thSe);
   fChain->SetBranchAddress("thSt", &thSt, &b_TwinMux_thSt);
   fChain->SetBranchAddress("thTheta", &thTheta, &b_TwinMux_thTheta);
   fChain->SetBranchAddress("thCode", &thCode, &b_TwinMux_thCode);
   fChain->SetBranchAddress("rpcSize", &rpcSize, &b_TwinMux_rpcSize);
   fChain->SetBranchAddress("rpcBx", &rpcBx, &b_TwinMux_rpcBx);
   fChain->SetBranchAddress("rpcWh", &rpcWh, &b_TwinMux_rpcWh);
   fChain->SetBranchAddress("rpcSe", &rpcSe, &b_TwinMux_rpcSe);
   fChain->SetBranchAddress("rpcSt", &rpcSt, &b_TwinMux_rpcSt);
   fChain->SetBranchAddress("rpcLayer", &rpcLayer, &b_TwinMux_rpcLayer);
   fChain->SetBranchAddress("rpcStrip", &rpcStrip, &b_TwinMux_rpcStrip);
   fChain->SetBranchAddress("tmSize", &tmSize, &b_TwinMux_tmSize);
   fChain->SetBranchAddress("tmBx", &tmBx, &b_TwinMux_tmBx);
   fChain->SetBranchAddress("tmWh", &tmWh, &b_TwinMux_tmWh);
   fChain->SetBranchAddress("tmSe", &tmSe, &b_TwinMux_tmSe);
   fChain->SetBranchAddress("tmSt", &tmSt, &b_TwinMux_tmSt);
   fChain->SetBranchAddress("tmAng", &tmAng, &b_TwinMux_tmAng);
   fChain->SetBranchAddress("tmBandAng", &tmBandAng, &b_TwinMux_tmBandAng);
   fChain->SetBranchAddress("tmCode", &tmCode, &b_TwinMux_tmCode);
   fChain->SetBranchAddress("tmTs2Tag", &tmTs2Tag, &b_TwinMux_tmTs2Tag);
   fChain->SetBranchAddress("tmRpcBit", &tmRpcBit, &b_TwinMux_tmRpcBit);
   Notify();
}

Bool_t L1TwinMuxTree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void L1TwinMuxTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t L1TwinMuxTree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef L1TwinMuxTree_cxx
