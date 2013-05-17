#ifndef __TrUpS_RecoMuonDataFormat_H__
#define __TrUpS_RecoMuonDataFormat_H__

//-------------------------------------------------------------------------------
// Created 07/03/2013 G. Flouris
// 
//  
// Original code : 
//-------------------------------------------------------------------------------

#include <vector>
#include "TMatrixD.h"


namespace TrUpS
{
  struct RecoMuonDataFormat
  {

    RecoMuonDataFormat(){Reset();};
    ~RecoMuonDataFormat(){};
    
    void Reset()
    {


    recoPt_Mu.clear();
    recoEta_Mu.clear();
    recoPhi_Mu.clear();
    recoStatus_Mu.clear();
    isTight_Mu.clear();
    isLoose_Mu.clear();
    isQuality_Valid_Mu.clear();
    isMuon.clear();
    isGlobal.clear();
    isTracker.clear();
    isCalo.clear();
    isPF.clear();
    reco_muons=0;
    }
      
    std::vector<float> recoPt_Mu;
    std::vector<float> recoPhi_Mu;
    std::vector<float> recoEta_Mu;
    std::vector<float> recoStatus_Mu;
    std::vector<bool>  isTight_Mu, isLoose_Mu;
    std::vector<bool>  isQuality_Valid_Mu;
    std::vector<bool>  isMuon;
    std::vector<bool>  isGlobal;
    std::vector<bool>  isTracker;
    std::vector<bool>  isCalo ;
    std::vector<bool>  isPF;
    int  reco_muons;



  }; 
} 
#endif


