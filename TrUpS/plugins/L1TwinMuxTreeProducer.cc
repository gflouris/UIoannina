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

#include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambPhContainer.h"
#include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambPhDigi.h"
#include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambThContainer.h"
#include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambThDigi.h"
#include "DataFormats/L1DTTrackFinder/interface/L1MuDTTrackContainer.h"
#include "DataFormats/RPCDigi/interface/RPCDigiCollection.h"

#include "FWCore/Utilities/interface/EDGetToken.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/Event.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

// ROOT output stuff
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"
#include "TTree.h"
#include "TF1.h"
#include <FWCore/Framework/interface/ConsumesCollector.h>

//local  data formats

#include "UIoannina/TrUpS/interface/L1AnalysisTwinMux.h"


//
// class declaration
//

class L1TwinMuxTreeProducer : public edm::EDAnalyzer {
public:
  explicit L1TwinMuxTreeProducer(const edm::ParameterSet&);
  ~L1TwinMuxTreeProducer();


private:
  virtual void beginJob(void) ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void analyzeTwinMux(const edm::Event&);
  virtual void endJob();

public:

  TrUpS::L1AnalysisTwinMux*     	          	l1twinmux;
  TrUpS::L1AnalysisTwinMuxDataFormat*         l1twinmux_data;

private:

  // output file
  edm::Service<TFileService> fs_;

  // tree
  TTree * tree_;

  edm::InputTag twinmuxInputTag_;

edm::EDGetTokenT<L1MuDTChambPhContainer> twinmuxPhInputTag_;
edm::EDGetTokenT<L1MuDTChambThContainer> twinmuxThInputTag_;
edm::EDGetTokenT<RPCDigiCollection>      twinmuxRPCInputTag_;
edm::EDGetTokenT<L1MuDTChambPhContainer> twinmuxOutputTag_;

};



L1TwinMuxTreeProducer::L1TwinMuxTreeProducer(const edm::ParameterSet& iConfig)
{


  l1twinmux      	=   new  TrUpS::L1AnalysisTwinMux(consumesCollector());
  l1twinmux_data	     = l1twinmux->getData();

  //consumes<L1MuDTChambPhContainer>(iConfig.getParameter<edm::InputTag>("twinmuxInputDigis"));
  //consumes<L1MuDTChambThContainer>(iConfig.getParameter<edm::InputTag>("twinmuxInputDigis"));


   twinmuxPhInputTag_ = consumes<L1MuDTChambPhContainer>(iConfig.getParameter<edm::InputTag>("twinmuxInputPhDigis"));
   twinmuxThInputTag_ = consumes<L1MuDTChambThContainer>(iConfig.getParameter<edm::InputTag>("twinmuxInputThDigis"));
   twinmuxRPCInputTag_ = consumes<RPCDigiCollection>(iConfig.getParameter<edm::InputTag>("twinmuxInputRPCDigis"));

   twinmuxOutputTag_ = consumes<L1MuDTChambPhContainer>(iConfig.getParameter<edm::InputTag>("twinmuxOutputDigis"));
  


  // set up output
  tree_=fs_->make<TTree>("L1Tree", "L1Tree");
  tree_->Branch("TwinMux","TrUpS::L1AnalysisTwinMuxDataFormat", &l1twinmux_data, 32000, 3);

}


L1TwinMuxTreeProducer::~L1TwinMuxTreeProducer()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void L1TwinMuxTreeProducer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  analyzeTwinMux(iEvent);
  tree_->Fill();
}



void L1TwinMuxTreeProducer::analyzeTwinMux(const edm::Event& iEvent)
{
  l1twinmux->Reset();

edm::InputTag dttfSource_("TwinMuxStage2Digis");
unsigned int max = 1680;
  edm::Handle<L1MuDTChambPhContainer > myL1MuDTChambPhContainer;
  //iEvent.getByLabel("TwinMuxStage2Digis",myL1MuDTChambPhContainer);
  iEvent.getByToken(twinmuxPhInputTag_,myL1MuDTChambPhContainer);

  if (!myL1MuDTChambPhContainer.isValid()) {
    edm::LogInfo("L1Prompt") << "can't find L1MuDTChambPhContainer" ;
    }
  else l1twinmux->SetDTPH(myL1MuDTChambPhContainer, max);

  edm::Handle<L1MuDTChambThContainer > myL1MuDTChambThContainer;
  //iEvent.getByLabel("TwinMuxStage2Digis",myL1MuDTChambThContainer);
  iEvent.getByToken(twinmuxThInputTag_,myL1MuDTChambThContainer);
  if (!myL1MuDTChambThContainer.isValid()) {
    edm::LogInfo("L1Prompt") << "can't find L1MuDTChambThContainer";
    }
  else l1twinmux->SetDTTH(myL1MuDTChambThContainer, max);



  edm::Handle<RPCDigiCollection > myRPCDigiCollection;
  iEvent.getByToken(twinmuxRPCInputTag_,myRPCDigiCollection);
  l1twinmux->SetRPC(*myRPCDigiCollection);

  edm::Handle<L1MuDTChambPhContainer > myL1MuDTChambPhContainerOut;
  //iEvent.getByLabel("TwinMuxStage2Digis",myL1MuDTChambThContainer);
  iEvent.getByToken(twinmuxOutputTag_,myL1MuDTChambPhContainerOut);
  if (!myL1MuDTChambPhContainerOut.isValid()) {
    edm::LogInfo("L1Prompt") << "can't find L1MuDTChambThContainer";
    }
  else l1twinmux->SetTwinMux(myL1MuDTChambPhContainerOut, max);






}



// ------------ method called once each job just before starting event loop  ------------
void
L1TwinMuxTreeProducer::beginJob(void)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
L1TwinMuxTreeProducer::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(L1TwinMuxTreeProducer);
