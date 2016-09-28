#ifndef __TrUpS_L1AnalysisTwinMux_H__
#define __TrUpS_L1AnalysisTwinMux_H__

#include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambPhContainer.h"
#include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambThContainer.h"
#include "DataFormats/L1DTTrackFinder/interface/L1MuDTTrackContainer.h"
#include "DataFormats/L1TMuon/interface/RegionalMuonCand.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/RPCDigi/interface/RPCDigiCollection.h"

#include <vector>
#include "TMatrixD.h"
#include "L1AnalysisTwinMuxDataFormat.h"


#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"


namespace TrUpS
{
  class L1AnalysisTwinMux
  {
  public:
    L1AnalysisTwinMux(edm::ConsumesCollector && ix);
    ~L1AnalysisTwinMux();

    void SetTwinMux(const edm::Handle<L1MuDTChambPhContainer > L1MuDTChambPhContainer, unsigned int maxDTPH);
    void SetDTPH(const edm::Handle<L1MuDTChambPhContainer > L1MuDTChambPhContainer, unsigned int maxDTPH);
    void SetDTTH(const edm::Handle<L1MuDTChambThContainer > L1MuDTChambThContainer, unsigned int maxDTTH);
    void SetRPC(RPCDigiCollection m_rpcDigis);
    //void SetTwinMux(const l1t::RegionalMuonCandBxCollection& coll, int& ctr, int bx);

    void Reset() {twinmux_.Reset();}
    L1AnalysisTwinMuxDataFormat * getData() {return &twinmux_;}

  private :
    L1AnalysisTwinMuxDataFormat twinmux_;
  };
}
#endif


