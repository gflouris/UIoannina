//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Jul 12 16:24:04 2015 by ROOT version 6.02/05
// from TTree L1Tree/L1Tree
// found on file: ../test/Tree_from_RAW_200events_locally_cmssw_LUTS_lin.root
//////////////////////////////////////////////////////////

#ifndef L1ClassDTBM_h
#define L1ClassDTBM_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "UIoannina/TrUpS/interface/L1AnalysisGMTDataFormat.h"
#include "UIoannina/TrUpS/interface/L1AnalysisDTTFDataFormat.h"

class L1ClassDTBM {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

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
 //TrUpS::L1AnalysisDTTFDataFormat *DTTF;
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
   Int_t           thSize;
   vector<int>     thBx;
   vector<int>     thWh;
   vector<int>     thSe;
   vector<int>     thSt;
   vector<float>   thX;
   vector<float>   thY;
   TMatrixT<double> thTheta;
   TMatrixT<double> thCode;
   Int_t           trSize;
   vector<int>     trBx;
   vector<int>     trTag;
   vector<int>     trQual;
   vector<int>     trPtPck;
   vector<float>   trPtVal;
   vector<int>     trPhiPck;
   vector<float>   trPhiVal;
   vector<int>     trEtaPck;
   vector<float>   trEtaVal;
   vector<double>  trPhiGlob;
   vector<int>     trChPck;
   vector<int>     trWh;
   vector<int>     trSc;
   vector<unsigned int> trAddress;
   Int_t           trmbSize;
   vector<int>     trmbBx;
   vector<int>     trmbTag;
   vector<int>     trmbQual;
   vector<int>     trmbPtPck;
   vector<int>     trmbPhiPck;
   vector<int>     trmbEtaPck;
   vector<double>  trmbPhiGlob;
   vector<int>     trmbChPck;
   vector<int>     trmbWh;
   vector<int>     trmbSc;
   vector<unsigned int> trmbAddress;

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
   TBranch        *b_DTTF_phSize;   //!
   TBranch        *b_DTTF_phBx;   //!
   TBranch        *b_DTTF_phWh;   //!
   TBranch        *b_DTTF_phSe;   //!
   TBranch        *b_DTTF_phSt;   //!
   TBranch        *b_DTTF_phAng;   //!
   TBranch        *b_DTTF_phGlobPhi;   //!
   TBranch        *b_DTTF_phBandAng;   //!
   TBranch        *b_DTTF_phCode;   //!
   TBranch        *b_DTTF_phX;   //!
   TBranch        *b_DTTF_phY;   //!
   TBranch        *b_DTTF_phBxRAW;   //!
   TBranch        *b_DTTF_phTs2Tag;   //!
   TBranch        *b_DTTF_thSize;   //!
   TBranch        *b_DTTF_thBx;   //!
   TBranch        *b_DTTF_thWh;   //!
   TBranch        *b_DTTF_thSe;   //!
   TBranch        *b_DTTF_thSt;   //!
   TBranch        *b_DTTF_thX;   //!
   TBranch        *b_DTTF_thY;   //!
   TBranch        *b_DTTF_thTheta;   //!
   TBranch        *b_DTTF_thCode;   //!
   TBranch        *b_DTTF_trSize;   //!
   TBranch        *b_DTTF_trBx;   //!
   TBranch        *b_DTTF_trTag;   //!
   TBranch        *b_DTTF_trQual;   //!
   TBranch        *b_DTTF_trPtPck;   //!
   TBranch        *b_DTTF_trPtVal;   //!
   TBranch        *b_DTTF_trPhiPck;   //!
   TBranch        *b_DTTF_trPhiVal;   //!
   TBranch        *b_DTTF_trEtaPck;   //!
   TBranch        *b_DTTF_trEtaVal;   //!
   TBranch        *b_DTTF_trPhiGlob;   //!
   TBranch        *b_DTTF_trChPck;   //!
   TBranch        *b_DTTF_trWh;   //!
   TBranch        *b_DTTF_trSc;   //!
   TBranch        *b_DTTF_trAddress;   //!
   TBranch        *b_DTTF_trmbSize;   //!
   TBranch        *b_DTTF_trmbBx;   //!
   TBranch        *b_DTTF_trmbTag;   //!
   TBranch        *b_DTTF_trmbQual;   //!
   TBranch        *b_DTTF_trmbPtPck;   //!
   TBranch        *b_DTTF_trmbPhiPck;   //!
   TBranch        *b_DTTF_trmbEtaPck;   //!
   TBranch        *b_DTTF_trmbPhiGlob;   //!
   TBranch        *b_DTTF_trmbChPck;   //!
   TBranch        *b_DTTF_trmbWh;   //!
   TBranch        *b_DTTF_trmbSc;   //!
   TBranch        *b_DTTF_trmbAddress;   //!

   L1ClassDTBM(TTree *tree=0);
   virtual ~L1ClassDTBM();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef L1ClassDTBM_cxx
L1ClassDTBM::L1ClassDTBM(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
//    if (tree == 0) {
//       TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../test/Tree_from_RAW_200events_locally_cmssw_LUTS_lin.root");
//       if (!f || !f->IsOpen()) {
//          f = new TFile("../test/Tree_from_RAW_200events_locally_cmssw_LUTS_lin.root");
//       }
//       TDirectory * dir = (TDirectory*)f->Get("../test/Tree_from_RAW_200events_locally_cmssw_LUTS_lin.root:/L1TProducer");
//       dir->GetObject("L1Tree",tree);
// 
//    }
   Init(tree);
}

L1ClassDTBM::~L1ClassDTBM()
{
   if (!fChain) return;
   //delete fChain->GetCurrentFile();
}

Int_t L1ClassDTBM::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t L1ClassDTBM::LoadTree(Long64_t entry)
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

void L1ClassDTBM::Init(TTree *tree)
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
   fChain->SetBranchAddress("phSize", &phSize, &b_DTTF_phSize);
   fChain->SetBranchAddress("phBx", &phBx, &b_DTTF_phBx);
   fChain->SetBranchAddress("phWh", &phWh, &b_DTTF_phWh);
   fChain->SetBranchAddress("phSe", &phSe, &b_DTTF_phSe);
   fChain->SetBranchAddress("phSt", &phSt, &b_DTTF_phSt);
   fChain->SetBranchAddress("phAng", &phAng, &b_DTTF_phAng);
   fChain->SetBranchAddress("phGlobPhi", &phGlobPhi, &b_DTTF_phGlobPhi);
   fChain->SetBranchAddress("phBandAng", &phBandAng, &b_DTTF_phBandAng);
   fChain->SetBranchAddress("phCode", &phCode, &b_DTTF_phCode);
   fChain->SetBranchAddress("phX", &phX, &b_DTTF_phX);
   fChain->SetBranchAddress("phY", &phY, &b_DTTF_phY);
   fChain->SetBranchAddress("phBxRAW", &phBxRAW, &b_DTTF_phBxRAW);
   fChain->SetBranchAddress("phTs2Tag", &phTs2Tag, &b_DTTF_phTs2Tag);
   fChain->SetBranchAddress("thSize", &thSize, &b_DTTF_thSize);
   fChain->SetBranchAddress("thBx", &thBx, &b_DTTF_thBx);
   fChain->SetBranchAddress("thWh", &thWh, &b_DTTF_thWh);
   fChain->SetBranchAddress("thSe", &thSe, &b_DTTF_thSe);
   fChain->SetBranchAddress("thSt", &thSt, &b_DTTF_thSt);
   fChain->SetBranchAddress("thX", &thX, &b_DTTF_thX);
   fChain->SetBranchAddress("thY", &thY, &b_DTTF_thY);
   fChain->SetBranchAddress("thTheta", &thTheta, &b_DTTF_thTheta);
   fChain->SetBranchAddress("thCode", &thCode, &b_DTTF_thCode);
   fChain->SetBranchAddress("trSize", &trSize, &b_DTTF_trSize);
   fChain->SetBranchAddress("trBx", &trBx, &b_DTTF_trBx);
   fChain->SetBranchAddress("trTag", &trTag, &b_DTTF_trTag);
   fChain->SetBranchAddress("trQual", &trQual, &b_DTTF_trQual);
   fChain->SetBranchAddress("trPtPck", &trPtPck, &b_DTTF_trPtPck);
   fChain->SetBranchAddress("trPtVal", &trPtVal, &b_DTTF_trPtVal);
   fChain->SetBranchAddress("trPhiPck", &trPhiPck, &b_DTTF_trPhiPck);
   fChain->SetBranchAddress("trPhiVal", &trPhiVal, &b_DTTF_trPhiVal);
   fChain->SetBranchAddress("trEtaPck", &trEtaPck, &b_DTTF_trEtaPck);
   fChain->SetBranchAddress("trEtaVal", &trEtaVal, &b_DTTF_trEtaVal);
   fChain->SetBranchAddress("trPhiGlob", &trPhiGlob, &b_DTTF_trPhiGlob);
   fChain->SetBranchAddress("trChPck", &trChPck, &b_DTTF_trChPck);
   fChain->SetBranchAddress("trWh", &trWh, &b_DTTF_trWh);
   fChain->SetBranchAddress("trSc", &trSc, &b_DTTF_trSc);
   fChain->SetBranchAddress("trAddress", &trAddress, &b_DTTF_trAddress);
   fChain->SetBranchAddress("trmbSize", &trmbSize, &b_DTTF_trmbSize);
   fChain->SetBranchAddress("trmbBx", &trmbBx, &b_DTTF_trmbBx);
   fChain->SetBranchAddress("trmbTag", &trmbTag, &b_DTTF_trmbTag);
   fChain->SetBranchAddress("trmbQual", &trmbQual, &b_DTTF_trmbQual);
   fChain->SetBranchAddress("trmbPtPck", &trmbPtPck, &b_DTTF_trmbPtPck);
   fChain->SetBranchAddress("trmbPhiPck", &trmbPhiPck, &b_DTTF_trmbPhiPck);
   fChain->SetBranchAddress("trmbEtaPck", &trmbEtaPck, &b_DTTF_trmbEtaPck);
   fChain->SetBranchAddress("trmbPhiGlob", &trmbPhiGlob, &b_DTTF_trmbPhiGlob);
   fChain->SetBranchAddress("trmbChPck", &trmbChPck, &b_DTTF_trmbChPck);
   fChain->SetBranchAddress("trmbWh", &trmbWh, &b_DTTF_trmbWh);
   fChain->SetBranchAddress("trmbSc", &trmbSc, &b_DTTF_trmbSc);
   fChain->SetBranchAddress("trmbAddress", &trmbAddress, &b_DTTF_trmbAddress);
   Notify();
}

Bool_t L1ClassDTBM::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void L1ClassDTBM::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t L1ClassDTBM::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef L1ClassDTBM_cxx
