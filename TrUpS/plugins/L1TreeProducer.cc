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
#include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambThContainer.h"
#include "DataFormats/L1DTTrackFinder/interface/L1MuDTTrackContainer.h"

#include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambPhContainer.h"
#include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambPhDigi.h"
#include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambThContainer.h"
#include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambThDigi.h"
#include "DataFormats/L1DTTrackFinder/interface/L1MuDTTrackContainer.h"

#include "DataFormats/L1TMuon/interface/RegionalMuonCand.h"

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

#include "UIoannina/TrUpS/interface/L1AnalysisGMT.h"
#include "UIoannina/TrUpS/interface/L1AnalysisDTTF.h"
#include "UIoannina/TrUpS/interface/L1AnalysisBMTF.h"


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
  virtual void analyzeBMTF(const edm::Event&);
  virtual void endJob();

public:

  TrUpS::L1AnalysisGMT*     		l1gmt;
  TrUpS::L1AnalysisGMTDataFormat*        l1gmt_data;

  TrUpS::L1AnalysisDTTF*     		l1dttf;
  TrUpS::L1AnalysisDTTFDataFormat*        l1dttf_data;

  TrUpS::L1AnalysisBMTF*     		l1bmtf;
  TrUpS::L1AnalysisBMTFDataFormat*        l1bmtf_data;
private:

  // output file
  edm::Service<TFileService> fs_;

  // tree
  TTree * tree_;

  // EDM input tags
  edm::InputTag trInputTag;
  edm::InputTag trInputTagDTTF;
  edm::InputTag mbtrInputTag;
  edm::InputTag mbtrInputTagBM;

};



L1TreeProducer::L1TreeProducer(const edm::ParameterSet& iConfig)
{





  l1gmt      	= new  TrUpS::L1AnalysisGMT(consumesCollector());
  l1gmt_data	     = l1gmt->getData();

  l1dttf      	=   new  TrUpS::L1AnalysisDTTF(consumesCollector());
  l1dttf_data	     = l1dttf->getData();

  l1bmtf      	=   new  TrUpS::L1AnalysisBMTF(consumesCollector());
  l1bmtf_data	     = l1bmtf->getData();


  //usesResource("L1TreeProducer");
  consumes<L1MuDTChambPhContainer>(iConfig.getParameter<edm::InputTag>("dttfDigis"));
  consumes<L1MuDTChambThContainer>(iConfig.getParameter<edm::InputTag>("dttfDigis"));

 consumes<L1MuDTChambThContainer>(iConfig.getParameter<edm::InputTag>("dttfDigis"));
  consumes<L1MuDTChambThContainer>(iConfig.getParameter<edm::InputTag>("dttfDigis"));

  consumes<L1MuDTTrackContainer>(iConfig.getParameter<edm::InputTag>("dttfDigis"));
//  edm::InputTag trInputTag;
  consumes<L1MuDTTrackContainer>(iConfig.getParameter<edm::InputTag>("trInputTag"));
  consumes<L1MuDTTrackContainer>(iConfig.getParameter<edm::InputTag>("trInputTagDTTF"));

  consumes<l1t::RegionalMuonCandBxCollection>(iConfig.getParameter<edm::InputTag>("mbtrInputTag"));
  consumes<l1t::RegionalMuonCandBxCollection>(iConfig.getParameter<edm::InputTag>("mbtrInputTagBMTF"));

  consumes<L1MuGMTReadoutCollection>(iConfig.getParameter<edm::InputTag>("gtDigis"));
//  consumes<std::vector<reco::Vertex> >(iConfig.getParameter<edm::InputTag>("offlinePrimaryVertices"));
  consumes<l1t::RegionalMuonCandBxCollection>(iConfig.getParameter<edm::InputTag>("mbtrInputTagBM"));
  consumes<l1t::RegionalMuonCandBxCollection>(iConfig.getParameter<edm::InputTag>("mbtrInputTagBMTF"));


  // set up output
  tree_=fs_->make<TTree>("L1Tree", "L1Tree");
  tree_->Branch("GMT",         "TrUpS::L1AnalysisGMTDataFormat",       	    &l1gmt_data,             32000, 3);
  tree_->Branch("DTTF",        "TrUpS::L1AnalysisDTTFDataFormat",       	    &l1dttf_data,             32000, 3);
  tree_->Branch("BMTF",        "TrUpS::L1AnalysisBMTFDataFormat",       	    &l1bmtf_data,             32000, 3);



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
//  analyzeDTTF(iEvent);
  analyzeBMTF(iEvent);

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
  //std::cout<<trstring<<std::endl;
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

  edm::InputTag mbtfSource_("bmtfDigis");
/*

  edm::Handle<BMTrackContainer > myL1MuMBTrackContainer;
  std::string mbtrstring;
  mbtrstring = mbtfSource_.label()+":"+"DATA"+":"+mbtfSource_.process();
  edm::InputTag mbtrInputTag(mbtrstring);
  iEvent.getByLabel(mbtrInputTag,myL1MuMBTrackContainer);
  if (myL1MuMBTrackContainer.isValid()) {
    l1dttf->SetMBTR(myL1MuMBTrackContainer, max);
  }
  else {
    mbtrstring = mbtfSource_.label()+":"+"BMTF"+":"+mbtfSource_.process();
    edm::InputTag mbtrInputTag(mbtrstring);
    iEvent.getByLabel(mbtrInputTag,myL1MuMBTrackContainer);
    if (myL1MuMBTrackContainer.isValid()) {
      l1dttf->SetMBTR(myL1MuMBTrackContainer, max);
    }
    else {
      edm::LogInfo("L1Prompt") << "can't find L1MuMBTrackContainer " << mbtfSource_.label();
    }
  }
*/



}

void L1TreeProducer::analyzeBMTF(const edm::Event& iEvent)
{
  l1bmtf->Reset();

edm::InputTag dttfSource_("dttfDigis");
unsigned int max = 50;
  edm::Handle<L1MuDTChambPhContainer > myL1MuDTChambPhContainer;
  iEvent.getByLabel("dttfDigis",myL1MuDTChambPhContainer);
  if (!myL1MuDTChambPhContainer.isValid()) {
    edm::LogInfo("L1Prompt") << "can't find L1MuDTChambPhContainer with label " << dttfSource_.label() ;
    }
  else l1bmtf->SetDTPH(myL1MuDTChambPhContainer, max);

  edm::Handle<L1MuDTChambThContainer > myL1MuDTChambThContainer;
  iEvent.getByLabel("dttfDigis",myL1MuDTChambThContainer);
  if (!myL1MuDTChambThContainer.isValid()) {
    edm::LogInfo("L1Prompt") << "can't find L1MuDTChambThContainer with label " << dttfSource_.label() ;
    edm::LogInfo("L1Prompt") << "if this fails try to add DATA to the process name." ;
    }
  else l1bmtf->SetDTTH(myL1MuDTChambThContainer, max);


   edm::InputTag mbtfSource_("simBmtfDigis");

/*
  edm::Handle<BMTrackContainer > myL1MuMBTrackContainer;
  std::string mbtrstring;
  mbtrstring = mbtfSource_.label()+":"+"DATA"+":"+mbtfSource_.process();
  edm::InputTag mbtrInputTag(mbtrstring);
  iEvent.getByLabel(mbtrInputTag,myL1MuMBTrackContainer);
  if (myL1MuMBTrackContainer.isValid()) {
    l1bmtf->SetMBTR(myL1MuMBTrackContainer, max);
  }
  else {
    mbtrstring = mbtfSource_.label()+":"+"BM"+":"+mbtfSource_.process();
    edm::InputTag mbtrInputTag1(mbtrstring);
    iEvent.getByLabel(mbtrInputTag1,myL1MuMBTrackContainer);
    if (myL1MuMBTrackContainer.isValid()) {
      l1bmtf->SetMBTR(myL1MuMBTrackContainer, max);
    }
    else {
      edm::LogInfo("L1Prompt") << "can't find L1MuMBTrackContainer " << mbtfSource_.label();
    }
  }
*/

  int ctr = 0;
  edm::Handle<l1t::RegionalMuonCandBxCollection> mycoll;
  std::string mbtrstring;
  mbtrstring = mbtfSource_.label()+":"+"DATA"+":"+mbtfSource_.process();
  edm::InputTag mbtrInputTag2(mbtrstring);
  iEvent.getByLabel(mbtrInputTag2,mycoll);
  if (mycoll.isValid()) {
        for(int i=-2; i<2; i++)
            l1bmtf->SetMBTF(*mycoll,ctr,  i);
  }
  else {
    mbtrstring = mbtfSource_.label()+":"+"BMTF"+":"+mbtfSource_.process();
    edm::InputTag mbtrInputTag3(mbtrstring);
    iEvent.getByLabel(mbtrInputTag3,mycoll);
    if (mycoll.isValid()) {
       for(int i=-2; i<2; i++)
            l1bmtf->SetMBTF(*mycoll,ctr, i);
    }
    else {
      edm::LogInfo("L1Prompt") << "can't find L1MuMBTrackContainer " << mbtfSource_.label();
    }

  }


   int ctr1 = 0;
  edm::Handle<l1t::RegionalMuonCandBxCollection> mycollbm;
  //std::string mbtrstring;
  iEvent.getByLabel(mbtrInputTag2,mycollbm);
  if (mycollbm.isValid()) {
        for(int i=-2; i<2; i++)
            l1bmtf->SetMBTR(*mycollbm,ctr1,  i);
  }
  else {
    mbtrstring = mbtfSource_.label()+":"+"UnsortedBMTF"+":"+mbtfSource_.process();
    edm::InputTag mbtrInputTag3(mbtrstring);
    iEvent.getByLabel(mbtrInputTag3,mycollbm);
    if (mycollbm.isValid()) {
        for(int i=-2; i<=2; i++)
            l1bmtf->SetMBTR(*mycollbm,ctr1, i);
    }
    else {
      edm::LogInfo("L1Prompt") << "can't find L1MuMBTrackContainer " << mbtfSource_.label();
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
