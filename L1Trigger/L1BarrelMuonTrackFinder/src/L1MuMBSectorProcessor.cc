//-------------------------------------------------
//
//   Class: L1MuMBSectorProcessor
//
//   Description: Sector Processor
//
//
//
//   Author :
//   N. Neumeister            CERN EP
//   J. Troconiz              UAM Madrid
//
//--------------------------------------------------

//-----------------------
// This Class's Header --
//-----------------------

#include "L1MuMBSectorProcessor.h"

//---------------
// C++ Headers --
//---------------

#include <iostream>
#include <cmath>

//-------------------------------
// Collaborating Class Headers --
//-------------------------------

#include <FWCore/Framework/interface/Event.h>
#include "L1Trigger/L1BarrelMuonTrackFinder/src/L1MuMBTFConfig.h"
#include "L1Trigger/L1BarrelMuonTrackFinder/src/L1MuMBSecProcId.h"
#include "L1Trigger/L1BarrelMuonTrackFinder/src/L1MuMBSectorReceiver.h"
#include "L1Trigger/L1BarrelMuonTrackFinder/src/L1MuMBDataBuffer.h"
#include "L1Trigger/L1BarrelMuonTrackFinder/src/L1MuMBExtrapolationUnit.h"
#include "L1Trigger/L1BarrelMuonTrackFinder/src/L1MuMBTrackAssembler.h"
#include "L1Trigger/L1BarrelMuonTrackFinder/src/L1MuMBAssignmentUnit.h"
#include "L1Trigger/L1BarrelMuonTrackFinder/interface/L1MuMBTrackFinder.h"
#include "L1Trigger/L1BarrelMuonTrackFinder/interface/L1MuMBTrack.h"

using namespace std;

// --------------------------------
//       class L1MuMBSectorProcessor
//---------------------------------

//----------------
// Constructors --
//----------------

L1MuMBSectorProcessor::L1MuMBSectorProcessor(const L1MuMBTrackFinder& tf,
                                             const L1MuMBSecProcId& id) :
      m_tf(tf), m_spid(id),
      m_SectorReceiver(new L1MuMBSectorReceiver(*this)),
      m_DataBuffer(new L1MuMBDataBuffer(*this)),
      m_EU(new L1MuMBExtrapolationUnit(*this)),
      m_TA(new L1MuMBTrackAssembler(*this)),
      m_AUs(), m_TrackCands(), m_TracKCands() {

  // 2 assignment units
  m_AUs.reserve(2);
  m_AUs.push_back(new L1MuMBAssignmentUnit(*this,0));
  m_AUs.push_back(new L1MuMBAssignmentUnit(*this,1));

  // now the 2 track candidates
  m_TrackCands.reserve(2);
  m_TrackCands.push_back(new L1MuMBTrack(m_spid) );
  m_TrackCands.push_back(new L1MuMBTrack(m_spid) );

  m_TracKCands.reserve(2);
  m_TracKCands.push_back(new L1MuMBTrack(m_spid) );
  m_TracKCands.push_back(new L1MuMBTrack(m_spid) );

}


//--------------
// Destructor --
//--------------

L1MuMBSectorProcessor::~L1MuMBSectorProcessor() {

  delete m_SectorReceiver;
  delete m_DataBuffer;
  delete m_EU;
  delete m_TA;
  delete m_AUs[0];
  delete m_AUs[1];
  delete m_TrackCands[0];
  delete m_TrackCands[1];
  delete m_TracKCands[0];
  delete m_TracKCands[1];

}

//--------------
// Operations --
//--------------

//
// run Sector Processor
//
void L1MuMBSectorProcessor::run(int bx, const edm::Event& e, const edm::EventSetup& c) {

  // receive data and store them into the data buffer
  if ( m_SectorReceiver ) m_SectorReceiver->run(bx, e, c);

  // check content of data buffer
  if ( m_DataBuffer ) {
    if ( L1MuMBTFConfig::Debug(4) && m_DataBuffer->numberTSphi() > 0 ) {
      cout << "Phi track segments received by " << m_spid << " : " << endl;
      m_DataBuffer->printTSphi();
    }
  }

  // perform all extrapolations
  int n_ext = 0;	// number of successful extrapolations
  if ( m_EU && m_DataBuffer && m_DataBuffer->numberTSphi() > 1 ) {
    m_EU->run(c);
    n_ext = m_EU->numberOfExt();
    if ( L1MuMBTFConfig::Debug(3) && n_ext > 0  ) {
//    if ( print_flag && n_ext > 0  ) {
      cout << "Number of successful extrapolations : " << n_ext << endl;
      m_EU->print();
    }
  }

  // hardware debug (output from Extrapolator and Quality Sorter)
  // m_EU->print(1);

  // perform track assembling
  if ( m_TA &&  n_ext > 0 ) {
    m_TA->run();
    if ( L1MuMBTFConfig::Debug(3) ) m_TA->print();
  }

  // assign pt, eta, phi and quality
  if ( m_AUs[0] && !m_TA->isEmpty(0) ) m_AUs[0]->run(c);
  if ( m_AUs[1] && !m_TA->isEmpty(1) ) m_AUs[1]->run(c);

  if ( m_spid.wheel() == -1 ) {
    if ( m_TrackCands[0] && !m_TrackCands[0]->empty() && m_TrackCands[0]->address(2)>3 && m_TrackCands[0]->address(2)<6 ) m_TrackCands[0]->reset();
    if ( m_TrackCands[0] && !m_TrackCands[0]->empty() && m_TrackCands[0]->address(3)>3 && m_TrackCands[0]->address(3)<6 ) m_TrackCands[0]->reset();
    if ( m_TrackCands[0] && !m_TrackCands[0]->empty() && m_TrackCands[0]->address(4)>3 && m_TrackCands[0]->address(4)<6 ) m_TrackCands[0]->reset();

    if ( m_TracKCands[0] && !m_TracKCands[0]->empty() && m_TracKCands[0]->address(2)>3 && m_TracKCands[0]->address(2)<6 ) m_TracKCands[0]->reset();
    if ( m_TracKCands[0] && !m_TracKCands[0]->empty() && m_TracKCands[0]->address(3)>3 && m_TracKCands[0]->address(3)<6 ) m_TracKCands[0]->reset();
    if ( m_TracKCands[0] && !m_TracKCands[0]->empty() && m_TracKCands[0]->address(4)>3 && m_TracKCands[0]->address(4)<6 ) m_TracKCands[0]->reset();

    if ( m_TrackCands[1] && !m_TrackCands[1]->empty() && m_TrackCands[1]->address(2)>3 && m_TrackCands[1]->address(2)<6 ) m_TrackCands[1]->reset();
    if ( m_TrackCands[1] && !m_TrackCands[1]->empty() && m_TrackCands[1]->address(3)>3 && m_TrackCands[1]->address(3)<6 ) m_TrackCands[1]->reset();
    if ( m_TrackCands[1] && !m_TrackCands[1]->empty() && m_TrackCands[1]->address(4)>3 && m_TrackCands[1]->address(4)<6 ) m_TrackCands[1]->reset();

    if ( m_TracKCands[1] && !m_TracKCands[1]->empty() && m_TracKCands[1]->address(2)>3 && m_TracKCands[1]->address(2)<6 ) m_TracKCands[1]->reset();
    if ( m_TracKCands[1] && !m_TracKCands[1]->empty() && m_TracKCands[1]->address(3)>3 && m_TracKCands[1]->address(3)<6 ) m_TracKCands[1]->reset();
    if ( m_TracKCands[1] && !m_TracKCands[1]->empty() && m_TracKCands[1]->address(4)>3 && m_TracKCands[1]->address(4)<6 ) m_TracKCands[1]->reset();

    if ( m_TrackCands[0] && !m_TrackCands[0]->empty() && m_TrackCands[0]->address(2)>7 && m_TrackCands[0]->address(2)<10 ) m_TrackCands[0]->reset();
    if ( m_TrackCands[0] && !m_TrackCands[0]->empty() && m_TrackCands[0]->address(3)>7 && m_TrackCands[0]->address(3)<10 ) m_TrackCands[0]->reset();
    if ( m_TrackCands[0] && !m_TrackCands[0]->empty() && m_TrackCands[0]->address(4)>7 && m_TrackCands[0]->address(4)<10 ) m_TrackCands[0]->reset();

    if ( m_TracKCands[0] && !m_TracKCands[0]->empty() && m_TracKCands[0]->address(2)>7 && m_TracKCands[0]->address(2)<10 ) m_TracKCands[0]->reset();
    if ( m_TracKCands[0] && !m_TracKCands[0]->empty() && m_TracKCands[0]->address(3)>7 && m_TracKCands[0]->address(3)<10 ) m_TracKCands[0]->reset();
    if ( m_TracKCands[0] && !m_TracKCands[0]->empty() && m_TracKCands[0]->address(4)>7 && m_TracKCands[0]->address(4)<10 ) m_TracKCands[0]->reset();

    if ( m_TrackCands[1] && !m_TrackCands[1]->empty() && m_TrackCands[1]->address(2)>7 && m_TrackCands[1]->address(2)<10 ) m_TrackCands[1]->reset();
    if ( m_TrackCands[1] && !m_TrackCands[1]->empty() && m_TrackCands[1]->address(3)>7 && m_TrackCands[1]->address(3)<10 ) m_TrackCands[1]->reset();
    if ( m_TrackCands[1] && !m_TrackCands[1]->empty() && m_TrackCands[1]->address(4)>7 && m_TrackCands[1]->address(4)<10 ) m_TrackCands[1]->reset();

    if ( m_TracKCands[1] && !m_TracKCands[1]->empty() && m_TracKCands[1]->address(2)>7 && m_TracKCands[1]->address(2)<10 ) m_TracKCands[1]->reset();
    if ( m_TracKCands[1] && !m_TracKCands[1]->empty() && m_TracKCands[1]->address(3)>7 && m_TracKCands[1]->address(3)<10 ) m_TracKCands[1]->reset();
    if ( m_TracKCands[1] && !m_TracKCands[1]->empty() && m_TracKCands[1]->address(4)>7 && m_TracKCands[1]->address(4)<10 ) m_TracKCands[1]->reset();
  }

}


//
// reset Sector Processor
//
void L1MuMBSectorProcessor::reset() {

  if ( m_SectorReceiver ) m_SectorReceiver->reset();
  if ( m_DataBuffer ) m_DataBuffer->reset();
  if ( m_EU ) m_EU->reset();
  if ( m_TA ) m_TA->reset();
  if ( m_AUs[0] ) m_AUs[0]->reset();
  if ( m_AUs[1] ) m_AUs[1]->reset();
  if ( m_TrackCands[0] ) m_TrackCands[0]->reset();
  if ( m_TrackCands[1] ) m_TrackCands[1]->reset();
  if ( m_TracKCands[0] ) m_TracKCands[0]->reset();
  if ( m_TracKCands[1] ) m_TracKCands[1]->reset();

}


//
// print candidates found in Sector Processor
//
void L1MuMBSectorProcessor::print() const {

  if ( anyTrack() ) {
    cout << "Muon candidates found in " << m_spid << " : " << endl;
    vector<L1MuMBTrack*>::const_iterator iter = m_TrackCands.begin();
    while ( iter != m_TrackCands.end() ) {
      if ( *iter) (*iter)->print();
      iter++;
    }
  }

}


//
// return pointer to nextWheel neighbour
//
const L1MuMBSectorProcessor* L1MuMBSectorProcessor::neighbour() const {

  int sector = m_spid.sector();
  int wheel  = m_spid.wheel();

  // the neighbour is in the same wedge with the following definition:
  // current SP  -3  -2  -1  +1  +2  +3
  // neighbour   -2  -1  +1   0  +1  +2

  if ( wheel == 1) return 0;
  wheel = (wheel == -1) ? 1 : (wheel/abs(wheel)) * (abs(wheel)-1);

  const L1MuMBSecProcId id(wheel,sector);

  return m_tf.sp(id);

}


//
// are there any muon candidates?
//
bool L1MuMBSectorProcessor::anyTrack() const {

  if ( m_TrackCands[0] && !m_TrackCands[0]->empty() ) return true;
  if ( m_TrackCands[1] && !m_TrackCands[1]->empty() ) return true;

  return false;

}
