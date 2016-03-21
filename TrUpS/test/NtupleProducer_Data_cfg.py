# -*- coding: utf-8 -*-
import FWCore.ParameterSet.Config as cms

from UIoannina.TrUpS.Ntuple_MC_cfg import *

process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(500)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.source = cms.Source ("PoolSource",
                             fileNames = cms.untracked.vstring(
			'file:///afs/cern.ch/work/g/gflouris/TriggerUpgrade/Development/BMTF/CMSSW_8_0_2/src/L1Trigger/L1TMuonBarrel/test/l1tbmtf_data_Run266535.root'
				)
                             )




#############L1 Trigger Block##################
process.load("UIoannina.TrUpS.L1Producer_cfi")
process.L1TProducer.bmtfOutputDigis = cms.InputTag("BMTFStage2Digis:BMTF")

process.L1TProducerEmulator = process.L1TProducer.clone(
		bmtfOutputDigis = cms.InputTag("dataBmtfDigis:BMTF")
)


process.p = cms.Path(
    process.L1TProducer       
    +process.L1TProducerEmulator   
)

###############################################
process.schedule = cms.Schedule(
    process.p
)


process.options = cms.untracked.PSet(
#    wantSummary = cms.untracked.bool( outputSummary ),
    SkipEvent = cms.untracked.vstring('ProductNotFound')
)



# output file
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('Ntuple_BMTF_data_Run266535_test.root')
)

