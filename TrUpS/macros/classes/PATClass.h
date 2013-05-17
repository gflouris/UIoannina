//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Mar 11 14:10:10 2013 by ROOT version 5.32/00
// from TTree PATTree/PATTree
// found on file: /mnt/storage/shared/DTTFStudies_reco.root
//////////////////////////////////////////////////////////

#ifndef PATClass_h
#define PATClass_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class PATClass {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
 //TrUpS::PATMuonDataFormat *PATMuons;
   vector<float>   patPt_Mu;
   vector<float>   patPhi_Mu;
   vector<float>   patEta_Mu;
   vector<float>   patStatus_Mu;

   // List of branches
   TBranch        *b_PATMuons_patPt_Mu;   //!
   TBranch        *b_PATMuons_patPhi_Mu;   //!
   TBranch        *b_PATMuons_patEta_Mu;   //!
   TBranch        *b_PATMuons_patStatus_Mu;   //!

   PATClass(TTree *tree=0);
   virtual ~PATClass();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef PATClass_cxx
PATClass::PATClass(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
//    if (tree == 0) {
//       TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/mnt/storage/shared/DTTFStudies_reco.root");
//       if (!f || !f->IsOpen()) {
//          f = new TFile("/mnt/storage/shared/DTTFStudies_reco.root");
//       }
//       TDirectory * dir = (TDirectory*)f->Get("/mnt/storage/shared/DTTFStudies_reco.root:/PATTProducer");
//       dir->GetObject("PATTree",tree);
// 
//    }
   Init(tree);
}

PATClass::~PATClass()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t PATClass::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t PATClass::LoadTree(Long64_t entry)
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

void PATClass::Init(TTree *tree)
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

   fChain->SetBranchAddress("patPt_Mu", &patPt_Mu, &b_PATMuons_patPt_Mu);
   fChain->SetBranchAddress("patPhi_Mu", &patPhi_Mu, &b_PATMuons_patPhi_Mu);
   fChain->SetBranchAddress("patEta_Mu", &patEta_Mu, &b_PATMuons_patEta_Mu);
   fChain->SetBranchAddress("patStatus_Mu", &patStatus_Mu, &b_PATMuons_patStatus_Mu);
   Notify();
}

Bool_t PATClass::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void PATClass::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t PATClass::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef PATClass_cxx
