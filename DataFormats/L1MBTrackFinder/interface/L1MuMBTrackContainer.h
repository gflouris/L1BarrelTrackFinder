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
#ifndef L1MuMBTrackContainer_H
#define L1MuMBTrackContainer_H

//------------------------------------
// Collaborating Class Declarations --
//------------------------------------
#include "DataFormats/L1MBTrackFinder/interface/L1MuMBTrackCand.h"

//----------------------
// Base Class Headers --
//----------------------
#include <vector>

//---------------
// C++ Headers --
//---------------

//              ---------------------
//              -- Class Interface --
//              ---------------------


class L1MuMBTrackContainer {

 public:

  typedef std::vector<L1MuMBTrackCand>    TrackContainer;
  typedef TrackContainer::const_iterator  Trackiterator;
  typedef TrackContainer::iterator        TrackIterator;

  //  Constructors
  L1MuMBTrackContainer();

  //  Destructor
  ~L1MuMBTrackContainer();

  void setContainer(const TrackContainer& inputTracks);

  TrackContainer const* getContainer() const;

  bool bxEmpty(int step) const;

  int bxSize(int step1, int step2) const;

  L1MuMBTrackCand const* dtTrackCand1(int wheel, int sect, int bx) const;

  L1MuMBTrackCand const* dtTrackCand2(int wheel, int sect, int bx) const;


 private:

  TrackContainer dtTracks;

};

#endif
