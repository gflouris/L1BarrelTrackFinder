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
#ifndef L1MuMBChambThContainer_H
#define L1MuMBChambThContainer_H

//------------------------------------
// Collaborating Class Declarations --
//------------------------------------
#include "DataFormats/L1MBTrackFinder/interface/L1MuMBChambThDigi.h"

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

class L1MuMBChambThContainer {

 public:

  typedef std::vector<L1MuMBChambThDigi>  The_Container;
  typedef The_Container::const_iterator   The_iterator;

  //  Constructors
  L1MuMBChambThContainer();

  //  Destructor
  ~L1MuMBChambThContainer();

  void setContainer(const The_Container& inputSegments);

  The_Container const* getContainer() const;

  bool bxEmpty(int step) const;

  int bxSize(int step1, int step2) const;

  L1MuMBChambThDigi const* chThetaSegm(int wheel, int stat, int sect, int bx) const;

 private:

  The_Container theSegments; 

};

#endif
