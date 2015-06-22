//-------------------------------------------------
//
//   Class L1MuMBTrackCand
//
//   Description: ouput data for MBTF trigger
//
//
//   Author List: Jorge Troconiz  UAM Madrid
//
//
//--------------------------------------------------

//-----------------------
// This Class's Header --
//-----------------------
#include "DataFormats/L1MBTrackFinder/interface/L1MuMBTrackCand.h"

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
//L1MuMBTrackCand::L1MuMBTrackCand() : L1MuRegionalCand(0,0) {
L1MuMBTrackCand::L1MuMBTrackCand() : l1t::L1TRegionalMuonCandidate() {

  wheel           = 0;
  sector          = 0;
  TrkTagCode      = -1;
  TrkAdd[0]       =  3;
  TrkAdd[1]       = 15;
  TrkAdd[2]       = 15;
  TrkAdd[3]       = 15;
  TClassCode      = 11;
}

//L1MuMBTrackCand::L1MuMBTrackCand( unsigned dataword, int bx, int uwh, int usc,
//                       int utag, int adr1, int adr2, int adr3, int adr4, int utc ) :
//                   L1MuRegionalCand(dataword, bx) {
L1MuMBTrackCand::L1MuMBTrackCand( unsigned dataword, int bx, int uwh, int usc,
                       int utag, int adr1, int adr2, int adr3, int adr4, int utc ) :
                   l1t::L1TRegionalMuonCandidate() {

  wheel           = uwh;
  sector          = usc;
  TrkTagCode      = utag;
  TrkAdd[0]       = adr1&0x03;
  TrkAdd[1]       = adr2;
  TrkAdd[2]       = adr3;
  TrkAdd[3]       = adr4;
  TClassCode      = utc;

  setAdd(1);
  setAdd(2);
  setAdd(3);
  setAdd(4);
}

//L1MuMBTrackCand::L1MuMBTrackCand( unsigned type_idx, unsigned phi, unsigned eta,
//                       unsigned pt, unsigned charge, unsigned ch_valid, unsigned finehalo,
//                       unsigned quality, int bx, int uwh, int usc, int utag,
//                       int adr1, int adr2, int adr3, int adr4 ) :
//                   L1MuRegionalCand(0, bx) {
L1MuMBTrackCand::L1MuMBTrackCand( unsigned type_idx, unsigned phi, unsigned eta,
                       unsigned pt, unsigned charge, unsigned ch_valid, unsigned finehalo,
                       unsigned quality, int bx, int uwh, int usc, int utag,
                       int adr1, int adr2, int adr3, int adr4 )  {

  setHwPhi(phi);
  setHwEta(eta);
  setHwPt(pt);
  setHwSign(charge);
  setHwSignValid(1);
  setHwQual(quality);
  setHwTrackAddress(adr1*1000000 + adr2*10000 + adr3*100 + adr4 );

  wheel           = uwh;
  sector          = usc;
  TrkTagCode      = utag;
  TrkAdd[0]       = adr1;
  TrkAdd[1]       = adr2;
  TrkAdd[2]       = adr3;
  TrkAdd[3]       = adr4;

  setTC();
}


L1MuMBTrackCand::L1MuMBTrackCand( int pt, int phi, int eta, int charge, int quality, int bx,
                                  int uwh, int usc, int utag,
                                  int adr1, int adr2, int adr3, int adr4, int utc )  {

  setHwPhi(phi);
  setHwEta(eta);
  setHwPt(pt);
  setHwSign(charge);
  setHwSignValid(1);
  setHwQual(quality);
  setBx(bx);
  setHwTrackAddress(adr1*1000000 + adr2*10000 + adr3*100 + adr4 );

  wheel           = uwh;
  sector          = usc;
  TrkTagCode      = utag;
  TrkAdd[0]       = adr1;
  TrkAdd[1]       = adr2;
  TrkAdd[2]       = adr3;
  TrkAdd[3]       = adr4;

  setTC();
}


//--------------
// Destructor --
//--------------
L1MuMBTrackCand::~L1MuMBTrackCand() {
}

//--------------
// Operations --
//--------------
int L1MuMBTrackCand::whNum() const {
  return wheel;
}

int L1MuMBTrackCand::scNum() const {
  return sector;
}

int L1MuMBTrackCand::stNum(int ust) const {
  return TrkAdd[ust-1];
}

int L1MuMBTrackCand::TCNum() const {
  return TClassCode;
}

int L1MuMBTrackCand::TrkTag() const {
  return TrkTagCode;
}

void L1MuMBTrackCand::setTC() {
  unsigned int uqua = hwQual(); //quality_packed();

  switch (uqua) {
    case 7:  { TClassCode =  0; break; }
    case 6:  { TClassCode =  1;
               if ( TrkAdd[3] != 15 ) TClassCode = 2;
               break; }
    case 5:  { TClassCode =  3; break; }
    case 4:  { TClassCode =  4; break; }
    case 3:  { TClassCode =  5;
               if ( TrkAdd[3] != 15 ) TClassCode = 6;
               if ( TrkAdd[2] != 15 ) TClassCode = 7;
               break; }
    case 2:  { TClassCode =  8;
               if ( TrkAdd[2] != 15 ) TClassCode = 9;
               break; }
    case 1:  { TClassCode = 10; break; }
    default: { TClassCode = 11; break; }
  }
}

void L1MuMBTrackCand::setAdd(int ust) {
  unsigned int uadd = stNum(ust);

  switch (uadd) {
    case  0:  { TrkAdd[ust-1] =   8; break; }
    case  1:  { TrkAdd[ust-1] =   9; break; }
    case  2:  { TrkAdd[ust-1] =   0; break; }
    case  3:  { TrkAdd[ust-1] =   1; break; }
    case  4:  { TrkAdd[ust-1] =  10; break; }
    case  5:  { TrkAdd[ust-1] =  11; break; }
    case  6:  { TrkAdd[ust-1] =   2; break; }
    case  7:  { TrkAdd[ust-1] =   3; break; }
    case  8:  { TrkAdd[ust-1] =  12; break; }
    case  9:  { TrkAdd[ust-1] =  13; break; }
    case 10:  { TrkAdd[ust-1] =   4; break; }
    case 11:  { TrkAdd[ust-1] =   5; break; }
    case 15:  { TrkAdd[ust-1] =  15; break; }
    default:  { TrkAdd[ust-1] =  15; break; }
  }

  if (ust!=1) return;

  switch (uadd) {
    case  0:  { TrkAdd[0] =  2; break; }
    case  1:  { TrkAdd[0] =  1; break; }
    case 15:  { TrkAdd[0] =  3; break; }
    default:  { TrkAdd[0] =  3; break; }
  }
}
