//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Mar 19 18:52:50 2013 by ROOT version 5.32/00
// from TTree RECOTree/RECOTree
// found on file: /mnt/storage/shared/DTTFStudies_reco_withgmt.root
//////////////////////////////////////////////////////////

#ifndef RECOClass_h
#define RECOClass_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class RECOClass {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
 //TrUpS::RecoMuonDataFormat *RECOMuons;
   vector<float>   recoPt_Mu;
   vector<float>   recoPhi_Mu;
   vector<float>   recoEta_Mu;
   vector<float>   recoStatus_Mu;
   vector<bool>    isTight_Mu;
   vector<bool>    isLoose_Mu;
   vector<bool>    isQuality_Valid_Mu;
   vector<bool>    isMuon;
   vector<bool>    isGlobal;
   vector<bool>    isTracker;
   vector<bool>    isCalo;
   vector<bool>    isPF;
   Int_t           reco_muons;

   // List of branches
   TBranch        *b_RECOMuons_recoPt_Mu;   //!
   TBranch        *b_RECOMuons_recoPhi_Mu;   //!
   TBranch        *b_RECOMuons_recoEta_Mu;   //!
   TBranch        *b_RECOMuons_recoStatus_Mu;   //!
   TBranch        *b_RECOMuons_isTight_Mu;   //!
   TBranch        *b_RECOMuons_isLoose_Mu;   //!
   TBranch        *b_RECOMuons_isQuality_Valid_Mu;   //!
   TBranch        *b_RECOMuons_isMuon;   //!
   TBranch        *b_RECOMuons_isGlobal;   //!
   TBranch        *b_RECOMuons_isTracker;   //!
   TBranch        *b_RECOMuons_isCalo;   //!
   TBranch        *b_RECOMuons_isPF;   //!
   TBranch        *b_RECOMuons_reco_muons;   //!

   RECOClass(TTree *tree=0);
   virtual ~RECOClass();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef RECOClass_cxx
RECOClass::RECOClass(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
//    if (tree == 0) {
//       TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/mnt/storage/shared/DTTFStudies_reco_withgmt.root");
//       if (!f || !f->IsOpen()) {
//          f = new TFile("/mnt/storage/shared/DTTFStudies_reco_withgmt.root");
//       }
//       TDirectory * dir = (TDirectory*)f->Get("/mnt/storage/shared/DTTFStudies_reco_withgmt.root:/RECOTProducer");
//       dir->GetObject("RECOTree",tree);
// 
//    }
   Init(tree);
}

RECOClass::~RECOClass()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t RECOClass::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t RECOClass::LoadTree(Long64_t entry)
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

void RECOClass::Init(TTree *tree)
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

   fChain->SetBranchAddress("recoPt_Mu", &recoPt_Mu, &b_RECOMuons_recoPt_Mu);
   fChain->SetBranchAddress("recoPhi_Mu", &recoPhi_Mu, &b_RECOMuons_recoPhi_Mu);
   fChain->SetBranchAddress("recoEta_Mu", &recoEta_Mu, &b_RECOMuons_recoEta_Mu);
   fChain->SetBranchAddress("recoStatus_Mu", &recoStatus_Mu, &b_RECOMuons_recoStatus_Mu);
   fChain->SetBranchAddress("isTight_Mu", &isTight_Mu, &b_RECOMuons_isTight_Mu);
   fChain->SetBranchAddress("isLoose_Mu", &isLoose_Mu, &b_RECOMuons_isLoose_Mu);
   fChain->SetBranchAddress("isQuality_Valid_Mu", &isQuality_Valid_Mu, &b_RECOMuons_isQuality_Valid_Mu);
   fChain->SetBranchAddress("isMuon", &isMuon, &b_RECOMuons_isMuon);
   fChain->SetBranchAddress("isGlobal", &isGlobal, &b_RECOMuons_isGlobal);
   fChain->SetBranchAddress("isTracker", &isTracker, &b_RECOMuons_isTracker);
   fChain->SetBranchAddress("isCalo", &isCalo, &b_RECOMuons_isCalo);
   fChain->SetBranchAddress("isPF", &isPF, &b_RECOMuons_isPF);
   fChain->SetBranchAddress("reco_muons", &reco_muons, &b_RECOMuons_reco_muons);
   Notify();
}

Bool_t RECOClass::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void RECOClass::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t RECOClass::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef RECOClass_cxx
