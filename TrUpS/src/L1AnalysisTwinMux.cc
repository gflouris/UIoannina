#include "UIoannina/TrUpS/interface/L1AnalysisTwinMux.h"
#include <FWCore/Framework/interface/ConsumesCollector.h>
#include <FWCore/ParameterSet/interface/ParameterSet.h>
#include "DataFormats/L1TMuon/interface/RegionalMuonCand.h"

#include <sstream>

TrUpS::L1AnalysisTwinMux::L1AnalysisTwinMux(edm::ConsumesCollector && ix)
{
}


TrUpS::L1AnalysisTwinMux::~L1AnalysisTwinMux()
{

}

void TrUpS::L1AnalysisTwinMux::SetDTPH(const edm::Handle<L1MuDTChambPhContainer > L1MuDTChambPhContainer, unsigned int maxDTPH)
{

   L1MuDTChambPhContainer::Phi_Container const *PhContainer = L1MuDTChambPhContainer->getContainer();

   //twinmux_.phSize = PhContainer->size();
   int iphtr=0;
   for( L1MuDTChambPhContainer::Phi_Container::const_iterator
       DTPhDigiItr =  PhContainer->begin() ;
       DTPhDigiItr != PhContainer->end() ;
       ++DTPhDigiItr )
    {
      if((unsigned int) iphtr>maxDTPH-1) continue;
      if(DTPhDigiItr->code()==7) continue;
      twinmux_.phBx.push_back     (  DTPhDigiItr->bxNum() );
      twinmux_.phTs2Tag.push_back     ( DTPhDigiItr->Ts2Tag() );
      twinmux_.phWh.push_back     (  DTPhDigiItr->whNum() );
      twinmux_.phSe.push_back     (  DTPhDigiItr->scNum() );
      twinmux_.phSt.push_back     (  DTPhDigiItr->stNum() );
      twinmux_.phAng.push_back    (  DTPhDigiItr->phi()   );
      twinmux_.phBandAng.push_back(  DTPhDigiItr->phiB()  );
      twinmux_.phCode.push_back   (  DTPhDigiItr->code()  );

      iphtr++;
    }

   twinmux_.phSize = iphtr;

}



void TrUpS::L1AnalysisTwinMux::SetTwinMux(const edm::Handle<L1MuDTChambPhContainer > L1MuDTChambPhContainer, unsigned int maxDTPH)
{

   L1MuDTChambPhContainer::Phi_Container const *PhContainer = L1MuDTChambPhContainer->getContainer();

//   twinmux_.tmSize = PhContainer->size();
   int iphtr=0;
   for( L1MuDTChambPhContainer::Phi_Container::const_iterator
       DTPhDigiItr =  PhContainer->begin() ;
       DTPhDigiItr != PhContainer->end() ;
       ++DTPhDigiItr )
    {
      if((unsigned int) iphtr>maxDTPH-1) continue;
      if(DTPhDigiItr->code()==7) continue;
      twinmux_.tmBx.push_back     (  DTPhDigiItr->bxNum() );
      twinmux_.tmTs2Tag.push_back     ( DTPhDigiItr->Ts2Tag() );
      twinmux_.tmWh.push_back     (  DTPhDigiItr->whNum() );
      twinmux_.tmSe.push_back     (  DTPhDigiItr->scNum() );
      twinmux_.tmSt.push_back     (  DTPhDigiItr->stNum() );
      twinmux_.tmAng.push_back    (  DTPhDigiItr->phi()   );
      twinmux_.tmBandAng.push_back(  DTPhDigiItr->phiB()  );
      twinmux_.tmCode.push_back   (  DTPhDigiItr->code()  );
      twinmux_.tmRpcBit.push_back   (  DTPhDigiItr->RpcBit()  );

      iphtr++;
    }
   twinmux_.tmSize = iphtr;

}


void TrUpS::L1AnalysisTwinMux::SetDTTH(const edm::Handle<L1MuDTChambThContainer > L1MuDTChambThContainer, unsigned int maxDTTH)
{

   L1MuDTChambThContainer::The_Container const *ThContainer = L1MuDTChambThContainer->getContainer();

   int ithtr=0;
   twinmux_.thSize = ThContainer->size();

   for( L1MuDTChambThContainer::The_Container::const_iterator
	 DTThDigiItr =  ThContainer->begin() ;
       DTThDigiItr != ThContainer->end() ;
       ++DTThDigiItr )
     {

      if((unsigned int) ithtr>maxDTTH-1) continue;
      twinmux_.thBx.push_back( DTThDigiItr->bxNum()  );
      twinmux_.thWh.push_back( DTThDigiItr->whNum() );
      twinmux_.thSe.push_back( DTThDigiItr->scNum() );
      twinmux_.thSt.push_back( DTThDigiItr->stNum() );

      ostringstream  ss1, ss2; 
      ss1.clear(); ss2.clear();
      ss1<<"9"; ss2<<"9";

      for(int j=0; j<7; j++){
        ss1<<DTThDigiItr->position(j);
         ss2<<DTThDigiItr->code(j) ;
      }
      twinmux_.thTheta.push_back(stoi(ss1.str())) ;
      twinmux_.thCode.push_back(stoi(ss2.str()));

      ithtr++;

    }
}





void TrUpS::L1AnalysisTwinMux::SetRPC(RPCDigiCollection m_rpcDigis)
{
  int rpcsize = 0;
  for( auto chamber = m_rpcDigis.begin(); chamber != m_rpcDigis.end(); ++chamber ) {

           RPCDetId detid = (*chamber).first;

               for( auto digi = (*chamber).second.first ; digi != (*chamber).second.second; ++digi ) {
                   twinmux_.rpcBx.push_back(digi->bx());
                   twinmux_.rpcWh.push_back(detid.ring());
                   twinmux_.rpcSe.push_back(detid.sector());
                   twinmux_.rpcSt.push_back(detid.station());
                   twinmux_.rpcLayer.push_back(detid.layer());
                   twinmux_.rpcStrip.push_back(digi->strip());
                   rpcsize++;

               }///for digicout

    }///for chamber   
    
    twinmux_.rpcSize = rpcsize;
 
}
