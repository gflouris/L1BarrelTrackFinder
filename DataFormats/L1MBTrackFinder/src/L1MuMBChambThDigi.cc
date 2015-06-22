//-------------------------------------------------
//
//   Class L1MuMBChambThDigi
//
//   Description: input data for PHTF trigger
//
//
//   Author List: Jorge Troconiz  UAM Madrid
//
//
//--------------------------------------------------

//-----------------------
// This Class's Header --
//-----------------------
#include "DataFormats/L1MBTrackFinder/interface/L1MuMBChambThDigi.h"

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
L1MuMBChambThDigi::L1MuMBChambThDigi() {

  bx              = -100;
  wheel           = 0;
  sector          = 0;
  station         = 0;

  for(int i=0;i<7;i++) {
    m_outPos[i] = 0;
    m_outQual[i] = 0;
  }
}

L1MuMBChambThDigi::L1MuMBChambThDigi( int ubx, int uwh, int usc, int ust,
                                      int* upos, int* uqual ) {

  bx              = ubx;
  wheel           = uwh;
  sector          = usc;
  station         = ust;

  for(int i=0;i<7;i++) {
    m_outPos[i] = upos[i];
    m_outQual[i] = uqual[i];
  }
}

L1MuMBChambThDigi::L1MuMBChambThDigi( int ubx, int uwh, int usc, int ust,
                                      int* upos ) {

  bx              = ubx;
  wheel           = uwh;
  sector          = usc;
  station         = ust;

  for(int i=0;i<7;i++) {
    m_outPos[i] = upos[i];
    m_outQual[i] = 0;
  }
}

//--------------
// Destructor --
//--------------
L1MuMBChambThDigi::~L1MuMBChambThDigi() {
}

//--------------
// Operations --
//--------------
int L1MuMBChambThDigi::bxNum() const {
  return bx;
}

int L1MuMBChambThDigi::whNum() const {
  return wheel;
}
int L1MuMBChambThDigi::scNum() const {
  return sector;
}
int L1MuMBChambThDigi::stNum() const {
  return station;
}

int L1MuMBChambThDigi::code(const int i) const {
  if (i<0||i>=7) return 0;

  return (int)(m_outPos[i]+m_outQual[i]);
}

int L1MuMBChambThDigi::position(const int i) const {
  if (i<0||i>=7) return 0;

  return (int)m_outPos[i];
}

int L1MuMBChambThDigi::quality(const int i) const {
  if (i<0||i>=7) return 0;

  return (int)m_outQual[i];
}
