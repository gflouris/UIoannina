#include "UIoannina/TrUpS/interface/L1AnalysisDTTF.h"



TrUpS::L1AnalysisDTTF::L1AnalysisDTTF()
{	     
}


TrUpS::L1AnalysisDTTF::~L1AnalysisDTTF()
{

}

void TrUpS::L1AnalysisDTTF::SetDTPH(const edm::Handle<L1MuDTChambPhContainer > L1MuDTChambPhContainer, unsigned int maxDTPH)
{
   
   L1MuDTChambPhContainer::Phi_Container const *PhContainer = L1MuDTChambPhContainer->getContainer();
    
   dttf_.phSize = PhContainer->size();
   int iphtr=0;
   double pig=acos(-1);
   for( L1MuDTChambPhContainer::Phi_Container::const_iterator 
       DTPhDigiItr =  PhContainer->begin() ;
       DTPhDigiItr != PhContainer->end() ;
       ++DTPhDigiItr ) 
    {        
      if((unsigned int) iphtr>maxDTPH-1) continue;
      dttf_.phBx.push_back     (  DTPhDigiItr->bxNum() - DTPhDigiItr->Ts2Tag()+1 );
      dttf_.phBxRAW.push_back     (  DTPhDigiItr->bxNum() );
      dttf_.phTs2Tag.push_back     ( DTPhDigiItr->Ts2Tag() );
      dttf_.phWh.push_back     (  DTPhDigiItr->whNum() );
      dttf_.phSe.push_back     (  DTPhDigiItr->scNum() );
      dttf_.phSt.push_back     (  DTPhDigiItr->stNum() );
      dttf_.phAng.push_back    (  DTPhDigiItr->phi()   );
      dttf_.phBandAng.push_back(  DTPhDigiItr->phiB()  );
      double locphi = (((double)DTPhDigiItr->phi())/4096.0);
      double newphi = locphi+(DTPhDigiItr->scNum()*(pig/6.));
      if (newphi>2*pig) newphi-=2*pig;
      if (newphi<0    ) newphi+=2*pig;
      dttf_.phGlobPhi.push_back(  newphi               );
      dttf_.phCode.push_back   (  DTPhDigiItr->code()  );
      dttf_.phX.push_back      (  DTPhDigiItr->scNum() );
      dttf_.phY.push_back      (  DTPhDigiItr->stNum()+4*(DTPhDigiItr->whNum()+2) );
      
      iphtr++;
    } 
  
}


void TrUpS::L1AnalysisDTTF::SetDTTH(const edm::Handle<L1MuDTChambThContainer > L1MuDTChambThContainer, unsigned int maxDTTH)
{
   
   L1MuDTChambThContainer::The_Container const *ThContainer = L1MuDTChambThContainer->getContainer();

   int ithtr=0;
   dttf_.thSize = ThContainer->size();
   dttf_.thTheta.ResizeTo(dttf_.thSize,7);
   dttf_.thCode.ResizeTo(dttf_.thSize,7);  


   for( L1MuDTChambThContainer::The_Container::const_iterator 
	 DTThDigiItr =  ThContainer->begin() ;
       DTThDigiItr != ThContainer->end() ;
       ++DTThDigiItr ) 
     {  
     
      if((unsigned int) ithtr>maxDTTH-1) continue;
      dttf_.thBx.push_back( DTThDigiItr->bxNum() + 1 );
      dttf_.thWh.push_back( DTThDigiItr->whNum() );
      dttf_.thSe.push_back( DTThDigiItr->scNum() );
      dttf_.thSt.push_back( DTThDigiItr->stNum() );
      dttf_.thX.push_back( DTThDigiItr->stNum()+4*(DTThDigiItr->whNum()+2) );
//	  int xpos = iwh*4+ist+1; ????
      dttf_.thY.push_back( DTThDigiItr->scNum() );
      //!

      for (unsigned int j = 0; j < 7; j++)
	{
         dttf_.thTheta[ithtr][j] = DTThDigiItr->position(j);
         dttf_.thCode[ithtr][j]  = DTThDigiItr->code(j);
	}
      
      ithtr++;
     
    }
}


void TrUpS::L1AnalysisDTTF::SetDTTR(const edm::Handle<L1MuDTTrackContainer > L1MuDTTrackContainer, unsigned int maxDTTR)
{
  double pig=acos(-1);
  L1MuDTTrackContainer::TrackContainer const *tr =  L1MuDTTrackContainer->getContainer();
  int idttr = 0 ;
  dttf_.trSize = tr->size();
  for ( L1MuDTTrackContainer::TrackContainer::const_iterator i 
	  = tr->begin(); i != tr->end(); ++i ) {
        if((unsigned int)idttr>maxDTTR-1) continue;	
	dttf_.trBx.push_back(  i->bx()+1 );  
	dttf_.trTag.push_back(  i->TrkTag() );  
	dttf_.trQual.push_back(  i->quality_packed() ); 
	dttf_.trPtPck.push_back(  i->pt_packed() );
	//dttf_.trPtVal.push_back(  i->ptValue() );
	dttf_.trPhiPck.push_back(  i->phi_packed() ); 
//	dttf_.trPhiVal.push_back(  i->phiValue() ); 
	dttf_.trEtaPck.push_back(  i->eta_packed() );
//	dttf_.trEtaVal.push_back(  i->etaValue() );

        int phi_local = i->phi_packed();//range: 0 < phi_local < 31 
        if(phi_local > 15) phi_local -= 32; //range: -16 < phi_local < 15
        double phi_global = (phi_local*(pig/72.))+((pig/6.)*i->scNum());// + 12*i->scNum(); //range: -16 < phi_global < 147
        if(phi_global < 0) phi_global+=2*pig; //range: 0 < phi_global < 147
        if(phi_global > 2*pig) phi_global-=2*pig; //range: 0 < phi_global < 143
	dttf_.trPhiGlob.push_back(  phi_global );
	dttf_.trChPck.push_back(  i->charge_packed() ); 
	dttf_.trWh.push_back(  i->whNum() );
	dttf_.trSc.push_back(  i->scNum() );
	unsigned int addresses=0;
	for (int KK = 0; KK<4; KK++){
	  //addresses|=((unsigned int)(i->stNum(KK+1))<<(KK*4));
	  //std::cout<<i->stNum(KK+1)<<std::endl;
	  addresses=i->stNum(KK+1);
	//}
	  dttf_.trAddress.push_back(addresses);
	}
	idttr++;
  }
 
}  


void TrUpS::L1AnalysisDTTF::SetMBTR(const edm::Handle<L1MuBMTrackContainer > L1MuBMTrackContainer, unsigned int maxMBTR)
{
  double pig=acos(-1);
  L1MuBMTrackContainer::TrackContainer const *tr =  L1MuBMTrackContainer->getContainer();
  int idttr = 0 ;
  dttf_.trmbSize = tr->size();
  for ( L1MuBMTrackContainer::TrackContainer::const_iterator i 
	  = tr->begin(); i != tr->end(); ++i ) {
        if((unsigned int)idttr>maxMBTR-1) continue;	
	dttf_.trmbBx.push_back(  i->bx()+1 );  
	dttf_.trmbTag.push_back(  i->TrkTag() );  
	dttf_.trmbQual.push_back(  i->hwQual() ); 
	dttf_.trmbPtPck.push_back(  i->hwPt() );
	dttf_.trmbPhiPck.push_back(  i->hwPhi() ); 
	dttf_.trmbEtaPck.push_back(  i->hwEta() );
	
        int phi_local = i->hwPhi();//range: 0 < phi_local < 31 
        if(phi_local > 15) phi_local -= 32; //range: -16 < phi_local < 15
        double phi_global = (phi_local*(pig/72.))+((pig/6.)*i->scNum());// + 12*i->scNum(); //range: -16 < phi_global < 147
        if(phi_global < 0) phi_global+=2*pig; //range: 0 < phi_global < 147
        if(phi_global > 2*pig) phi_global-=2*pig; //range: 0 < phi_global < 143
	dttf_.trmbPhiGlob.push_back(  phi_global );
	dttf_.trmbChPck.push_back(  i->hwSign() ); 
	dttf_.trmbWh.push_back(  i->whNum() );
	dttf_.trmbSc.push_back(  i->scNum() );
	dttf_.trmbAddress.push_back( i->hwTrackAddress());
	
	idttr++;
  }
 
}  
