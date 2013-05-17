#ifndef __TrUpS_PATMuonDataFormat_H
#define __TrUpS_PATMuonDataFormat_H__

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
  struct PATMuonDataFormat
  {

    PATMuonDataFormat(){Reset();};
    ~PATMuonDataFormat(){};
    
    void Reset()
    {


    patPt_Mu.clear();
    patEta_Mu.clear();
    patPhi_Mu.clear();
    patStatus_Mu.clear();
    isTight_Mu.clear();
    isLoose_Mu.clear();
    pat_muons = 0;
  //  ispatTight_Mu.clear();
    }
      
    std::vector<float> patPt_Mu;
    std::vector<float> patPhi_Mu;
    std::vector<float> patEta_Mu;
    std::vector<float> patStatus_Mu;
    std::vector<bool>  isTight_Mu, isLoose_Mu;
    int			pat_muons;
 //   std::vector<bool>  ispatTight_Mu;

  }; 
} 
#endif


