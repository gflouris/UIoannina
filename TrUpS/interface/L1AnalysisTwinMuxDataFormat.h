#ifndef __TrUpS_L1AnalysisTwinMuxDataFormat_H__
#define __TrUpS_L1AnalysisTwinMuxDataFormat_H__



#include <vector>
#include "TMatrixD.h"
#include <string>

namespace TrUpS
{
  struct L1AnalysisTwinMuxDataFormat
  {

    L1AnalysisTwinMuxDataFormat(){Reset();};
    ~L1AnalysisTwinMuxDataFormat(){};

    void Reset()
    {

    phSize = 0;

    phBx.clear();
    phWh.clear();
    phSe.clear();
    phSt.clear();
    phAng.clear();
    phBandAng.clear();
    phCode.clear();
    phTs2Tag.clear();

    tmSize = 0;

    tmBx.clear();
    tmWh.clear();
    tmSe.clear();
    tmSt.clear();
    tmAng.clear();
    tmBandAng.clear();
    tmCode.clear();
    tmTs2Tag.clear();
    tmRpcBit.clear();


    thSize = 0;

    thBx.clear();
    thWh.clear();
    thSe.clear();
    thSt.clear();
    thCode.clear();
    thTheta.clear();

    rpcSize = 0;
    rpcBx.clear();
    rpcWh.clear();
    rpcSe.clear();
    rpcSt.clear();
    rpcLayer.clear();
    rpcStrip.clear();


    // twinmuxSize = 0;
    // twinmuxPt.clear();
    // twinmuxEta.clear();
    // twinmuxPhi.clear();
    // twinmuxqual.clear();
    // twinmuxch.clear();
    // twinmuxbx.clear();
    // twinmuxprocessor.clear();
    // twinmuxtrAddress.clear();
    // twinmuxwh.clear();
    // twinmuxFineBit.clear();
    }

    // ---- L1AnalysisTwinMuxDataFormat information.

    int phSize;
    std::vector<int>    phBx;
    std::vector<int>    phWh;
    std::vector<int>    phSe;
    std::vector<int>    phSt;
    std::vector<float>  phAng;
    std::vector<float>  phBandAng;
    std::vector<int>    phCode;
    std::vector<int>    phTs2Tag;


    int thSize;
    std::vector<int>   thBx;
    std::vector<int>   thWh;
    std::vector<int>   thSe;
    std::vector<int>   thSt;

    std::vector<int> thTheta;
    std::vector<int> thCode; 
 

    int rpcSize;
    std::vector<int>    rpcBx;
    std::vector<int>    rpcWh;
    std::vector<int>    rpcSe;
    std::vector<int>    rpcSt;
    std::vector<int>    rpcLayer;
    std::vector<int>    rpcStrip;


    int tmSize;
    std::vector<int>    tmBx;
    std::vector<int>    tmWh;
    std::vector<int>    tmSe;
    std::vector<int>    tmSt;
    std::vector<float>  tmAng;
    std::vector<float>  tmBandAng;
    std::vector<int>    tmCode;
    std::vector<int>    tmTs2Tag;
    std::vector<int>    tmRpcBit;


  };
}
#endif


