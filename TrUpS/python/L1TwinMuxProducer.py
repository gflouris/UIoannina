import FWCore.ParameterSet.Config as cms

L1TwinMuxProducer = cms.EDAnalyzer("L1TwinMuxTreeProducer",
    twinmuxInputPhDigis = cms.InputTag("simDtTriggerPrimitiveDigis"),
    twinmuxInputThDigis = cms.InputTag("simDtTriggerPrimitiveDigis"),
    twinmuxInputRPCDigis = cms.InputTag("simMuonRPCDigis"),

)

