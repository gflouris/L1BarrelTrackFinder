//-------------------------------------------------
//
//   Class: L1MuMBDataBuffer
//
//   Description: Data Buffer
//
//
//
//   Author :
//   N. Neumeister            CERN EP
//
//--------------------------------------------------

//-----------------------
// This Class's Header --
//-----------------------

#include "L1Trigger/L1BarrelMuonTrackFinder/src/L1MuMBDataBuffer.h"

//---------------
// C++ Headers --
//---------------

#include <iostream>
#include <vector>
#include <cmath>

//-------------------------------
// Collaborating Class Headers --
//-------------------------------

#include "L1Trigger/L1BarrelMuonTrackFinder/src/L1MuMBTFConfig.h"
#include "L1Trigger/L1BarrelMuonTrackFinder/src/L1MuMBSectorProcessor.h"
#include "L1Trigger/L1BarrelMuonTrackFinder/src/L1MuMBTrackSegLoc.h"
#include "L1Trigger/L1BarrelMuonTrackFinder/src/L1MuMBTrackSegPhi.h"

using namespace std;

// --------------------------------
//       class L1MuMBDataBuffer
//---------------------------------

//----------------
// Constructors --
//----------------
L1MuMBDataBuffer::L1MuMBDataBuffer(const L1MuMBSectorProcessor& sp) :
        m_sp(sp), m_tsphi(0) {


  m_tsphi = new TSPhivector(38);
  m_tsphi->reserve(38);

}


//--------------
// Destructor --
//--------------
L1MuMBDataBuffer::~L1MuMBDataBuffer() {

  delete m_tsphi;

}


//--------------
// Operations --
//--------------

//
// clear buffer
//
void L1MuMBDataBuffer::reset() {

  TSPhivector::iterator iter = m_tsphi->begin();
  while ( iter != m_tsphi->end() ) {
    if ( *iter) {
      delete *iter;
      *iter = 0;
    }
    iter++;
  }

}


//
// get phi track segment of a given station
//
const L1MuMBTrackSegPhi* L1MuMBDataBuffer::getTSphi(int station, int reladr) const {

  int address = (station == 1) ? reladr : reladr + (station-2)*12 + 2;
  return (*m_tsphi)[address];

}


//
// add new phi track segment to the buffer
//
void L1MuMBDataBuffer::addTSphi(int adr, const L1MuMBTrackSegPhi& ts) {

  L1MuMBTrackSegPhi* tmpts = new L1MuMBTrackSegPhi(ts);
  (*m_tsphi)[adr] = tmpts;

}


//
// print all phi track segments in the buffer
//
void L1MuMBDataBuffer::printTSphi() const {

  TSPhivector::const_iterator iter = m_tsphi->begin();
  while ( iter != m_tsphi->end() ) {
    if ( *iter ) cout << *(*iter) << endl;
    iter++;
  }

}


//
// count number of non empty phi track segments
//
int L1MuMBDataBuffer::numberTSphi() const {

  int count = 0;
  TSPhivector::iterator iter = m_tsphi->begin();
  while ( iter != m_tsphi->end() ) {
    if ( *iter && !(*iter)->empty() ) count++;
    iter++;
  }
  return count;

}
