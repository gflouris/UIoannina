# -*- coding: utf-8 -*-
import FWCore.ParameterSet.Config as cms

from UIoannina.TrUpS.Ntuple_MC_cfg import *

process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(500)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.source = cms.Source ("PoolSource",
                             fileNames = cms.untracked.vstring(
'file:///afs/cern.ch/work/g/gflouris/TriggerUpgrade/CMSSW_8_0_0_pre6/src/L1Trigger/L1TMuonBarrel/test/l1tbmtf_mc_etam08p08_pt115120.root'

				)
                             )


#############L1 Trigger Block##################
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
   # fileName = cms.string('Ntuple_GEN_BMTF_test_no_sp.root')
     fileName = cms.string('Ntuple_l1tbmtf_mc_etam08p08_pt115120_etahitsrev.root')
)

