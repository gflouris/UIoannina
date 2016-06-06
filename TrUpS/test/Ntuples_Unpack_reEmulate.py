# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: SingleElectronPt10_cfi.py -s GEN,SIM,DIGI,L1 --pileup=NoPileUp --geometry DB --conditions=auto:startup -n 1 --no_exec
import FWCore.ParameterSet.Config as cms


# options
process = cms.Process('Raw2Digi')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.source = cms.Source ("NewEventStreamFileReader",  #"PoolSource",
#process.source = cms.Source ("PoolSource",
 
       fileNames=cms.untracked.vstring(
'/store/t0streamer/Data/PhysicsMuons/000/274/198/run274198_ls0082_streamPhysicsMuons_StorageManager.dat',
'/store/t0streamer/Data/PhysicsMuons/000/274/198/run274198_ls0083_streamPhysicsMuons_StorageManager.dat'
        ),
    )

# N events
process.maxEvents = cms.untracked.PSet(
#    input = cms.untracked.int32(options.maxEvents)
     input = cms.untracked.int32(-1)
)

process.load("FWCore.MessageLogger.MessageLogger_cfi")

process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1000)
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(False))

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:startup', '')


# dump raw data
process.dumpRaw = cms.EDAnalyzer( 
    "DumpFEDRawDataProduct",
    label = cms.untracked.string("rawDataCollector"),
    feds = cms.untracked.vint32 ( 1376,1377 ),
    dumpPayload = cms.untracked.bool ( False )
)

# validation event filter
process.load('EventFilter.L1TRawToDigi.validationEventFilter_cfi')

# raw to digi
process.load('EventFilter.L1TRawToDigi.l1tRawtoDigiBMTF_cfi')
#process.BMTFStage2Digis.InputLabel = cms.InputTag('stage2MPRaw')




# PostLS1 geometry used
process.load('Configuration.Geometry.GeometryExtended2015Reco_cff')
process.load('Configuration.Geometry.GeometryExtended2015_cff')
############################
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc', '')


####Event Setup Producer
process.load('L1Trigger.L1TMuonBarrel.fakeBmtfParams_cff')
process.esProd = cms.EDAnalyzer("EventSetupRecordDataGetter",
   toGet = cms.VPSet(
      cms.PSet(record = cms.string('L1TMuonBarrelParamsRcd'),
               data = cms.vstring('L1TMuonBarrelParams'))
                   ),
   verbose = cms.untracked.bool(True)
)
process.fakeBmtfParams.fwVersion = cms.uint32(2)
#process.fakeBmtfParams.EtaTrackFinder = cms.bool(False)
process.fakeBmtfParams.BX_max = cms.int32(2)
process.fakeBmtfParams.BX_min = cms.int32(-2)

maskenable      = '000000000000'
maskdisable     = '111111111111'
process.fakeBmtfParams.mask_phtf_st1        = cms.vstring(maskdisable, maskenable, maskenable, maskenable, maskenable, maskenable, maskdisable)
process.fakeBmtfParams.mask_phtf_st2        = cms.vstring(maskenable,  maskenable, maskenable, maskenable, maskenable, maskenable, maskenable)
process.fakeBmtfParams.mask_phtf_st3        = cms.vstring(maskenable,  maskenable, maskenable, maskenable, maskenable, maskenable, maskenable)
process.fakeBmtfParams.mask_phtf_st4        = cms.vstring(maskenable,  maskenable, maskenable, maskenable, maskenable, maskenable, maskenable)

process.fakeBmtfParams.mask_ettf_st1        = cms.vstring(maskdisable, maskenable, maskenable, maskenable, maskenable, maskenable, maskdisable)
process.fakeBmtfParams.mask_ettf_st2        = cms.vstring(maskenable,  maskenable, maskenable, maskenable, maskenable, maskenable, maskenable)
process.fakeBmtfParams.mask_ettf_st3        = cms.vstring(maskenable,  maskenable, maskenable, maskenable, maskenable, maskenable, maskenable)
####BMTF Emulator
#process.load('L1Trigger.L1TMuonBarrel.simTwinMuxDigis_cfi')
process.load('L1Trigger.L1TMuonBarrel.simBmtfDigis_cfi')
process.simBmtfDigis.Debug = cms.untracked.int32(0)
process.simBmtfDigis.DTDigi_Source = cms.InputTag("BMTFStage2Digis")
process.simBmtfDigis.DTDigi_Theta_Source = cms.InputTag("BMTFStage2Digis")



process.dumpED = cms.EDAnalyzer("EventContentAnalyzer")
process.dumpES = cms.EDAnalyzer("PrintEventSetupContent")

####Ntuple Block
process.load("UIoannina.TrUpS.L1Producer_cfi")
process.L1TProducer.bmtfOutputDigis = cms.InputTag("BMTFStage2Digis:BMTF")
process.L1TProducer.bmtfInputPhDigis = cms.InputTag("BMTFStage2Digis")
process.L1TProducer.bmtfInputThDigis = cms.InputTag("BMTFStage2Digis")

process.L1TProducerEmulator = process.L1TProducer.clone(
        bmtfOutputDigis = cms.InputTag("simBmtfDigis:BMTF")
)
process.load("UIoannina.TrUpS.EVRProducer_cfi")



# Path and EndPath definitions
process.path = cms.Path(
#    process.validationEventFilter
#    +process.dumpRaw
    process.BMTFStage2Digis
    +process.esProd
    +process.simBmtfDigis
    +process.EVRTProducer
    +process.L1TProducer
    +process.L1TProducerEmulator

)

# output file
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('Ntuple_BMTF_data_Run274198.root')
)


# optional EDM file
process.output = cms.OutputModule(
        "PoolOutputModule",
        outputCommands = cms.untracked.vstring("drop *",
                                               "keep *_BMTFStage2Digis_*_*",
                                               "keep *_simBmtfDigis_*_*"),

        fileName = cms.untracked.string('l1tBMTF_EDM_OUTNUM.root')
)

#process.out = cms.EndPath(
#        process.output
#)
   
    
