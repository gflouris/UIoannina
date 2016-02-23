#ifndef __TrUpS_L1AnalysisBMTFDataFormat_H__
#define __TrUpS_L1AnalysisBMTFDataFormat_H__

//-------------------------------------------------------------------------------
// Created 16/04/2010 - E. Conte, A.C. Le Bihan
//
//
// Original code : UserCode/L1TriggerDPG/L1NtupleProducer
//-------------------------------------------------------------------------------

#include <vector>
#include "TMatrixD.h"
#include <string>

namespace TrUpS
{
  struct L1AnalysisBMTFDataFormat
  {

    L1AnalysisBMTFDataFormat(){Reset();};
    ~L1AnalysisBMTFDataFormat(){};

    void Reset()
    {

    phSize = 0;

    phBx.clear();
    phWh.clear();
    phSe.clear();
    phSt.clear();
    phAng.clear();
    phGlobPhi.clear(); ///
    phBandAng.clear();
    phCode.clear();
    phX.clear();
    phY.clear();
    phBxRAW.clear();
    phTs2Tag.clear();


    thSize = 0;

    thBx.clear();
    thWh.clear();
    thSe.clear();
    thSt.clear();
    thX.clear();
    thY.clear();
    thCode.clear();
    thTheta.clear();

    bmtfSize = 0;
    bmtfPt.clear();
    bmtfEta.clear();
    bmtfPhi.clear();
    bmtfqual.clear();
    bmtfch.clear();
    bmtfbx.clear();
    bmtfprocessor.clear();
    bmtftrAddress.clear();
    bmtfwh.clear();
    bmtfFineBit.clear();

    trmbSize = 0;
    trmbPt.clear();
    trmbEta.clear();
    trmbPhi.clear();
    trmbqual.clear();
    trmbch.clear();
    trmbbx.clear();
    trmbprocessor.clear();
    trmbtrAddress.clear();
    trmbwh.clear();
    trmbFineBit.clear();
  /*  trmbSize = 0;
    trmbBx.clear();
    trmbTag.clear();
    trmbQual.clear();
    trmbPtPck.clear();
    trmbPhiPck.clear();
    trmbEtaPck.clear();
    trmbPhiGlob.clear();
    trmbChPck.clear();
    trmbWh.clear();
    trmbSc.clear();
    trmbAddress.clear();*/


    }

    // ---- L1AnalysisBMTFDataFormat information.

    int phSize;
    std::vector<int>    phBx;
    std::vector<int>    phWh;
    std::vector<int>    phSe;
    std::vector<int>    phSt;
    std::vector<float>  phAng;
    std::vector<double> phGlobPhi;
    std::vector<float>  phBandAng;
    std::vector<int>    phCode;
    std::vector<float>  phX;
    std::vector<float>  phY;
    std::vector<int>  phBxRAW;
    std::vector<int>  phTs2Tag;


    int thSize;
    std::vector<int>   thBx;
    std::vector<int>   thWh;
    std::vector<int>   thSe;
    std::vector<int>   thSt;
    std::vector<float> thX;
    std::vector<float> thY;

   // TMatrixD thTheta;
   // TMatrixD thCode;
    std::vector<int> thTheta;
    std::vector<int> thCode; 
 
    int bmtfSize;
    std::vector<int> bmtfPt;
    std::vector<int> bmtfEta;
    std::vector<int> bmtfPhi;
    std::vector<int> bmtfqual;
    std::vector<int> bmtfch;
    std::vector<int> bmtfbx;
    std::vector<int> bmtfprocessor;
    std::vector<int> bmtftrAddress;
    std::vector<int> bmtfwh;
    std::vector<int> bmtfFineBit;

    int trmbSize;
    std::vector<int> trmbPt;
    std::vector<int> trmbEta;
    std::vector<int> trmbPhi;
    std::vector<int> trmbqual;
    std::vector<int> trmbch;
    std::vector<int> trmbbx;
    std::vector<int> trmbprocessor;
    std::vector<int> trmbtrAddress;
    std::vector<int> trmbwh;
    std::vector<int> trmbFineBit;

/*
    int trmbSize;
    std::vector<int>   trmbBx;
    std::vector<int>   trmbTag;
    std::vector<int>   trmbQual;
    std::vector<int>   trmbPtPck;
    std::vector<int>   trmbPhiPck;
    std::vector<int>   trmbEtaPck;
    std::vector<double>trmbPhiGlob;
    std::vector<int>   trmbChPck;
    std::vector<int>   trmbWh;
    std::vector<int>   trmbSc;
    std::vector<unsigned int> trmbAddress;
*/

  };
}
#endif


