from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

RUN_NUMBER = '274198'
config.General.requestName = 'BMTF_Ntuples2'
config.General.workArea = 'BMTF_Ntuples_Run'+RUN_NUMBER
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.allowUndistributedCMSSW = True
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'Ntuples_Unpack_reEmulate.py'

config.Data.inputDataset = '/ZeroBias/Run2016B-v2/RAW'
config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 5
#config.Data.lumiMask = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions12/8TeV/Prompt/Cert_190456-208686_8TeV_PromptReco_Collisions12_JSON.txt'
config.Data.runRange = RUN_NUMBER #'272716' # '193093-194075'
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = False

config.Site.storageSite = 'T2_GR_Ioannina' 

