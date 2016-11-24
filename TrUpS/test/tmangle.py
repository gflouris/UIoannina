import FWCore.ParameterSet.VarParsing as VarParsing
import FWCore.ParameterSet.Config as cms
import os
import sys
import commands



options = VarParsing.VarParsing ('analysis')
options.register ('processor','',VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int,"Pocessor ID")
options.register ('wheel','',VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int,"Wheel ID")
options.parseArguments()

#print "processorid "+str(options.processor)
#print "wheelid "+str(options.wheel)


process = cms.Process("Analysis")
process.source = cms.Source("EmptySource")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1))


process.load('Configuration.Geometry.GeometryExtended2015_cff')
process.load('Configuration.Geometry.GeometryExtended2015Reco_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc', '')


#
# connect custom cabling map
#
#process.load("EventFilter.RPCRawToDigi.RPCSQLiteCabling_cfi")
#process.RPCCabling.connect = 'sqlite_file:RPCEMap10.db'
#process.RPCCabling.toGet[0].tag = 'RPCEMap_v3'
#process.es_prefer_RPCEMap = cms.ESPrefer("PoolDBESSource","RPCCabling");


process.angle= cms.EDAnalyzer("TMAngleAnalyser",
	processorid    = cms.int32(options.processor),
	wheelid     = cms.int32(options.wheel)
	)

process.p = cms.Path(process.angle)

