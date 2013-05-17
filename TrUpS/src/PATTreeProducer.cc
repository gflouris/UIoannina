// -*- C++ -*-
//
// Package:    
// Class:      
//



//
// Original Author:  G.Flouris
//         Created:
// 
//
//


// system include files
#include <memory>

// framework
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Framework/interface/ESHandle.h"




// ROOT output stuff
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"
#include "TTree.h"
#include "TF1.h"

//local  data formats

#include "UIoannina/TrUpS/interface/PATMuon.h"


//
// class declaration
//

class PATTreeProducer : public edm::EDAnalyzer {
public:
  explicit PATTreeProducer(const edm::ParameterSet&);
  ~PATTreeProducer();


private:
  virtual void beginJob(void) ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob();

public:

  TrUpS::PATMuon*     		pat;

  TrUpS::PATMuonDataFormat*            pat_data;


private:

  // output file
  edm::Service<TFileService> fs_;

  // tree
  TTree * tree_;

  // EDM input tags
//  edm::InputTag jetTag_;
};



PATTreeProducer::PATTreeProducer(const edm::ParameterSet& iConfig)
{

 
  pat      	= new  TrUpS::PATMuon();

  pat_data	     = pat->getData();


  // set up output
  tree_=fs_->make<TTree>("PATTree", "PATTree");
  tree_->Branch("PATMuons",        "TrUpS::PATMuonDataFormat",       	    &pat_data,             32000, 3);



}


PATTreeProducer::~PATTreeProducer()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void PATTreeProducer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  pat->Reset();
  pat->SetPAT(iEvent,iSetup);

  tree_->Fill();

}

// ------------ method called once each job just before starting event loop  ------------
void
PATTreeProducer::beginJob(void)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
PATTreeProducer::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(PATTreeProducer);
