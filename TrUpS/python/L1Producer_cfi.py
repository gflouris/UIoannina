import FWCore.ParameterSet.Config as cms

L1TProducer = cms.EDAnalyzer("L1TreeProducer",
	dttfDigis = cms.InputTag("dttfDigis"),
	trInputTag = cms.InputTag("dttfDigis:DATA:"),
	trInputTagDTTF = cms.InputTag("dttfDigis:DTTF:"),
	gtDigis   = cms.InputTag("gtDigis"),
	bmtfEmulator   = cms.InputTag("simBmtfDigis"),
	mbtrInputTag   = cms.InputTag("simBmtfDigis:DATA:"),
	mbtrInputTagBMTF   = cms.InputTag("simBmtfDigis:UnsortedBMTF:"),
        mbtrInputTagBM   = cms.InputTag("simBmtfDigis:BMTF:")



)

