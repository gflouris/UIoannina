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

#include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambPhContainer.h"
#include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambPhDigi.h"
#include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambThContainer.h"
#include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambThDigi.h"
#include "DataFormats/L1DTTrackFinder/interface/L1MuDTTrackContainer.h"


// ROOT output stuff
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"
#include "TTree.h"
#include "TF1.h"

//local  data formats

#include "UIoannina/TrUpS/interface/L1AnalysisGMT.h"
#include "UIoannina/TrUpS/interface/L1AnalysisDTTF.h"


//
// class declaration
//

class L1TreeProducer : public edm::EDAnalyzer {
public:
  explicit L1TreeProducer(const edm::ParameterSet&);
  ~L1TreeProducer();


private:
  virtual void beginJob(void) ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void analyzeGMT(const edm::Event&);
  virtual void analyzeDTTF(const edm::Event&);
  virtual void endJob();

public:

  TrUpS::L1AnalysisGMT*     		l1gmt;
  TrUpS::L1AnalysisGMTDataFormat*        l1gmt_data;

  TrUpS::L1AnalysisDTTF*     		l1dttf;
  TrUpS::L1AnalysisDTTFDataFormat*        l1dttf_data;
private:

  // output file
  edm::Service<TFileService> fs_;

  // tree
  TTree * tree_;

  // EDM input tags
//  edm::InputTag jetTag_;
};



L1TreeProducer::L1TreeProducer(const edm::ParameterSet& iConfig)
{


 
  l1gmt      	= new  TrUpS::L1AnalysisGMT();
  l1gmt_data	     = l1gmt->getData();

  l1dttf      	=   new  TrUpS::L1AnalysisDTTF();
  l1dttf_data	     = l1dttf->getData();

  // set up output
  tree_=fs_->make<TTree>("L1Tree", "L1Tree");
  tree_->Branch("GMT",         "TrUpS::L1AnalysisGMTDataFormat",       	    &l1gmt_data,             32000, 3);
  tree_->Branch("DTTF",        "TrUpS::L1AnalysisDTTFDataFormat",       	    &l1dttf_data,             32000, 3);



}


L1TreeProducer::~L1TreeProducer()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void L1TreeProducer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{


  analyzeGMT(iEvent);
  analyzeDTTF(iEvent);
  tree_->Fill();

}

void L1TreeProducer::analyzeGMT(const edm::Event& iEvent)
{
    l1gmt->Reset();
    edm::Handle<L1MuGMTReadoutCollection> gmtrc_handle;
    iEvent.getByLabel("gtDigis",gmtrc_handle);
    L1MuGMTReadoutCollection const* gmtrc = gmtrc_handle.product();

    l1gmt->SetGMT(gmtrc);


}

void L1TreeProducer::analyzeDTTF(const edm::Event& iEvent)
{
  l1dttf->Reset();

edm::InputTag dttfSource_("dttfDigis");
unsigned int max = 50;
  edm::Handle<L1MuDTChambPhContainer > myL1MuDTChambPhContainer;  
  iEvent.getByLabel("dttfDigis",myL1MuDTChambPhContainer);
  if (!myL1MuDTChambPhContainer.isValid()) {
    edm::LogInfo("L1Prompt") << "can't find L1MuDTChambPhContainer with label " << dttfSource_.label() ;   
    }
  else l1dttf->SetDTPH(myL1MuDTChambPhContainer, max);

  edm::Handle<L1MuDTChambThContainer > myL1MuDTChambThContainer;  
  iEvent.getByLabel("dttfDigis",myL1MuDTChambThContainer);
  if (!myL1MuDTChambThContainer.isValid()) {
    edm::LogInfo("L1Prompt") << "can't find L1MuDTChambThContainer with label " << dttfSource_.label() ;
    edm::LogInfo("L1Prompt") << "if this fails try to add DATA to the process name." ;   
    }
  else l1dttf->SetDTTH(myL1MuDTChambThContainer, max);


  edm::Handle<L1MuDTTrackContainer > myL1MuDTTrackContainer;
  std::string trstring;
  trstring = dttfSource_.label()+":"+"DATA"+":"+dttfSource_.process();
  edm::InputTag trInputTag(trstring);
  iEvent.getByLabel(trInputTag,myL1MuDTTrackContainer);
  if (myL1MuDTTrackContainer.isValid()) {
    l1dttf->SetDTTR(myL1MuDTTrackContainer, max);
  }
  else {
    trstring = dttfSource_.label()+":"+"DTTF"+":"+dttfSource_.process();
    edm::InputTag trInputTag(trstring);
    iEvent.getByLabel(trInputTag,myL1MuDTTrackContainer);
    if (myL1MuDTTrackContainer.isValid()) {
      l1dttf->SetDTTR(myL1MuDTTrackContainer, max);
    }
    else {
      edm::LogInfo("L1Prompt") << "can't find L1MuDTTrackContainer " << dttfSource_.label();
    }
  }



}

// ------------ method called once each job just before starting event loop  ------------
void
L1TreeProducer::beginJob(void)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
L1TreeProducer::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(L1TreeProducer);
