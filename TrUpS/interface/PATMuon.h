#ifndef __TrUpS_PATMuon_H__
#define __TrUpS_PATMuon_H__

//-------------------------------------------------------------------------------
// Created 07/03/2013 - G. Flouris
// 
//  
// Original code : 
//-------------------------------------------------------------------------------

#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TFile.h"
#include "TH1F.h"
#include "PATMuonDataFormat.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"


namespace TrUpS
{
  class PATMuon 
  {
  public:
    PATMuon();
    ~PATMuon();

    void SetPAT(const edm::Event & event, const edm::EventSetup& eventSetup);
    void Reset() {patmu_.Reset();}
    PATMuonDataFormat * getData() {return &patmu_;}


  private : 
    PATMuonDataFormat patmu_;
  }; 
} 
#endif



// class L1TriggerPAT : public edm::EDAnalyzer 
// {
//   public:
//     explicit L1TriggerPAT(edm::ParameterSet const& cfg);
//     virtual void beginJob();
//     virtual void analyze(edm::Event const& iEvent, edm::EventSetup const& iSetup);
//     virtual void endJob();
//     virtual ~L1TriggerPAT();
// 
//   private:  
//     //---- configurable parameters --------   
//   //  bool isMC_;
//    // double etaMax_,ptMin_,htMin_,betaMin_;
//     edm::InputTag srcMuons_;
// //    edm::Service<TFileService> fs_;
//     TH1F *hPtrec;
//     TH1F *hEtarec;     
//     TH1F *hPhirec;     
//     edm::Handle<edm::TriggerResults> trigResults; //our trigger result object
//     HLTConfigProvider hltConfig;
//  
// };
// 
// #endif
