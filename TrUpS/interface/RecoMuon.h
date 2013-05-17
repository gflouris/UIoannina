#ifndef __TrUpS_RecoMuon_H__
#define __TrUpS_RecoMuon_H__

//-------------------------------------------------------------------------------
// Created 07/03/2013 - G. Flouris
// 
//  
// Original code : 
//-------------------------------------------------------------------------------

#include "DataFormats/Common/interface/Handle.h"

#include "RecoMuonDataFormat.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"


namespace TrUpS
{
  class RecoMuon 
  {
  public:
    RecoMuon();
    ~RecoMuon();

    void SetReco(const edm::Event& , const edm::EventSetup&);
    void Reset() {recomu_.Reset();}
    RecoMuonDataFormat * getData() {return &recomu_;}

  private : 
    RecoMuonDataFormat recomu_;
  }; 
} 
#endif


