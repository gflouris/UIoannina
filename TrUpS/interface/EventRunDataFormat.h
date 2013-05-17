#ifndef __TrUpS_EventRunDataFormat_H__
#define __TrUpS_EventRunDataFormat_H__

//-------------------------------------------------------------------------------
// Created 17/05/2013 G. Flouris
// 
//  
// Original code : 
//-------------------------------------------------------------------------------

#include <vector>
#include "TMatrixD.h"


namespace TrUpS
{
  struct EventRunDataFormat
  {

    EventRunDataFormat(){Reset();};
    ~EventRunDataFormat(){};
    
    void Reset()
    {
    pvertex=0;
    }

    int  pvertex;


  }; 
} 
#endif


