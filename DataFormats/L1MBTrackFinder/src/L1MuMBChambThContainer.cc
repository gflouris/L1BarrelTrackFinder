//-------------------------------------------------
//
//   Class L1MuMBChambThContainer
//
//   Description: input data for ETTF trigger
//
//
//   Author List: Jorge Troconiz  UAM Madrid
//
//
//--------------------------------------------------

//-----------------------
// This Class's Header --
//-----------------------
#include "DataFormats/L1MBTrackFinder/interface/L1MuMBChambThContainer.h"

//-------------------------------
// Collaborating Class Headers --
//-------------------------------


//---------------
// C++ Headers --
//---------------
using namespace std;

//-------------------
// Initializations --
//-------------------


//----------------
// Constructors --
//----------------
L1MuMBChambThContainer::L1MuMBChambThContainer() {}

//--------------
// Destructor --
//--------------
L1MuMBChambThContainer::~L1MuMBChambThContainer() {}

//--------------
// Operations --
//--------------
void L1MuMBChambThContainer::setContainer(const The_Container& inputSegments) {

  theSegments = inputSegments;
}

L1MuMBChambThContainer::The_Container const* L1MuMBChambThContainer::getContainer() const {
  return &theSegments;
}

bool L1MuMBChambThContainer::bxEmpty(int step) const {

  bool empty = true;

  for ( The_iterator i  = theSegments.begin();
                     i != theSegments.end();
                     i++ ) {
    if  (step == i->bxNum()) empty = false;
  }

  return(empty);
}

int L1MuMBChambThContainer::bxSize(int step1, int step2) const {

  int size = 0;

  for ( The_iterator i  = theSegments.begin();
                     i != theSegments.end();
                     i++ ) {
    if  (step1 <= i->bxNum() && step2 >= i->bxNum()) size++;
  }

  return(size);
}

L1MuMBChambThDigi const* L1MuMBChambThContainer::chThetaSegm(int wheel, int stat, int sect, int step) const {

  L1MuMBChambThDigi const* rT=0;

  for ( The_iterator i  = theSegments.begin();
                     i != theSegments.end();
                     i++ ) {
    if  (step == i->bxNum() && wheel == i->whNum() && sect == i->scNum()
      && stat == i->stNum() )
      rT = &(*i);
  }

  return(rT);
}

