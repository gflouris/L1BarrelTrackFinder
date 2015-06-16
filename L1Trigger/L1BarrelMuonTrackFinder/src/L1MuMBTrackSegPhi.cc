//-------------------------------------------------
//
//   Class: L1MuMBTrackSegPhi
//
//   Description: PHI Track Segment
//
//
//
//   Author :
//   N. Neumeister            CERN EP
//
//--------------------------------------------------

//-----------------------
// This Class's Header --
//-----------------------

#include "L1Trigger/L1BarrelMuonTrackFinder/src/L1MuMBTrackSegPhi.h"

//---------------
// C++ Headers --
//---------------

#include <iostream>
#include <iomanip>
#include <cmath>

//-------------------------------
// Collaborating Class Headers --
//-------------------------------

#include "L1Trigger/L1BarrelMuonTrackFinder/src/L1MuMBTrackSegLoc.h"

using namespace std;

// --------------------------------
//       class L1MuMBTrackSegPhi
//---------------------------------

//----------------
// Constructors --
//----------------

L1MuMBTrackSegPhi::L1MuMBTrackSegPhi() :
      m_location(), m_phi(0), m_phib(0), m_quality(Null), m_bx(0) {}


L1MuMBTrackSegPhi::L1MuMBTrackSegPhi(int wheel_id, int sector_id, int station_id,
                                     int phi, int phib,
                                     TSQuality quality, bool tag, int  bx,
                                     bool etaFlag) :
  m_location(wheel_id, sector_id, station_id),
  m_phi(phi), m_phib(phib), m_quality(quality), m_bx(bx), m_etaFlag(etaFlag) {

  if ( phi  < -2048 || phi  > 2047 ) {
    //    cerr << "TrackSegPhi : phi out of range: " << phi << endl;
  }
  if ( phib <  -512 || phib >  511 ) {
    //    cerr << "TrackSegPhi : phib out of range: " << phib << endl;
  }
  if ( quality > 7 ) {
    //    cerr << "TrackSegPhi : quality out of range: " << quality << endl;
  }

}


L1MuMBTrackSegPhi::L1MuMBTrackSegPhi(const L1MuMBTrackSegLoc& id,
                                     int phi, int phib,
                                     TSQuality quality, bool tag, int bx,
                                     bool etaFlag) :
  m_location(id), m_phi(phi), m_phib(phib),
  m_quality(quality), m_tag(tag), m_bx(bx), m_etaFlag(etaFlag) {

  if ( phi  < -2048 || phi  > 2047 ) {
    //    cerr << "TrackSegPhi : phi out of range: " << phi << endl;
  }
  if ( phib <  -512 || phib >  511 ) {
    //    cerr << "TrackSegPhi : phib out of range: " << phib << endl;
  }
  if ( quality > 7 ) {
    //    cerr << "TrackSegPhi : quality out of range: " << quality << endl;
  }

}


L1MuMBTrackSegPhi::L1MuMBTrackSegPhi(const L1MuMBTrackSegPhi& id) :
  m_location(id.m_location),
  m_phi(id.m_phi), m_phib(id.m_phib), m_quality(id.m_quality),
  m_tag(id.m_tag), m_bx(id.m_bx), m_etaFlag(id.m_etaFlag) {}



//--------------
// Destructor --
//--------------
L1MuMBTrackSegPhi::~L1MuMBTrackSegPhi() {}


//--------------
// Operations --
//--------------

//
// reset PHI Track Segment
//
void L1MuMBTrackSegPhi::reset() {

  m_phi     = 0;
  m_phib    = 0;
  m_quality = Null;
  m_tag     = false;
  m_bx      = 0;
  m_etaFlag = false;

}


//
// return phi in global coordinates [0,2pi]
//
double L1MuMBTrackSegPhi::phiValue() const {

  double tmp = static_cast<double>(m_location.sector())*M_PI/6;
  tmp += static_cast<double>(m_phi)/4096;
  return (tmp > 0 ) ? tmp : (2*M_PI + tmp);

}


//
// return phib in radians
//
double L1MuMBTrackSegPhi::phibValue() const {

  return static_cast<double>(m_phib)/512;

}


//
// Assignment operator
//
L1MuMBTrackSegPhi& L1MuMBTrackSegPhi::operator=(const L1MuMBTrackSegPhi& id) {

  if ( this != &id ) {
    m_location  = id.m_location;
    m_phi       = id.m_phi;
    m_phib      = id.m_phib;
    m_quality   = id.m_quality;
    m_tag       = id.m_tag;
    m_bx        = id.m_bx;
    m_etaFlag   = id.m_etaFlag;
  }
  return *this;

}


//
// Equal operator
//
bool L1MuMBTrackSegPhi::operator==(const L1MuMBTrackSegPhi& id) const {

  if ( m_location != id.m_location ) return false;
  if ( m_phi      != id.m_phi )      return false;
  if ( m_phib     != id.m_phib )     return false;
  if ( m_quality  != id.m_quality )  return false;
  if ( m_bx       != id.m_bx )       return false;
  return true;

}


//
// Unequal operator
//
bool L1MuMBTrackSegPhi::operator!=(const L1MuMBTrackSegPhi& id) const {

  if ( m_location != id.m_location ) return true;
  if ( m_phi      != id.m_phi )      return true;
  if ( m_phib     != id.m_phib )     return true;
  if ( m_quality  != id.m_quality )  return true;
  if ( m_bx       != id.m_bx )       return true;
  return false;

}


//
// output stream operator phi track segment quality
//
ostream& operator<<(ostream& s, const L1MuMBTrackSegPhi::TSQuality& quality) {

  switch (quality) {
    case L1MuMBTrackSegPhi::Li   : return s << "Li ";
    case L1MuMBTrackSegPhi::Lo   : return s << "Lo ";
    case L1MuMBTrackSegPhi::Hi   : return s << "Hi ";
    case L1MuMBTrackSegPhi::Ho   : return s << "Ho ";
    case L1MuMBTrackSegPhi::LL   : return s << "LL ";
    case L1MuMBTrackSegPhi::HL   : return s << "HL ";
    case L1MuMBTrackSegPhi::HH   : return s << "HH ";
    case L1MuMBTrackSegPhi::Null : return s << "Null ";
    default :
      return s << "unknown TS phi Quality ";
  }

}


//
// output stream operator for phi track segments
//
ostream& operator<<(ostream& s, const L1MuMBTrackSegPhi& id) {

  s.setf(ios::right,ios::adjustfield);
  s << (id.m_location) << "\t"
    << "phi : "     << setw(5) << id.m_phi  << "  "
    << "phib : "    << setw(4) << id.m_phib << "  "
    << "quality : " << setw(4) << id.m_quality;

  return s;

}
