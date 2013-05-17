//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Mar 19 17:46:42 2013 by ROOT version 5.28/00h
// from TTree L1Tree/L1Tree
// found on file: ./DTTFStudies_reco_withgmt.root
//////////////////////////////////////////////////////////

#ifndef L1Class_h
#define L1Class_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class L1Class {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
 //TrUpS::L1AnalysisGMTDataFormat *GMT;
   Int_t           EvBx;
   Int_t           gmt_muons;
   vector<int>     Bx;
   vector<int>     Quality;
   vector<float>   Pt;
   vector<float>   Eta;
   vector<float>   Phi;
   vector<int>     Charge;
   vector<bool>    Charge_Valid;
   vector<bool>    Isol;
   vector<bool>    IsMatchedCand;
   vector<bool>    IsHaloCand;
   vector<bool>    Mip;

   // List of branches
   TBranch        *b_GMT_EvBx;   //!
   TBranch        *b_GMT_gmt_muons;   //!
   TBranch        *b_GMT_Bx;   //!
   TBranch        *b_GMT_Quality;   //!
   TBranch        *b_GMT_Pt;   //!
   TBranch        *b_GMT_Eta;   //!
   TBranch        *b_GMT_Phi;   //!
   TBranch        *b_GMT_Charge;   //!
   TBranch        *b_GMT_Charge_Valid;   //!
   TBranch        *b_GMT_Isol;   //!
   TBranch        *b_GMT_IsMatchedCand;   //!
   TBranch        *b_GMT_IsHaloCand;   //!
   TBranch        *b_GMT_Mip;   //!

   L1Class(TTree *tree=0);
   virtual ~L1Class();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef L1Class_cxx
L1Class::L1Class(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
//    if (tree == 0) {
//       TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/mnt/storage/shared/DTTFStudies_reco_withgmt.root");
//       if (!f) {
//          f = new TFile("/mnt/storage/shared/DTTFStudies_reco_withgmt.root");
//          f->cd("/mnt/storage/shared/DTTFStudies_reco_withgmt.root:/L1TProducer");
//       }
//      tree = (TTree*)gDirectory->Get("L1Tree");

//   }
   Init(tree);
}

L1Class::~L1Class()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t L1Class::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t L1Class::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void L1Class::Init(TTree *tree)
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

   fChain->SetBranchAddress("EvBx", &EvBx, &b_GMT_EvBx);
   fChain->SetBranchAddress("gmt_muons", &gmt_muons, &b_GMT_gmt_muons);
   fChain->SetBranchAddress("Bx", &Bx, &b_GMT_Bx);
   fChain->SetBranchAddress("Quality", &Quality, &b_GMT_Quality);
   fChain->SetBranchAddress("Pt", &Pt, &b_GMT_Pt);
   fChain->SetBranchAddress("Eta", &Eta, &b_GMT_Eta);
   fChain->SetBranchAddress("Phi", &Phi, &b_GMT_Phi);
   fChain->SetBranchAddress("Charge", &Charge, &b_GMT_Charge);
   fChain->SetBranchAddress("Charge_Valid", &Charge_Valid, &b_GMT_Charge_Valid);
   fChain->SetBranchAddress("Isol", &Isol, &b_GMT_Isol);
   fChain->SetBranchAddress("IsMatchedCand", &IsMatchedCand, &b_GMT_IsMatchedCand);
   fChain->SetBranchAddress("IsHaloCand", &IsHaloCand, &b_GMT_IsHaloCand);
   fChain->SetBranchAddress("Mip", &Mip, &b_GMT_Mip);
   Notify();
}

Bool_t L1Class::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void L1Class::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t L1Class::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef L1Class_cxx
