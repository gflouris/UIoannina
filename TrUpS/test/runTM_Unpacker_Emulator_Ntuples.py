import FWCore.ParameterSet.Config as cms

process = cms.Process("TwinMuxRawToDigi")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = "80X_dataRun2_Express_v10"

process.load("EventFilter.RPCRawToDigi.rpcUnpackingModule_cfi")
process.load("CondTools.RPC.RPCLinkMap_sqlite_cff")
process.load("EventFilter.L1TXRawToDigi.twinMuxStage2Digis_cfi")
process.load("EventFilter.RPCRawToDigi.RPCTwinMuxRawToDigi_cfi")
process.load('EventFilter.L1TRawToDigi.l1tRawtoDigiBMTF_cfi')

process.RPCTwinMuxRawToDigi.bxMin = cms.int32(-5)
process.RPCTwinMuxRawToDigi.bxMax = cms.int32(5)

process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )


process.source = cms.Source ("NewEventStreamFileReader",  #"PoolSource",
#process.source = cms.Source ("PoolSource",
 
       fileNames=cms.untracked.vstring(
#'file:///afs/cern.ch/work/g/gflouris/TriggerUpgrade/Development/TwinMux/Emulator_Unpacker/CMSSW_8_0_11/src/UIoannina/TrUpS/test/Data/run280364_ls0111_streamPhysicsMuons_StorageManager.dat',
  #'/store/t0streamer/Data/ExpressCosmics/000/280/992/run280992_ls0100_streamExpressCosmics_StorageManager.dat',
  #'/store/t0streamer/Data/ExpressCosmics/000/280/992/run280992_ls0101_streamExpressCosmics_StorageManager.dat',
  #'/store/t0streamer/Data/ExpressCosmics/000/280/992/run280992_ls0102_streamExpressCosmics_StorageManager.dat',
  #'/store/t0streamer/Data/ExpressCosmics/000/280/992/run280992_ls0103_streamExpressCosmics_StorageManager.dat',
  #'/store/t0streamer/Data/ExpressCosmics/000/280/992/run280992_ls0104_streamExpressCosmics_StorageManager.dat',
#'/store/t0streamer/Data/PhysicsMuons/000/281/614/run281614_ls0330_streamPhysicsMuons_StorageManager.dat',
#'/store/t0streamer/Data/PhysicsMuons/000/281/614/run281614_ls0331_streamPhysicsMuons_StorageManager.dat',
#'/store/t0streamer/Data/PhysicsMuons/000/281/614/run281614_ls0332_streamPhysicsMuons_StorageManager.dat',
#'/store/t0streamer/Data/PhysicsMuons/000/281/614/run281614_ls0333_streamPhysicsMuons_StorageManager.dat',
#'/store/t0streamer/Data/PhysicsMuons/000/281/614/run281614_ls0334_streamPhysicsMuons_StorageManager.dat',
#'/store/t0streamer/Data/PhysicsMuons/000/281/614/run281614_ls0335_streamPhysicsMuons_StorageManager.dat',
'/store/t0streamer/Data/ExpressCosmics/000/281/614/run281614_ls0020_streamExpressCosmics_StorageManager.dat',
'/store/t0streamer/Data/ExpressCosmics/000/281/614/run281614_ls0021_streamExpressCosmics_StorageManager.dat',
'/store/t0streamer/Data/ExpressCosmics/000/281/614/run281614_ls0022_streamExpressCosmics_StorageManager.dat',
'/store/t0streamer/Data/ExpressCosmics/000/281/614/run281614_ls0023_streamExpressCosmics_StorageManager.dat',
'/store/t0streamer/Data/ExpressCosmics/000/281/614/run281614_ls0024_streamExpressCosmics_StorageManager.dat',


# 'file:///afs/cern.ch/work/g/gflouris/TriggerUpgrade/Development/TwinMux/Emulator_Unpacker/CMSSW_8_0_11/src/UIoannina/TrUpS/test/Data/run280992_ls0104_streamExpressCosmics_StorageManager.dat'


# '/store/t0streamer/Data/PhysicsMuons/000/280/364/run280364_ls0188_streamPhysicsMuons_StorageManager.dat',
# '/store/t0streamer/Data/PhysicsMuons/000/280/364/run280364_ls0189_streamPhysicsMuons_StorageManager.dat',
# '/store/t0streamer/Data/PhysicsMuons/000/280/364/run280364_ls0190_streamPhysicsMuons_StorageManager.dat',
# '/store/t0streamer/Data/PhysicsMuons/000/280/364/run280364_ls0191_streamPhysicsMuons_StorageManager.dat',
# '/store/t0streamer/Data/PhysicsMuons/000/280/364/run280364_ls0192_streamPhysicsMuons_StorageManager.dat',
# '/store/t0streamer/Data/PhysicsMuons/000/280/364/run280364_ls0193_streamPhysicsMuons_StorageManager.dat',
# '/store/t0streamer/Data/PhysicsMuons/000/280/364/run280364_ls0194_streamPhysicsMuons_StorageManager.dat',
# '/store/t0streamer/Data/PhysicsMuons/000/280/364/run280364_ls0195_streamPhysicsMuons_StorageManager.dat',
# '/store/t0streamer/Data/PhysicsMuons/000/280/364/run280364_ls0196_streamPhysicsMuons_StorageManager.dat',
# '/store/t0streamer/Data/PhysicsMuons/000/280/364/run280364_ls0197_streamPhysicsMuons_StorageManager.dat',
# '/store/t0streamer/Data/PhysicsMuons/000/280/364/run280364_ls0198_streamPhysicsMuons_StorageManager.dat',
        ),


#Run = 280992   Event = 6101256   Lumi = 104
#Run = 280992   Event = 6117067   Lumi = 104
#Run = 280992   Event = 6119708   Lumi = 104

#eventsToProcess=cms.untracked.VEventRange('281614:334:163164542-281614:334:163164542')
    )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1))

# PostLS1 geometry used
process.load('Configuration.Geometry.GeometryExtended2015Reco_cff')
process.load('Configuration.Geometry.GeometryExtended2015_cff')
############################
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc', '')


####Event Setup Producer
process.load('L1Trigger.L1TwinMux.fakeTwinMuxParams_cff')

process.esProd = cms.EDAnalyzer("EventSetupRecordDataGetter",
   toGet = cms.VPSet(
      cms.PSet(record = cms.string('L1TwinMuxParamsRcd'),
               data = cms.vstring('L1TwinMuxParams'))      
              ),
   verbose = cms.untracked.bool(True)
)

###TwinMux Emulator
process.load('L1Trigger.L1TwinMux.simTwinMuxDigis_cfi')
process.simTwinMuxDigisEmu.DTDigi_Source = cms.InputTag("twinMuxStage2Digis:PhIn")
process.simTwinMuxDigisEmu.DTThetaDigi_Source = cms.InputTag("twinMuxStage2Digis:ThIn")
process.simTwinMuxDigisEmu.RPC_Source = cms.InputTag("RPCTwinMuxRawToDigi")

process.fakeTwinMuxParams.useRpcBxForDtBelowQuality = cms.uint32(4)
process.fakeTwinMuxParams.verbose = cms.bool(False)
process.fakeTwinMuxParams.useOnlyDT = cms.bool(True)
#process.fakeTwinMuxParams.CorrectDTBxwRPC           = cms.bool(False)


process.dumpED = cms.EDAnalyzer("EventContentAnalyzer")
process.dumpES = cms.EDAnalyzer("PrintEventSetupContent")




#########################################
##########Ntuples Block#################
########################################
process.load("UIoannina.TrUpS.L1TwinMuxProducer")

process.L1TwinMuxProducer = process.L1TwinMuxProducer.clone(
     twinmuxOutputDigis = cms.InputTag("twinMuxStage2Digis:PhOut"),
     twinmuxInputPhDigis = cms.InputTag("twinMuxStage2Digis:PhIn"),
       twinmuxInputThDigis = cms.InputTag("twinMuxStage2Digis:ThIn"),
     twinmuxInputRPCDigis = cms.InputTag("RPCTwinMuxRawToDigi")

)

process.L1TwinMuxProducerEmulator = process.L1TwinMuxProducer.clone(
     twinmuxOutputDigis = cms.InputTag("simTwinMuxDigisEmu:TwinMuxEmulator"),
     twinmuxInputPhDigis = cms.InputTag("twinMuxStage2Digis:PhIn"),
        twinmuxInputThDigis = cms.InputTag("twinMuxStage2Digis:ThIn"),
     twinmuxInputRPCDigis = cms.InputTag("RPCTwinMuxRawToDigi")

)
process.load("UIoannina.TrUpS.EVRProducer_cfi")


# output file
process.TFileService = cms.Service("TFileService",
     fileName = cms.string('Ntuples/Ntuple_l1ttwinmux_data_run281614.root')
)

############################

process.load("UIoannina.TrUpS.L1Producer_cfi")
process.L1TProducer.bmtfOutputDigis = cms.InputTag("BMTFStage2Digis:BMTF")
process.L1TProducer.bmtfInputPhDigis = cms.InputTag("BMTFStage2Digis:PhiDigis")
process.L1TProducer.bmtfInputThDigis = cms.InputTag("BMTFStage2Digis:TheDigis")


process.L1TMuonSeq = cms.Sequence(process.RPCTwinMuxRawToDigi
                     + process.twinMuxStage2Digis
                     + process.rpcUnpackingModule
                     + process.esProd
                     + process.simTwinMuxDigisEmu                     
                     + process.EVRTProducer
                     + process.L1TwinMuxProducer    
                     + process.L1TwinMuxProducerEmulator  
                     + process.BMTFStage2Digis
                     + process.L1TProducer

)


process.L1TMuonPath = cms.Path(process.L1TMuonSeq)

# process.out = cms.OutputModule("PoolOutputModule", 
#     outputCommands = cms.untracked.vstring(
#         'drop *',
#         #'keep *CSC*_*_*_*',
#         'keep *RPC*_*_*_*',
#         'keep *DT*_*_*_*',
#         'keep *L1Mu*_*_*_*',
#         'keep *_*Muon*_*_*',
#         'keep *_*gen*_*_*',
#         'keep *_*TwinMux*_*_*',
#         'keep *_*BMTF*_*_*',
#         'keep GenEventInfoProduct_generator_*_*'),
 
#   fileName = cms.untracked.string("l1ttwinmux_edm.root")
# )

#process.output_step = cms.EndPath(process.out)
process.schedule = cms.Schedule(process.L1TMuonPath)
#process.schedule.extend([process.output_step])
