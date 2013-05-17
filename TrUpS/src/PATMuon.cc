
#include "UIoannina/TrUpS/interface/PATMuon.h"

//#include "DataFormats/VertexReco/interface/Vertex.h"

#include <iostream>
#include <sstream>
#include <istream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>
#include <functional>
#include <vector>
#include <cassert>
//#include "TMath.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
//#include "DataFormats/VertexReco/interface/Vertex.h"
//#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/HLTReco/interface/TriggerObject.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "DataFormats/MuonReco/interface/MuonMETCorrectionData.h"

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/PatCandidates/interface/Lepton.h"
#include "DataFormats/ParticleFlowCandidate/interface/IsolatedPFCandidateFwd.h"
#include "DataFormats/ParticleFlowCandidate/interface/IsolatedPFCandidate.h"


using namespace std;

TrUpS::PATMuon::PATMuon()
{	     
}


TrUpS::PATMuon::~PATMuon()
{
}

void TrUpS::PATMuon::SetPAT(const edm::Event & iEvent, const edm::EventSetup& eventSetup)
{
//   edm::Handle<edm::View<pat::Muon> > muons;
  // Get the Muon collection
  edm::Handle<pat::MuonCollection> ppmuons;
  iEvent.getByLabel("selectedPatMuons",ppmuons);
  //  edm::View<pat::Muon> pat_muons = *ppmuons;
//  edm::Handle<pat::Muon> *ipt;
 // ipt->IPTYPE() type = Pv2D;
    int indx=0;
    for(pat::MuonCollection::const_iterator imu = ppmuons->begin();imu != ppmuons->end(); ++imu,++indx) { 

//   patmu_.ispatTight_Mu.push_back(false);
   if((imu->pdgId()==13 || imu->pdgId()==-13)){
   patmu_.patPt_Mu.push_back(imu->pt());
   patmu_.patEta_Mu.push_back(imu->eta());
   patmu_.patStatus_Mu.push_back(imu->status());
   patmu_.patPhi_Mu.push_back(imu->phi());
//   patmu_.isTight_Mu.push_back( (imu->isGlobalMuon() && imu->isPFMuon() &&  imu->globalTrack()->normalizedChi2() < 10. && imu->globalTrack()->hitPattern().numberOfValidMuonHits() > 0 &&
	//	    imu->numberOfMatchedStations() > 1 &&  fabs(imu->muonBestTrack()->dxy(vertex->at(0).position())) < 0.2 &&  fabs(imu->muonBestTrack()->dz(vertex->at(0).position())) < 0.5 &&
	//	    imu->innerTrack()->hitPattern().numberOfValidPixelHits() > 0 &&  imu->track()->hitPattern().trackerLayersWithMeasurement() > 5 ));
 //  patmu_.isTight_Mu.push_back( (imu->isGlobalMuon() && imu->isPFMuon() &&  imu->globalTrack()->normalizedChi2() < 10. && imu->globalTrack()->hitPattern().numberOfValidMuonHits() > 0 &&
//		    imu->numberOfMatchedStations() > 1 &&  imu->dB(type) < 0.2 &&
//		    imu->innerTrack()->hitPattern().numberOfValidPixelHits() > 0 &&  imu->track()->hitPattern().trackerLayersWithMeasurement() > 5 ));

   patmu_.isLoose_Mu.push_back ((imu->isGlobalMuon() || imu->isTrackerMuon()) && imu->isPFMuon());
	

  indx++;
   }

}  

patmu_.pat_muons = indx;

if(patmu_.pat_muons == 0){
   patmu_.patPt_Mu.push_back(-100);
   patmu_.patEta_Mu.push_back(-100);
   patmu_.patStatus_Mu.push_back(-100);
   patmu_.patPhi_Mu.push_back(-100);
} 
}
