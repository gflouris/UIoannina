import FWCore.ParameterSet.Config as cms

from UIoannina.TrUpS.Ntuple_cfg import *

# job options

process.GlobalTag.globaltag = 'START52_V9::All'

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
'file:///mnt/storage/flouris/FC238AA2-278A-E111-BB8E-0030487F92B1.root'
)

secFiles = cms.untracked.vstring(
#'file:///mnt/storage/flouris/00D8FE5F-B198-E111-9C42-0025904B1448.root'
	)
process.source = cms.Source ("PoolSource",
                             fileNames = readFiles,
                             secondaryFileNames = secFiles
                             )


###############PAT Block###############
process.load("PhysicsTools.PatAlgos.patSequences_cff")
from PhysicsTools.PatAlgos.tools.coreTools import *

process.pat_step=cms.Path(process.patDefaultSequence)
process.pat_tree=cms.Path(process.PATTProducer)


###############################################
process.schedule = cms.Schedule(
    process.default,
    process.pat_step,
    process.pat_tree
)



# output file
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('Tree_from_RECO.root')
)

