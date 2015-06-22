//-------------------------------------------------
//
//   Class L1MuMBTrackContainer
//
//   Description: output data for MBTF trigger
//
//
//   Author List: Jorge Troconiz  UAM Madrid
//
//
//--------------------------------------------------

//-----------------------
// This Class's Header --
//-----------------------
#include "DataFormats/L1MBTrackFinder/interface/L1MuMBTrackContainer.h"

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
L1MuMBTrackContainer::L1MuMBTrackContainer() {}

//--------------
// Destructor --
//--------------
L1MuMBTrackContainer::~L1MuMBTrackContainer() {}

//--------------
// Operations --
//--------------
void L1MuMBTrackContainer::setContainer(const TrackContainer& inputTracks) {

  dtTracks = inputTracks;
}

L1MuMBTrackContainer::TrackContainer const* L1MuMBTrackContainer::getContainer() const {
  return &dtTracks;
}

bool L1MuMBTrackContainer::bxEmpty(int step) const {

  bool empty = true;

  for ( Trackiterator i  = dtTracks.begin();
                      i != dtTracks.end();
                      i++ ) {
    if  (step == i->bx()) empty = false;
  }

  return(empty);
}

int L1MuMBTrackContainer::bxSize(int step1, int step2) const {

  int size = 0;

  for ( Trackiterator i  = dtTracks.begin();
                      i != dtTracks.end();
                      i++ ) {
    if  (step1 <= i->bx() && step2 >= i->bx()
//      && i->quality_packed() != 0) size++;
      && i->hwQual() != 0) size++;
  }

  return(size);
}

L1MuMBTrackCand const* L1MuMBTrackContainer::dtTrackCand1(int wheel, int sect, int step) const {

  L1MuMBTrackCand const* rT=0;

  for ( Trackiterator i  = dtTracks.begin();
                      i != dtTracks.end();
                      i++ ) {
    if  (step == i->bx() && wheel == i->whNum() && sect == i->scNum()
      && i->TrkTag() == 0)
      rT = &(*i);
  }

  return(rT);
}

L1MuMBTrackCand const* L1MuMBTrackContainer::dtTrackCand2(int wheel, int sect, int step) const {

  L1MuMBTrackCand const* rT=0;

  for ( Trackiterator i  = dtTracks.begin();
                      i != dtTracks.end();
                      i++ ) {
    if  (step == i->bx() && wheel == i->whNum() && sect == i->scNum()
      && i->TrkTag() == 1)
      rT = &(*i);
  }

  return(rT);
}
