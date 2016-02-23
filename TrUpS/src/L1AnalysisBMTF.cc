#include "UIoannina/TrUpS/interface/L1AnalysisBMTF.h"
#include <FWCore/Framework/interface/ConsumesCollector.h>
#include <FWCore/ParameterSet/interface/ParameterSet.h>
#include "DataFormats/L1TMuon/interface/RegionalMuonCand.h"
#include <sstream>
#include <iostream>
#include <string>     // std::string, std::stoi


TrUpS::L1AnalysisBMTF::L1AnalysisBMTF(edm::ConsumesCollector && ix)
{
}


TrUpS::L1AnalysisBMTF::~L1AnalysisBMTF()
{

}

void TrUpS::L1AnalysisBMTF::SetDTPH(const edm::Handle<L1MuDTChambPhContainer > L1MuDTChambPhContainer, unsigned int maxDTPH)
{

   L1MuDTChambPhContainer::Phi_Container const *PhContainer = L1MuDTChambPhContainer->getContainer();

   bmtf_.phSize = PhContainer->size();
   int iphtr=0;
   double pig=acos(-1);
   for( L1MuDTChambPhContainer::Phi_Container::const_iterator
       DTPhDigiItr =  PhContainer->begin() ;
       DTPhDigiItr != PhContainer->end() ;
       ++DTPhDigiItr )
    {
      if((unsigned int) iphtr>maxDTPH-1) continue;
      bmtf_.phBx.push_back     (  DTPhDigiItr->bxNum() - DTPhDigiItr->Ts2Tag()+1 );
      bmtf_.phBxRAW.push_back     (  DTPhDigiItr->bxNum() );
      bmtf_.phTs2Tag.push_back     ( DTPhDigiItr->Ts2Tag() );
      bmtf_.phWh.push_back     (  DTPhDigiItr->whNum() );
      bmtf_.phSe.push_back     (  DTPhDigiItr->scNum() );
      bmtf_.phSt.push_back     (  DTPhDigiItr->stNum() );
      bmtf_.phAng.push_back    (  DTPhDigiItr->phi()   );
      bmtf_.phBandAng.push_back(  DTPhDigiItr->phiB()  );
      double locphi = (((double)DTPhDigiItr->phi())/4096.0);
      double newphi = locphi+(DTPhDigiItr->scNum()*(pig/6.));
      if (newphi>2*pig) newphi-=2*pig;
      if (newphi<0    ) newphi+=2*pig;
      bmtf_.phGlobPhi.push_back(  newphi               );
      bmtf_.phCode.push_back   (  DTPhDigiItr->code()  );
      bmtf_.phX.push_back      (  DTPhDigiItr->scNum() );
      bmtf_.phY.push_back      (  DTPhDigiItr->stNum()+4*(DTPhDigiItr->whNum()+2) );

      iphtr++;
    }

}


void TrUpS::L1AnalysisBMTF::SetDTTH(const edm::Handle<L1MuDTChambThContainer > L1MuDTChambThContainer, unsigned int maxDTTH)
{

   L1MuDTChambThContainer::The_Container const *ThContainer = L1MuDTChambThContainer->getContainer();

   int ithtr=0;
   bmtf_.thSize = ThContainer->size();
   //bmtf_.thTheta.ResizeTo(bmtf_.thSize,7);
//   bmtf_.thCode.ResizeTo(bmtf_.thSize,7);


   for( L1MuDTChambThContainer::The_Container::const_iterator
	 DTThDigiItr =  ThContainer->begin() ;
       DTThDigiItr != ThContainer->end() ;
       ++DTThDigiItr )
     {

      if((unsigned int) ithtr>maxDTTH-1) continue;
      bmtf_.thBx.push_back( DTThDigiItr->bxNum()  );
      bmtf_.thWh.push_back( DTThDigiItr->whNum() );
      bmtf_.thSe.push_back( DTThDigiItr->scNum() );
      bmtf_.thSt.push_back( DTThDigiItr->stNum() );
      bmtf_.thX.push_back( DTThDigiItr->stNum()+4*(DTThDigiItr->whNum()+2) );
//	  int xpos = iwh*4+ist+1; ????
      bmtf_.thY.push_back( DTThDigiItr->scNum() );
	
	ostringstream  ss1, ss2; 
	ss1.clear(); ss2.clear();
        ss1<<"9"; ss2<<"9";


       if(DTThDigiItr->whNum()<=0) {
        for(int j=0; j<7; j++){
       //for ( int j = 6; j >= 0; j-- ) {
         ss1<<DTThDigiItr->position(j);
	 ss2<<DTThDigiItr->code(j) ;
        }

}

        else{
      for ( int j = 6; j >= 0; j-- ) {
            ss1<<DTThDigiItr->position(j);
            ss2<<DTThDigiItr->code(j) ;
        }
       }
        bmtf_.thTheta.push_back(stoi(ss1.str())) ;
         bmtf_.thCode.push_back(stoi(ss2.str()));
        

      ithtr++;

    }
}
/*
void TrUpS::L1AnalysisBMTF::SetMBTR(const edm::Handle<BMTrackContainer > BMTrackContainer, unsigned int maxMBTR)
{
  double pig=acos(-1);
  BMTrackContainer::TrackContainer const *tr =  BMTrackContainer->getContainer();
  int idttr = 0 ;
  bmtf_.trmbSize = tr->size();
  for ( BMTrackContainer::TrackContainer::const_iterator i
	  = tr->begin(); i != tr->end(); ++i ) {
        if((unsigned int)idttr>maxMBTR-1) continue;
	bmtf_.trmbBx.push_back(  i->bx() );
	bmtf_.trmbTag.push_back(  i->TrkTag() );
	bmtf_.trmbQual.push_back(  i->hwQual() );
	bmtf_.trmbPtPck.push_back(  i->hwPt() );
	bmtf_.trmbPhiPck.push_back(  i->hwPhi() );
	bmtf_.trmbEtaPck.push_back(  i->hwEta() );

        int phi_local = i->hwPhi();//range: 0 < phi_local < 31
        if(phi_local > 15) phi_local -= 32; //range: -16 < phi_local < 15
        double phi_global = (phi_local*(pig/72.))+((pig/6.)*i->scNum());// + 12*i->scNum(); //range: -16 < phi_global < 147
        if(phi_global < 0) phi_global+=2*pig; //range: 0 < phi_global < 147
        if(phi_global > 2*pig) phi_global-=2*pig; //range: 0 < phi_global < 143
	bmtf_.trmbPhiGlob.push_back(  phi_global );
	bmtf_.trmbChPck.push_back(  i->hwSign() );
	bmtf_.trmbWh.push_back(  i->whNum() );
	bmtf_.trmbSc.push_back(  i->scNum() );
	//bmtf_.trmbAddress.push_back( i->hwTrackAddress());

	idttr++;
  }

}
*/
void TrUpS::L1AnalysisBMTF::SetMBTF(const l1t::RegionalMuonCandBxCollection& coll, int& ctr, int bx) {

  for (auto mu = coll.begin(bx); mu != coll.end(bx); ++mu) {
      //cout<<ctr<<endl;
      ctr++;
      bmtf_.bmtfPt.push_back(mu->hwPt());
      bmtf_.bmtfEta.push_back(mu->hwEta());
      bmtf_.bmtfPhi.push_back(mu->hwPhi());
      bmtf_.bmtfqual.push_back(mu->hwQual());
      bmtf_.bmtfch.push_back(mu->hwSign());
      bmtf_.bmtfbx.push_back(bx);
      bmtf_.bmtfprocessor.push_back(mu->processor());
      bmtf_.bmtfFineBit.push_back(mu->hwHF());

     // bmtf_.bmtftrAddress.push_back(mu->hwTrackAddress());
      std::map<int, int>  trAdd;
      trAdd = mu->trackAddress();
      int wheel = pow(-1,trAdd[0]) * trAdd[1];
      bmtf_.bmtfwh.push_back(wheel);
      bmtf_.bmtftrAddress.push_back(trAdd[2]);
      bmtf_.bmtftrAddress.push_back(trAdd[3]);
      bmtf_.bmtftrAddress.push_back(trAdd[4]);
      bmtf_.bmtftrAddress.push_back(trAdd[5]);

    }
        bmtf_.bmtfSize = ctr;

}


void TrUpS::L1AnalysisBMTF::SetMBTR(const l1t::RegionalMuonCandBxCollection& coll, int& ctr, int bx) {

  for (auto mu = coll.begin(bx); mu != coll.end(bx); ++mu) {
      //cout<<ctr<<endl;
      ctr++;
      bmtf_.trmbPt.push_back(mu->hwPt());
      bmtf_.trmbEta.push_back(mu->hwEta());
      bmtf_.trmbPhi.push_back(mu->hwPhi());
      bmtf_.trmbqual.push_back(mu->hwQual());
      bmtf_.trmbch.push_back(mu->hwSign());
      bmtf_.trmbbx.push_back(bx);
      bmtf_.trmbprocessor.push_back(mu->processor());
      bmtf_.trmbFineBit.push_back(mu->hwHF());

    // bmtf_.bmtftrAddress.push_back(mu->hwTrackAddress());
       std::map<int, int>  trAdd;
      trAdd = mu->trackAddress();
      int wheel = pow(-1,trAdd[0]) * trAdd[1];
      bmtf_.trmbwh.push_back(wheel);
      bmtf_.trmbtrAddress.push_back(trAdd[2]);
      bmtf_.trmbtrAddress.push_back(trAdd[3]);
      bmtf_.trmbtrAddress.push_back(trAdd[4]);
      bmtf_.trmbtrAddress.push_back(trAdd[5]);


    }
    if(bx == 2)bmtf_.trmbSize = ctr;
}
