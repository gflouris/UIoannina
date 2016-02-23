#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "UIoannina/TrUpS/interface/GenMuon.h"

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
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include <FWCore/ParameterSet/interface/ParameterSet.h>
#include <FWCore/Framework/interface/ConsumesCollector.h>

TrUpS::GenMuon::GenMuon(edm::ConsumesCollector && ix)
{	
//consumesCollector();     
// consumes<reco::GenParticleCollection>(iConfig.getParameter<edm::InputTag>("genParticles"));
 
}


TrUpS::GenMuon::~GenMuon()
{

}

void TrUpS::GenMuon::SetGen(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

edm::Handle<reco::GenParticleCollection> genParticles;
iEvent.getByLabel("genParticles", genParticles);

   int indx=0; 
for(reco::GenParticleCollection::const_iterator ig = genParticles->begin(); ig!= genParticles->end(); ++ig) {

   if(ig->pdgId()==13 || ig->pdgId()==-13){
   gen_.genPt_Mu.push_back(ig->pt());
   gen_.genEta_Mu.push_back(ig->eta());
   gen_.genStatus_Mu.push_back(ig->status());
   gen_.genPhi_Mu.push_back(ig->phi());
   indx++;
   }
} 
gen_.gen_muons=indx;

if(gen_.gen_muons == 0){
   gen_.genPt_Mu.push_back(-100);
   gen_.genEta_Mu.push_back(-100);
   gen_.genStatus_Mu.push_back(-100);
   gen_.genPhi_Mu.push_back(-100);
}
 
}
