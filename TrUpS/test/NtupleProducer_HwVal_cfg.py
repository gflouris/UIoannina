# -*- coding: utf-8 -*-
import FWCore.ParameterSet.Config as cms

from UIoannina.TrUpS.Ntuple_MC_cfg import *
process.load('FWCore.MessageLogger.MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.source = cms.Source ("PoolSource",
                             fileNames = cms.untracked.vstring(
				'file:///home/gflouris/DTTF/uBMTF/newNtuples/CMSSW_7_5_0_pre1/src/L1Trigger/L1BarrelMuonTrackFinder/test/l1tmuon_test.root'

				)
                             )


process.load("Configuration.StandardSequences.RawToDigi_Data_cff")
process.load("UIoannina.TrUpS.L1Producer_cfi")

process.p = cms.Path(
    process.L1TProducer    
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
    fileName = cms.string('Tree_SingleMuPt120_Phi_test.root')
)

