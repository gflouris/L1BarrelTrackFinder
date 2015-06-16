//-------------------------------------------------
//
//   Class: L1MuMBSecProcMap
//
//   Description: Sector Processor container
//
//
//
//   Author :
//   N. Neumeister             CERN EP
//
//--------------------------------------------------

//-----------------------
// This Class's Header --
//-----------------------

#include "L1Trigger/L1BarrelMuonTrackFinder/src/L1MuMBSecProcMap.h"

//---------------
// C++ Headers --
//---------------

#include <iostream>

//-------------------------------
// Collaborating Class Headers --
//-------------------------------

#include "L1Trigger/L1BarrelMuonTrackFinder/src/L1MuMBSecProcId.h"
#include "L1Trigger/L1BarrelMuonTrackFinder/src/L1MuMBSectorProcessor.h"

using namespace std;

// --------------------------------
//       class L1MuMBSecProcMap
//---------------------------------

//----------------
// Constructors --
//----------------

L1MuMBSecProcMap::L1MuMBSecProcMap() : m_map() {}

//--------------
// Destructor --
//--------------

L1MuMBSecProcMap::~L1MuMBSecProcMap() {

  SPmap_iter iter = m_map.begin();
  while ( iter != m_map.end() ) {
    delete (*iter).second;
    iter++;
  }
  m_map.clear();

}


//--------------
// Operations --
//--------------

//
// return Sector Processor
//
L1MuMBSectorProcessor* L1MuMBSecProcMap::sp(const L1MuMBSecProcId& id ) const {

  SPmap::const_iterator it = m_map.find(id);
  if ( it == m_map.end() ) {
    //    cerr << "Error: Sector Processor not in the map" << endl;
    return 0;
  }
  return (*it).second;

}


//
// insert Sector Processor into container
//
void L1MuMBSecProcMap::insert(const L1MuMBSecProcId& id, L1MuMBSectorProcessor* sp)  {

  //SPmap::const_iterator it = m_map.find(id);
  //  if ( it != m_map.end() )
    //    cerr << "Error: More than one Sector Processor with same identifier"
    //         << endl;
  m_map[id] = sp;

}
