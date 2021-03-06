//-------------------------------------------------
//
//   Class: L1MuMBTrack
//
//   Description: Muon Track Candidate
//
//
//
//   Author :
//   N. Neumeister            CERN EP
//   J. Troconiz              UAM Madrid
//
//--------------------------------------------------

//-----------------------
// This Class's Header --
//-----------------------

#include "L1Trigger/L1BarrelMuonTrackFinder/interface/L1MuMBTrack.h"

//---------------
// C++ Headers --
//---------------

#include <iostream>
#include <iomanip>

//-------------------------------
// Collaborating Class Headers --
//-------------------------------

#include "L1Trigger/L1BarrelMuonTrackFinder/src/L1MuMBSecProcId.h"
#include "L1Trigger/L1BarrelMuonTrackFinder/src/L1MuMBTrackSegPhi.h"
#include "L1Trigger/L1BarrelMuonTrackFinder/src/L1MuMBTrackSegEta.h"
#include "CondFormats/L1TObjects/interface/L1MuTriggerPtScale.h"
#include "CondFormats/DataRecord/interface/L1MuTriggerPtScaleRcd.h"
#include "CondFormats/L1TObjects/interface/L1MuPacking.h"

using namespace std;

#include "DataFormats/L1TMuon/interface/L1TMuonInternalTrack.h"

// --------------------------------
//       class L1MuMBTrack
//---------------------------------

//----------------
// Constructors --
//----------------
L1MuMBTrack::L1MuMBTrack() :
               //L1MuRegionalCand(0,0),-->
               l1t::L1TRegionalMuonCandidate(),
               m_spid(L1MuMBSecProcId()), m_name("L1MuMBTrack"), m_empty(true),
               m_tc(UNDEF),
               m_addArray(), m_tsphiList(), m_tsetaList() {

  m_tsphiList.reserve(4);
  m_tsetaList.reserve(3);

  //setType(0);    //Giannis
  //setChargeValid(true);    //Giannis

}


L1MuMBTrack::L1MuMBTrack(const L1MuMBSecProcId& spid) :
               //L1MuRegionalCand(0,0),-->
               l1t::L1TRegionalMuonCandidate(),
               m_spid(spid), m_name("L1MuMBTrack"), m_empty(true),
               m_tc(UNDEF),
               m_addArray(), m_tsphiList(), m_tsetaList() {

  m_tsphiList.reserve(4);
  m_tsetaList.reserve(3);
  //setType(0);    //Giannis
  //setChargeValid(true);    //Giannis

}


L1MuMBTrack::L1MuMBTrack(const L1MuMBTrack& id) :
               //L1MuRegionalCand(id),-->
               l1t::L1TRegionalMuonCandidate(id),
               m_spid(id.m_spid), m_name(id.m_name), m_empty(id.m_empty),
               m_tc(id.m_tc),
               m_addArray(id.m_addArray),
               m_tsphiList(id.m_tsphiList), m_tsetaList(id.m_tsetaList) {}


//--------------
// Destructor --
//--------------
L1MuMBTrack::~L1MuMBTrack() {}


//--------------
// Operations --
//--------------

//
// reset Muon Track Candidate
//
void L1MuMBTrack::reset() {

  //L1MuRegionalCand::reset(); Giannis(?)
  m_empty   = true;
  m_tc      = UNDEF;
  m_addArray.reset();
  m_tsphiList.clear();
  m_tsetaList.clear();

}


//
// set (packed) eta-code of muon candidate
//
void L1MuMBTrack::setEta(int eta) {

  // eta is a signed integer [-32,31],
  // representing 64 bins in an interval [-1.2,+1.2]
  // first convert eta into an unsigned integer
  L1MuSignedPacking<6> pEta;
//  setEtaPacked(pEta.packedFromIdx(eta)); -->
  setHwEta(pEta.packedFromIdx(eta));


}


//
// return start phi track segment
//
const L1MuMBTrackSegPhi& L1MuMBTrack::getStartTSphi() const {

  return m_tsphiList.front();

}


//
// return end phi track segment
//
const L1MuMBTrackSegPhi& L1MuMBTrack::getEndTSphi() const {

  return m_tsphiList.back();

}


//
// return start eta track segment
//
const L1MuMBTrackSegEta& L1MuMBTrack::getStartTSeta() const {

  return m_tsetaList.front();

}


//
// return end eta track segment
//
const L1MuMBTrackSegEta& L1MuMBTrack::getEndTSeta() const {

  return m_tsetaList.back();

}


//
// set phi track segments used to form the muon candidate
//
void L1MuMBTrack::setTSphi(const vector<const L1MuMBTrackSegPhi*>& tsList) {

  if ( !tsList.empty() ) {
    vector<const L1MuMBTrackSegPhi*>::const_iterator iter;
    for ( iter = tsList.begin(); iter != tsList.end(); iter++ ) {
      if ( *iter ) m_tsphiList.push_back(**iter);
    }
  }

}


//
// set eta track segments used to form the muon candidate
//
void L1MuMBTrack::setTSeta(const vector<const L1MuMBTrackSegEta*>& tsList) {

  if ( !tsList.empty() ) {
    vector<const L1MuMBTrackSegEta*>::const_iterator iter;
    for ( iter = tsList.begin(); iter != tsList.end(); iter++ ) {
      if ( *iter ) m_tsetaList.push_back(**iter);
    }
  }

}


//
// convert pt value in GeV to pt code
//
unsigned int L1MuMBTrack::triggerScale(float value, const edm::EventSetup& c) const {

  const float eps = 1.e-5; // add an epsilon so that setting works with low edge value

  edm::ESHandle< L1MuTriggerPtScale > theTriggerScales;
  c.get< L1MuTriggerPtScaleRcd >().get( theTriggerScales );
  unsigned int t_Scale = theTriggerScales->getPtScale()->getPacked( value + eps );

  return t_Scale;
}


//
// Assignment operator
//
L1MuMBTrack& L1MuMBTrack::operator=(const L1MuMBTrack& track) {

  if ( this != &track ) {
    this->setBx(track.bx());
    //this->setDataWord(track.getDataWord()); Giannis(?)
    m_spid      = track.m_spid;
    m_empty     = track.m_empty;
    m_name      = track.m_name;
    m_tc        = track.m_tc;
    m_addArray  = track.m_addArray;
    m_tsphiList = track.m_tsphiList;
    m_tsetaList = track.m_tsetaList;
  }
  return *this;

}


//
// Equal operator
//
bool L1MuMBTrack::operator==(const L1MuMBTrack& track) const {

  if ( m_spid       != track.m_spid )       return false;
  if ( m_empty      != track.m_empty )      return false;
  if ( m_tc         != track.m_tc )         return false;
  if ( bx()         != track.bx() )         return false;
  if ( phi()        != track.phi() )        return false;
  if ( eta()        != track.eta() )        return false;
  if ( fineEtaBit() != track.fineEtaBit() ) return false;
  if ( pt()         != track.pt() )         return false;
  if ( charge()     != track.charge() )     return false;
  if ( quality()    != track.quality() )    return false;
  if ( m_addArray   != track.m_addArray )   return false;
  return true;

}


//
// Unequal operator
//
bool L1MuMBTrack::operator!=(const L1MuMBTrack& track) const {

  if ( m_spid       != track.m_spid )       return true;
  if ( m_empty      != track.m_empty )      return true;
  if ( m_tc         != track.m_tc )         return true;
  if ( bx()         != track.bx() )         return true;
  if ( phi()        != track.phi() )        return true;
  if ( eta()        != track.eta() )        return true;
  if ( fineEtaBit() != track.fineEtaBit() ) return true;
  if ( pt()         != track.pt() )         return true;
  if ( charge()     != track.charge() )     return true;
  if ( quality()    != track.quality() )    return true;
  if ( m_addArray   != track.m_addArray )   return true;
  return false;

}


//
// print parameters of track candidate
//
void L1MuMBTrack::print() const {

  if ( !empty() ) {
    cout.setf(ios::showpoint);
    cout.setf(ios::right,ios::adjustfield);
    cout << setiosflags(ios::showpoint | ios::fixed);
    cout << "MUON : "
         << "pt = "      << setw(3) << hwPt() << "  "
         << "charge = "  << setw(2) << hwSign() << "  "
         << "eta = "     << setw(2) << hwEta()
         //<< " ("         << setw(1) << finehalo_packed() << ")  "
         << "phi = "     << setw(3) << hwPhi() << "  "
         << "quality = " << setw(1) << hwQual() << '\t'
         << "class = "   << tc() << "  "
         << "bx = "      << setw(2) << bx() << endl;
    cout << "       found in " << m_spid << " with phi track segments :" << endl;
    vector<L1MuMBTrackSegPhi>::const_iterator iter;
    for ( iter = m_tsphiList.begin(); iter != m_tsphiList.end(); iter++ ) {
       cout << "       " << (*iter) << endl;
    }
  }

}


//
// output stream operator for track candidate
//
ostream& operator<<(ostream& s, const L1MuMBTrack& id) {

  if ( !id.empty() ) {
    s << setiosflags(ios::showpoint | ios::fixed)
      << "pt = "      << setw(3) << id.hwPt() << "  "
      << "charge = "  << setw(2) << id.hwSign() << "  "
      << "eta = "     << setw(2) << id.hwEta()
      //<< " ("         << setw(1) << id.finehalo_packed() << ")  "
      << "phi = "     << setw(3) << id.hwPhi() << "  "
      << "quality = " << setw(1) << id.hwQual() << '\t'
      << "bx = "      << setw(2) << id.bx();
  }
  return s;

}
