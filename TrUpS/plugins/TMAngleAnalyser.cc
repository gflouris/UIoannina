#include <vector>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <map>
#include <utility>
#include <algorithm>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "DataFormats/Common/interface/Handle.h"

#include "TrackingTools/Records/interface/TrackingComponentsRecord.h"
#include "DataFormats/DetId/interface/DetIdCollection.h"
#include "DataFormats/GeometryVector/interface/GlobalPoint.h"


#include "Geometry/DTGeometry/interface/DTGeometry.h"
#include "Geometry/DTGeometry/interface/DTChamber.h"
#include "DataFormats/MuonDetId/interface/DTChamberId.h"

#include "Geometry/RPCGeometry/interface/RPCRoll.h"
#include "Geometry/RPCGeometry/interface/RPCGeometry.h"

#include "Geometry/CSCGeometry/interface/CSCGeometry.h"
#include "Geometry/CSCGeometry/interface/CSCChamber.h"
#include "Geometry/CSCGeometry/interface/CSCLayer.h"
#include "Geometry/CSCGeometry/interface/CSCLayerGeometry.h"
#include "DataFormats/MuonDetId/interface/CSCDetId.h"

#include "CondFormats/RPCObjects/interface/RPCReadOutMapping.h"
#include "CondFormats/RPCObjects/interface/LinkBoardSpec.h"
#include "FWCore/Framework/interface/ESTransientHandle.h"
#include "CondFormats/RPCObjects/interface/RPCEMap.h"
#include "CondFormats/DataRecord/interface/RPCEMapRcd.h"

#include "CondFormats/RPCObjects/interface/DccSpec.h"
#include "CondFormats/RPCObjects/interface/LinkBoardElectronicIndex.h"
#include "CondFormats/RPCObjects/interface/LinkBoardPackedStrip.h"
#include "CondFormats/RPCObjects/interface/TriggerBoardSpec.h"
#include "CondFormats/RPCObjects/interface/LinkBoardSpec.h"

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"


typedef std::vector< std::pair< LinkBoardElectronicIndex, LinkBoardPackedStrip> > RawDataFrames;

class TMAngleAnalyser : public edm::EDAnalyzer {
public:
  TMAngleAnalyser (const edm::ParameterSet & cfg);
  virtual ~TMAngleAnalyser(){}
  virtual void beginJob() { std::cout << "begin Job" << std::endl; }
  virtual void beginRun(const edm::Run&,  const edm::EventSetup& es) {
    std::cout <<"beingRun " << std::endl;

    rpc2dt(es);
  }

  virtual void analyze(const edm::Event&, const edm::EventSetup& es) {
    //std::cout <<"analyze event" << std::endl;
  }

private:
  int localXX(int phi, int layer, int station);

  std::string lbNameforDetId(const RPCReadOutMapping* cabling, uint32_t rawDetId);
  void rpc2dt( const edm::EventSetup& es);
  int processor_id;
  int wheel_id;

};


TMAngleAnalyser::TMAngleAnalyser (const edm::ParameterSet & cfg) {

    processor_id        = cfg.getParameter<int>                       ("processorid");
    wheel_id        = cfg.getParameter<int>                       ("wheelid");

}





void TMAngleAnalyser::rpc2dt(const edm::EventSetup& es)
{

  edm::ESHandle<RPCGeometry> rpcGeometry;
  es.get<MuonGeometryRecord>().get(rpcGeometry);
  const std::vector<const RPCRoll*>& rolls = rpcGeometry->rolls();

  std::cout <<"size: " << rolls.size() << std::endl;

  std::vector<const RPCRoll*> sector1Rolls;
  for (auto & roll : rolls) {
    RPCDetId aId = roll->id();

    ///Region 0 for Barrel
     if  (aId.region()!=0)  continue;
     if ( ( aId.sector() != processor_id || aId.ring() != wheel_id) ) continue;

     sector1Rolls.push_back(roll);
  }//end of for


  std::cout <<" proc1 rolls: " << sector1Rolls.size() << std::endl;


  //
  //
  //
  edm::ESTransientHandle<RPCEMap> readoutMapping;
  es.get<RPCEMapRcd>().get(readoutMapping);
  const RPCReadOutMapping * cabling= readoutMapping->convert();
  std::cout <<" Has readout map, VERSION: " << cabling->version() << std::endl;

  std::map<std::string, std::vector<const RPCRoll* > > lbrolls;
  for (auto & roll : sector1Rolls) {
    RPCDetId rollDetId = roll->id();
    std::string lbName = lbNameforDetId(cabling, rollDetId);
    lbrolls[lbName].push_back(roll);
  }


  std::cout << " ROLL map size is: " << lbrolls.size() << std::endl;
  for (auto me : lbrolls) {
    std::string lbName = me.first;
    const RPCRoll * roll = me.second.front();
    RPCReadOutMapping::StripInDetUnit duFrame(roll->id(), 1);
    RawDataFrames rawDataFrames = cabling->rawDataFrame(duFrame);
    LinkBoardElectronicIndex eleIndex = rawDataFrames.front().first;
    const LinkBoardSpec *linkBoard = cabling->location(eleIndex);
    for (unsigned int lbChannel = 0; lbChannel <= 95; lbChannel++) {

      RPCReadOutMapping::StripInDetUnit duFrame = cabling->detUnitFrame(*linkBoard, LinkBoardPackedStrip(lbChannel) );
      uint32_t rawDetId = duFrame.first;
      int strip = duFrame.second;

      if (rawDetId && strip) {
        const RPCRoll* roll = rpcGeometry->roll(rawDetId);
        GlobalPoint stripPosition = roll->toGlobal(roll->centreOfStrip(strip));
        //LocalPoint  stripPositionlocal = roll->toLocal(stripPosition);
        unsigned int halfChannel = 2*lbChannel;

        // from phiGlobal to radialAngle of the primitive in sector sec in [1..12]
        //GlobalPoint p1cmPRG = roll->toGlobal(LocalPoint(1,0,0));
        //GlobalPoint m1cmPRG = roll->toGlobal(LocalPoint(-1,0,0));
        //int direction = (p1cmPRG.phi()-m1cmPRG.phi())/fabs((p1cmPRG.phi()-m1cmPRG.phi()));

        int iPhiHalfChannel;
        double globalphi = stripPosition.phi();
        //int localx = direction*stripPositionlocal.x();
//        double globalx = stripPosition.x();


        int sector = (roll->id()).sector();
        if ( sector == 1) iPhiHalfChannel = int( globalphi*1024. );
        else {
          if ( globalphi >= 0) iPhiHalfChannel = int( (globalphi-(sector-1)*Geom::pi()/6.)*1024. );
          else iPhiHalfChannel = int( (globalphi+(13-sector)*Geom::pi()/6.)*1024. );
        }
        int localx = localXX(iPhiHalfChannel, roll->id().layer(), roll->id().station());

        std::cout << std::setfill(' ')
                  << lbName
                  <<" " <<std::setw(10)<< roll->id().rawId()
                  <<" strip: "<< std::setw(3) << strip
                  << " lbChannel: "<< std::setw(3) <<  lbChannel
                  <<" halfChannel: "<<std::setw(4) << halfChannel
                  <<" phi: "<<std::setw(5) << iPhiHalfChannel
                  <<" x: "<<std::setw(5) << localx
                  <<" eta: 0 "<<std::setw(5)// << globalphi
//                  <<" x: "<<std::setw(5) << globalx
                  << std::endl;

        for (unsigned int lbChannelN = lbChannel+1; lbChannelN <= 95; lbChannelN++) {
          RPCReadOutMapping::StripInDetUnit duFrameN = cabling->detUnitFrame(*linkBoard, LinkBoardPackedStrip(lbChannelN) );
          uint32_t rawDetIdN = duFrameN.first;
          int stripN = duFrameN.second;
          if (rawDetIdN && stripN) {
            const RPCRoll* rollN = rpcGeometry->roll(rawDetIdN);
            GlobalPoint stripPositionN = rollN->toGlobal(rollN->centreOfStrip(stripN));
            //LocalPoint stripPositionNlocal = rollN->toLocal(stripPositionN);

            int iPhiHalfChannelMid;
            int iPhiHalfChannelNext;

            //double phi1 = stripPosition.phi(); double phi2 = stripPositionN.phi();

            //double globalphiN = ( (double)stripPosition.phi()+(double)stripPositionN.phi())/2.;
            double angle =  (double)stripPosition.phi();
            double angleN =  (double)stripPositionN.phi();

            //std::cout << "The type is: " << typeid(stripPosition.phi()).name() <<std::endl;

            // std::cout << "Average is: " << (stripPosition.phi()+stripPositionN.phi())/2. << "\t" << globalphiN << std::endl;
            // double globalphiN = (phi1+phi2)/2.;
            if ( sector == 1) {
              //radialAngleN = int( globalphiN*1024 );
              iPhiHalfChannelMid = std::lround( (angle+angleN)/2.*1024. );
              iPhiHalfChannelNext = std::lround( angleN * 1024.);

            }
            else {
              if ( angle >= 0) {
                iPhiHalfChannelMid = int( (((angle+angleN)/2.)-(sector-1)*Geom::pi()/6)*1024 );
                iPhiHalfChannelNext = int( (angleN-(sector-1)*Geom::pi()/6)*1024 );
              }
              else {
                iPhiHalfChannelMid = int( (((angle+angleN)/2.)+(13-sector)*Geom::pi()/6)*1024 );
                iPhiHalfChannelNext = int( (angleN+(13-sector)*Geom::pi()/6)*1024 );
              }
            }

            //int localxMid = direction*((double)stripPositionlocal.x() + (double)stripPositionNlocal.x())/2.;
            //int localxNext = direction*(double)stripPositionNlocal.x();

            int localxMid = localXX(iPhiHalfChannelMid, rollN->id().layer(), rollN->id().station());
            int localxNext = localXX(iPhiHalfChannelNext, rollN->id().layer(), rollN->id().station());

           // double globalxN = stripPositionN.x();
           unsigned int halfChannelMid = lbChannel+lbChannelN;

           for (unsigned int halfChannelHole = 2*lbChannel+1; halfChannelHole <2*lbChannelN; halfChannelHole++) {
             int iPhiHC =   (halfChannelHole < halfChannelMid ) ? iPhiHalfChannel
                          : (halfChannelHole > halfChannelMid ) ? iPhiHalfChannelNext : iPhiHalfChannelMid ;

            int iXHC =   (halfChannelHole < halfChannelMid ) ? localx
                         : (halfChannelHole > halfChannelMid ) ? localxNext : localxMid ;



              std::cout << std::setfill(' ')
                      << lbName
                      <<" " <<std::setw(10)<< 0
                      <<" strip: "<< std::setw(3) <<     0
                      << " lbChannel: "<< std::setw(3) <<        0
                      <<" halfChannel: "<<std::setw(4) << halfChannelHole
                      <<" phi: "<<std::setw(5) << iPhiHC
                      <<" x: "<<std::setw(5) << iXHC
                      <<" eta: 0 "<<std::setw(5)// << globalphiN  <<"\t"<<stripPosition.phi()<<"\t"<<stripPositionN.phi()
//                      <<" x: "<<std::setw(5) << globalxN
                      << std::endl;
            }



            break;
          }
        }///end of for lbChannelsN
      }
    }///end of for lbChannels
  }///end of for lbrolls
}

std::string TMAngleAnalyser::lbNameforDetId(const RPCReadOutMapping* cabling, uint32_t rawDetId)
{
  RPCReadOutMapping::StripInDetUnit duFrame(rawDetId, 1);
  RawDataFrames rawDataFrames = cabling->rawDataFrame(duFrame);

  std::string lbName = "unknown";
  std::vector<const DccSpec*> dccs = cabling->dccList();
  for (std::vector<const DccSpec*>::const_iterator it1= dccs.begin(); it1!= dccs.end(); ++it1) {
    const std::vector<TriggerBoardSpec> & rmbs = (*it1)->triggerBoards();
    for (std::vector<TriggerBoardSpec>::const_iterator it2 = rmbs.begin(); it2 != rmbs.end(); ++it2) {
      const  std::vector<LinkConnSpec> & links = it2->linkConns();
      for (std::vector<LinkConnSpec>::const_iterator it3 = links.begin(); it3 != links.end(); ++it3) {
        const  std::vector<LinkBoardSpec> & lbs = it3->linkBoards();
        for (std::vector<LinkBoardSpec>::const_iterator it4=lbs.begin(); it4 != lbs.end(); ++it4) {
          LinkBoardElectronicIndex ele = { (*it1)->id(), it2->dccInputChannelNum(), it3->triggerBoardInputNumber(), it4->linkBoardNumInLink()};
          for (auto fr : rawDataFrames) {
            if (    fr.first.dccId == ele.dccId
                 && fr.first.dccInputChannelNum == ele.dccInputChannelNum
                 && fr.first.tbLinkInputNum == ele.tbLinkInputNum
                 && fr.first.lbNumInLink == ele.lbNumInLink
                    ) return it4->linkBoardName();
          }
        }
      }
    }
  }
  return std::string("unknown");
}


int TMAngleAnalyser::localXX(int phi, int layer, int station){
  //R[stat][layer] - radius of rpc station/layer from center of CMS
  phi = phi << 2;
  if(station>2) return 0;
  double R[2][2] = {{410.0,444.8},{492.7,527.3}};
  double rvalue = R[station-1][layer-1]*tan(phi/4096.);
  //std::cout<<phi<<"   "<<layer<<"   "<<station<<"   "<<rvalue<<std::endl;
  return rvalue;

}

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(TMAngleAnalyser);
