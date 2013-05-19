import FWCore.ParameterSet.Config as cms

from UIoannina.TrUpS.Ntuple_cfg import *

# job options

process.GlobalTag.globaltag = 'FT_R_53_V6::All'#GR_R_53_V21::All'

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
'file:////afs/cern.ch/work/g/gflouris/MultiJet_Run2012A_FEF90708-EED5-E111-B7B4-003048678B88.root'
#'file:///afs/cern.ch/work/g/gflouris/FEFE1E7B-65D9-E111-966A-00261894398C.root'
#FEF90708-EED5-E111-B7B4-003048678B88.root
)

secFiles = cms.untracked.vstring(
#'file:///mnt/storage/flouris/00D8FE5F-B198-E111-9C42-0025904B1448.root'
	)
process.source = cms.Source ("PoolSource",
                             fileNames = readFiles,
                             secondaryFileNames = secFiles
                             )


#############L1 Trigger Block##################
process.load("Configuration.StandardSequences.RawToDigi_Data_cff")

process.p = cms.Path(
    process.RawToDigi
    +process.L1TProducer
)


###############################################
process.schedule = cms.Schedule(
    process.p,
    process.default
#    process.pat_step,
#    process.pat_tree
)



# output file
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('Tree_from_AOD.root')
)

