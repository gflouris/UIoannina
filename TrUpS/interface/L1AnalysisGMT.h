#ifndef __TrUpS_L1AnalysisGMT_H__
#define __TrUpS_L1AnalysisGMT_H__

//-------------------------------------------------------------------------------
// 
// 
//
// Original code : 
//-------------------------------------------------------------------------------

#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "L1AnalysisGMTDataFormat.h"

namespace TrUpS
{
  class L1AnalysisGMT
  {
  public:
    L1AnalysisGMT();
    ~L1AnalysisGMT();
    
    void SetGMT(const L1MuGMTReadoutCollection* gmtrc);	
    L1AnalysisGMTDataFormat * getData() {return &gmt_;}
    void Reset() {gmt_.Reset();}
  
  private :
    L1AnalysisGMTDataFormat gmt_;	   		      
  }; 
} 
#endif


