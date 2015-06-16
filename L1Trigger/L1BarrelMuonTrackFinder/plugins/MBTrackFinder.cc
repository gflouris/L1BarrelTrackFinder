//-------------------------------------------------
//
//   Class: MBTrackFinder
//
//   L1 MB Track Finder EDProducer
//
//
//
//   Author :
//   J. Troconiz              UAM Madrid
//   Modified :
//   G. Flouris               U Ioannina
//--------------------------------------------------

#include "MBTrackFinder.h"

#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/Event.h"

#include "/home/gflouris/DTTF/uBMTF/CMSSW_7_5_0_pre1/src/DataFormats/L1DTTrackFinder/interface/L1MuDTChambPhContainer.h"
#include "/home/gflouris/DTTF/uBMTF/CMSSW_7_5_0_pre1/src/DataFormats/L1DTTrackFinder/interface/L1MuDTChambThContainer.h"
#include "/home/gflouris/DTTF/uBMTF/CMSSW_7_5_0_pre1/src/DataFormats/L1DTTrackFinder/interface/L1MuDTTrackContainer.h"
//#include <DataFormats/L1GlobalMuonTrigger/interface/L1MuRegionalCand.h>

#include "../src/L1MuMBTFConfig.h"
#include "../interface/L1MuMBTFSetup.h"
#include "../interface/L1MuMBTrackFinder.h"

#include <iostream>
#include <iomanip>

using namespace std;

MBTrackFinder::MBTrackFinder(const edm::ParameterSet & pset) {

  produces<L1MuDTTrackContainer>("MBTF");
  //produces<vector<L1MuRegionalCand> >("MB"); -->
  produces<vector<l1t::L1TRegionalMuonCandidate> >("MB");


  setup1 = new L1MuMBTFSetup(pset,consumesCollector());
  usesResource("MBTrackFinder");
}

MBTrackFinder::~MBTrackFinder() {

  delete setup1;

}

void MBTrackFinder::produce(edm::Event& e, const edm::EventSetup& c) {

  if ( L1MuMBTFConfig::Debug(1) ) cout << endl;
  if ( L1MuMBTFConfig::Debug(1) ) cout << "**** L1MuonMBTFTrigger processing event  ****" << endl;

  L1MuMBTrackFinder* dtbx = setup1->TrackFinder();
  dtbx->clear();
  //cout<<"Point 1"<<endl;

  dtbx->run(e,c);
//cout<<"Point 2"<<endl;

  int ndt = dtbx->numberOfTracks();
  if ( L1MuMBTFConfig::Debug(1) ) cout << "Number of muons found by the L1 MBBX TRIGGER : "
                                       << ndt << endl;
//cout<<"Point 3"<<endl;

  auto_ptr<L1MuDTTrackContainer> tra_product(new L1MuDTTrackContainer);
  //auto_ptr<vector<L1MuRegionalCand> >  vec_product(new vector<L1MuRegionalCand>); -->
  std::auto_ptr<vector<l1t::L1TRegionalMuonCandidate>  > vec_product(new vector<l1t::L1TRegionalMuonCandidate> );

  vector<L1MuDTTrackCand>&  dtTracks = dtbx->getcache0();
  tra_product->setContainer(dtTracks);
  //vector<L1MuRegionalCand>& MBTracks = dtbx->getcache(); -->
  vector<l1t::L1TRegionalMuonCandidate> & MBTracks = dtbx->getcache();
//cout<<"Point 1"<<endl;
//cout<<vec_product->size()<<"    "<<MBTracks.size()<<endl;

  *vec_product = MBTracks;

  //cout<<"MBTF"<<endl;
  e.put(tra_product,"MBTF");
  //cout<<"MB"<<endl;
  e.put(vec_product,"MB");

}
