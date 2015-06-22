//-------------------------------------------------
//
//   Class L1MuMBChambPhContainer
//
//   Description: input data for PHTF trigger
//
//
//   Author List: Jorge Troconiz  UAM Madrid
//
//
//--------------------------------------------------
#ifndef L1MuMBChambPhContainer_H
#define L1MuMBChambPhContainer_H

//------------------------------------
// Collaborating Class Declarations --
//------------------------------------
#include "DataFormats/L1MBTrackFinder/interface/L1MuMBChambPhDigi.h"

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


class L1MuMBChambPhContainer {

 public:

  typedef std::vector<L1MuMBChambPhDigi>  Phi_Container;
  typedef Phi_Container::const_iterator   Phi_iterator;

  //  Constructors
  L1MuMBChambPhContainer();

  //  Destructor
  ~L1MuMBChambPhContainer();

  void setContainer(const Phi_Container& inputSegments);

  Phi_Container const* getContainer() const;

  bool bxEmpty(int step) const;

  int bxSize(int step1, int step2) const;

  L1MuMBChambPhDigi const* chPhiSegm1(int wheel, int stat, int sect, int bx) const;

  L1MuMBChambPhDigi const* chPhiSegm2(int wheel, int stat, int sect, int bx) const;

 private:

  Phi_Container phiSegments; 

};

#endif
