//-------------------------------------------------
//
//   Class: L1MuMBTFSetup
//
//   Description: Setup the L1 barrel Muon Trigger Track Finder
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

#include "L1Trigger/L1BarrelMuonTrackFinder/interface/L1MuMBTFSetup.h"

//---------------
// C++ Headers --
//---------------

#include <iostream>


//-------------------------------
// Collaborating Class Headers --
//-------------------------------

#include "L1Trigger/L1BarrelMuonTrackFinder/interface/L1MuMBTrackFinder.h"

using namespace std;

// --------------------------------
//       class L1MuMBTFSetup
//---------------------------------


//----------------
// Constructors --
//----------------

L1MuMBTFSetup::L1MuMBTFSetup(const edm::ParameterSet & ps, edm::ConsumesCollector && iC) : m_tf(new L1MuMBTrackFinder(ps,std::move(iC))) {
  // setup  the barrel Muon Trigger Track Finder
  m_tf->setup();

}


//--------------
// Destructor --
//--------------

L1MuMBTFSetup::~L1MuMBTFSetup() {

  delete m_tf;

}


//--------------
// Operations --
//--------------
