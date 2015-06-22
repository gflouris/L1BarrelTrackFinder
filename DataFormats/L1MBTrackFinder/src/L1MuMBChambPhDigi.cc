//-------------------------------------------------
//
//   Class L1MuMBChambPhDigi
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
#include "DataFormats/L1MBTrackFinder/interface/L1MuMBChambPhDigi.h"

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
L1MuMBChambPhDigi::L1MuMBChambPhDigi() {

  bx              = -100;
  wheel           = 0;
  sector          = 0;
  station         = 0;
  radialAngle     = 0;
  bendingAngle    = 0;
  qualityCode     = 7;
  Ts2TagCode      = 0;
  BxCntCode       = 0;
}

L1MuMBChambPhDigi::L1MuMBChambPhDigi( int ubx, int uwh, int usc, int ust,
                         int uphr, int uphb, int uqua, int utag, int ucnt ) {

  bx              = ubx;
  wheel           = uwh;
  sector          = usc;
  station         = ust;
  radialAngle     = uphr;
  bendingAngle    = uphb;
  qualityCode     = uqua;
  Ts2TagCode      = utag;
  BxCntCode       = ucnt;
}

//--------------
// Destructor --
//--------------
L1MuMBChambPhDigi::~L1MuMBChambPhDigi() {
}

//--------------
// Operations --
//--------------
int L1MuMBChambPhDigi::bxNum() const {
  return bx;
}

int L1MuMBChambPhDigi::whNum() const {
  return wheel;
}
int L1MuMBChambPhDigi::scNum() const {
  return sector;
}
int L1MuMBChambPhDigi::stNum() const {
  return station;
}

int L1MuMBChambPhDigi::phi() const {
  return radialAngle;
}

int L1MuMBChambPhDigi::phiB() const {
  return bendingAngle;
}

int L1MuMBChambPhDigi::code() const {
  return qualityCode;
}

int L1MuMBChambPhDigi::Ts2Tag() const {
  return Ts2TagCode;
}

int L1MuMBChambPhDigi::BxCnt() const {
  return BxCntCode;
}
