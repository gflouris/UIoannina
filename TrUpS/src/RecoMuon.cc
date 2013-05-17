#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "UIoannina/TrUpS/interface/RecoMuon.h"

#include "DataFormats/VertexReco/interface/Vertex.h"

// framework
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include <FWCore/Framework/interface/LuminosityBlock.h>

TrUpS::RecoMuon::RecoMuon()
{	     
}


TrUpS::RecoMuon::~RecoMuon()
{

}

void TrUpS::RecoMuon::SetReco(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
edm::Handle<reco::MuonCollection> rmuons;
iEvent.getByLabel("muons", rmuons);

edm::Handle<std::vector<reco::Vertex> > vertex;
iEvent.getByLabel(edm::InputTag("offlinePrimaryVertices"), vertex);

   int indx=0;

for(reco::MuonCollection::const_iterator imu = rmuons->begin(); imu!= rmuons->end(); ++imu) {

   if(((imu->pdgId()==13 || imu->pdgId()==-13))){
   recomu_.recoPt_Mu.push_back(imu->pt());
   recomu_.recoEta_Mu.push_back(imu->eta());
   recomu_.recoStatus_Mu.push_back(imu->status());
   recomu_.recoPhi_Mu.push_back(imu->phi());
   recomu_.isTight_Mu.push_back( (imu->isGlobalMuon() && imu->isPFMuon() &&  imu->globalTrack()->normalizedChi2() < 10. && imu->globalTrack()->hitPattern().numberOfValidMuonHits() > 0 &&
		    imu->numberOfMatchedStations() > 1 &&  fabs(imu->muonBestTrack()->dxy(vertex->at(0).position())) < 0.2 &&  fabs(imu->muonBestTrack()->dz(vertex->at(0).position())) < 0.5 &&
		    imu->innerTrack()->hitPattern().numberOfValidPixelHits() > 0 &&  imu->track()->hitPattern().trackerLayersWithMeasurement() > 5 ));

   recomu_.isLoose_Mu.push_back ((imu->isGlobalMuon() || imu->isTrackerMuon()) && imu->isPFMuon());
   recomu_.isQuality_Valid_Mu.push_back(imu->isQualityValid());	
   recomu_.isMuon.push_back(imu->isMuon());
   recomu_.isGlobal.push_back(imu->isGlobalMuon());
   recomu_.isTracker.push_back(imu->isTrackerMuon());
   recomu_.isCalo.push_back(imu->isCaloMuon());
   recomu_.isPF.push_back(imu->isPFMuon());
      indx++;
   }
 
}  
recomu_.reco_muons = indx;
if(recomu_.reco_muons == 0){
   recomu_.recoPt_Mu.push_back(-100);
   recomu_.recoEta_Mu.push_back(-100);
   recomu_.recoStatus_Mu.push_back(-100);
   recomu_.recoPhi_Mu.push_back(-100);
   recomu_.isTight_Mu.push_back(false);
   recomu_.isLoose_Mu.push_back(false);
   recomu_.isQuality_Valid_Mu.push_back(false);
   recomu_.isMuon.push_back(false);
   recomu_.isGlobal.push_back(false);
   recomu_.isTracker.push_back(false);
   recomu_.isCalo.push_back(false);
   recomu_.isPF.push_back(false);
   }
 
}
