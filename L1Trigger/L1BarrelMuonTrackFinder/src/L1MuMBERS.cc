//-------------------------------------------------
//
//   Class: L1MuMBERS
//
//   Description: Extrapolation Result Selector
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

#include "L1Trigger/L1BarrelMuonTrackFinder/src/L1MuMBERS.h"

//---------------
// C++ Headers --
//---------------

#include <iostream>
#include <algorithm>

//-------------------------------
// Collaborating Class Headers --
//-------------------------------

#include "L1Trigger/L1BarrelMuonTrackFinder/src/L1MuMBTFConfig.h"
#include "L1Trigger/L1BarrelMuonTrackFinder/src/L1MuMBTrackSegPhi.h"
#include "L1Trigger/L1BarrelMuonTrackFinder/src/L1MuMBSEU.h"
#include "L1Trigger/L1BarrelMuonTrackFinder/src/L1MuMBEUX.h"

using namespace std;

// --------------------------------
//       class L1MuMBERS
//---------------------------------

//----------------
// Constructors --
//----------------

L1MuMBERS::L1MuMBERS(const L1MuMBSEU& seu) : m_seu(seu) {

  reset();

}


//--------------
// Destructor --
//--------------

L1MuMBERS::~L1MuMBERS() {}


//--------------
// Operations --
//--------------

//
// run ERS
//
void L1MuMBERS::run() {

  int n_ext = m_seu.numberOfExt();
  if ( n_ext > 0 ) {
    vector<L1MuMBEUX*>::const_iterator first = m_seu.eux().begin();
    vector<L1MuMBEUX*>::const_iterator last  = m_seu.eux().end();
    vector<L1MuMBEUX*>::const_iterator first_max;
    vector<L1MuMBEUX*>::const_iterator second_max;

    // find the best extrapolation
    first_max  = max_element(first, last, L1MuMBEUX::EUX_Comp() );
    m_address[0] = (*first_max)->address();
    m_quality[0] = (*first_max)->quality();
    m_start[0]   = (*first_max)->ts().first;
    m_target[0]  = (*first_max)->ts().second;


    if ( n_ext > 1 ) {
      // find the second best extrapolation
      second_max = max_element(first, last, L1MuMBEUX::EUX_Comp(*first_max) );
      m_address[1] =  (*second_max)->address();
      m_quality[1] =  (*second_max)->quality();
      m_start[1]   =  (*second_max)->ts().first;
      m_target[1]  =  (*second_max)->ts().second;
    }

    if ( L1MuMBTFConfig::Debug(4) ) {
      cout << "ERS : " << endl;
      cout << "\t first  : " << m_address[0] << '\t' << m_quality[0] << endl;
      cout << "\t second : " << m_address[1] << '\t' << m_quality[1] << endl;
    }

  }

}


//
// reset ERS
//
void L1MuMBERS::reset() {

  for ( int id  = 0; id < 2; id++ ) {
    m_quality[id] = 0;
    m_address[id] = 15;
    m_start[id]   = 0;
    m_target[id]  = 0;
  }

}


//
// return pointer to start and target track segment
//
pair<const L1MuMBTrackSegPhi*, const L1MuMBTrackSegPhi*> L1MuMBERS::ts(int id) const {

  return pair<const L1MuMBTrackSegPhi*,const L1MuMBTrackSegPhi*>(m_start[id],m_target[id]);

}
