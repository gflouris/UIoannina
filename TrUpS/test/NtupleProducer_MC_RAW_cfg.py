import FWCore.ParameterSet.Config as cms

from UIoannina.TrUpS.Ntuple_MC_cfg import *

# job options

#process.GlobalTag.globaltag = 'START52_V9::All'

#process.options = cms.untracked.PSet(
#SkipEvent = cms.untracked.vstring('ProductNotFound')
#				    )


process.oneGoodVertexFilter = cms.EDFilter("VertexSelector",
   src = cms.InputTag("offlinePrimaryVertices"),
   cut = cms.string("!isFake && ndof >= 4 && abs(z) <= 15 && position.Rho <= 2"),
   filter = cms.bool(True),   # otherwise it won't filter the events, just produce an empty vertex collection.
)
process.noScraping = cms.EDFilter("FilterOutScraping",
    applyfilter = cms.untracked.bool(True),
    debugOn = cms.untracked.bool(False), ## Or 'True' to get some per-event info
    numtrack = cms.untracked.uint32(10),
    thresh = cms.untracked.double(0.25)
)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

readFiles = cms.untracked.vstring(
#'file:///mnt/storage/flouris/FC238AA2-278A-E111-BB8E-0030487F92B1.root'
 'file://../../../SingleMuPt100_500events.root'
  #'file://../../../SingleMuPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW.root'
#  'file:///afs/cern.ch/user/n/nloukas/public/SingleMuPt100_20000.root'
)

secFiles = cms.untracked.vstring(
#'file:///mnt/storage/flouris/00D8FE5F-B198-E111-9C42-0025904B1448.root'
	)
process.source = cms.Source ("PoolSource",
                             fileNames = readFiles,
                             secondaryFileNames = secFiles
                             )


#############L1 Trigger Block##################
#process.load("UserCode.L1TriggerDPG.l1Ntuple_cfg")
#process.load("UserCode.L1TriggerDPG.l1NtupleProducer_cfi")
process.load("Configuration.StandardSequences.RawToDigi_Data_cff")
process.load("UIoannina.TrUpS.L1Producer_cfi")

process.p = cms.Path(
    process.RawToDigi
    +process.L1TProducer    
#+process.l1NtupleProducer
)

process.load("UIoannina.TrUpS.GENProducer_cfi")
process.gen = cms.Path (
	process.GENTProducer
)
###############################################
process.schedule = cms.Schedule(
    process.gen,
    process.p
)



# output file
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('Tree_from_RAW_500events_old_LUTS.root')
)

