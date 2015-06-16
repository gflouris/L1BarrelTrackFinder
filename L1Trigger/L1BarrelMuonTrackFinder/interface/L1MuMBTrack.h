//-------------------------------------------------
//
/**  \class L1MuMBTrack
 *
 *   L1 Muon Track Candidate
 *
 *
 *
 *   N. Neumeister            CERN EP
 *   J. Troconiz              UAM Madrid
 */
//
//--------------------------------------------------
#ifndef L1MUMB_TRACK_H
#define L1MUMB_TRACK_H

//---------------
// C++ Headers --
//---------------

#include <iosfwd>
#include <string>
#include <vector>
#include <functional>

//----------------------
// Base Class Headers --
//----------------------

//#include "/home/gflouris/MBTF/DebugEmulator/CMSSW_7_2_0/src/DataFormats/L1GlobalMuonTrigger/interface/L1MuRegionalCand.h"
#include "DataFormats/L1TMuon/interface/L1TRegionalMuonCandidate.h"
#include "DataFormats/L1TMuon/interface/L1TMuonCandidateTrack.h"

//------------------------------------
// Collaborating Class Declarations --
//------------------------------------

#include <FWCore/Framework/interface/ESHandle.h>
#include <FWCore/Framework/interface/EventSetup.h>
#include "L1Trigger/L1BarrelMuonTrackFinder/src/L1MuMBTrackAssParam.h"
#include "L1Trigger/L1BarrelMuonTrackFinder/src/L1MuMBTrackAssParam.h"
#include "L1Trigger/L1BarrelMuonTrackFinder/src/L1MuMBAddressArray.h"
#include "L1Trigger/L1BarrelMuonTrackFinder/src/L1MuMBTrackSegPhi.h"
#include "L1Trigger/L1BarrelMuonTrackFinder/src/L1MuMBTrackSegEta.h"
#include "L1Trigger/L1BarrelMuonTrackFinder/src/L1MuMBSecProcId.h"

#include "DataFormats/L1TMuon/interface/L1TMuonInternalTrack.h"

using namespace L1TMuon;

//              ---------------------
//              -- Class Interface --
//              ---------------------

class L1MuMBTrack : public l1t::L1TRegionalMuonCandidate {

  public:

    /// default constructor
    L1MuMBTrack();

    /// constructor
    L1MuMBTrack(const L1MuMBSecProcId&);

    /// copy constructor
    L1MuMBTrack(const L1MuMBTrack&);

    /// destructor
    virtual ~L1MuMBTrack();

    /// reset muon candidate
    void reset();

    /// get name of object
    inline std::string name() const { return m_name; }

    /// get pt-code (5 bits)
    inline unsigned int pt() const { return hwPt(); }

    /// get phi-code (8 bits)
    inline unsigned int phi() const { return hwPhi(); }

    /// get eta-code (6 bits)
    inline unsigned int eta() const { return hwEta(); }

    /// get fine eta bit
    inline bool fineEtaBit() const { return 1;}//return isFineHalo(); }//Implement later - Giannis

    /// get charge (1 bit)
    inline int charge() const { return hwSign(); }

    /// get quality
    inline unsigned int quality() const { return hwQual(); } //Giannis mod

    /// get track-class
    inline TrackClass tc() const { return m_tc; }

    /// is it an empty  muon candidate?
    inline bool empty() const { return m_empty; }

    /// return Sector Processor in which the muon candidate was found
    inline const L1MuMBSecProcId& spid() const { return m_spid; }

    /// get address-array for this muon candidate
    inline L1MuMBAddressArray address() const { return m_addArray; }

    /// get relative address of a given station
    inline int address(int stat) const { return m_addArray.station(stat); }

    /// return number of phi track segments used to form the muon candidate
    inline int numberOfTSphi() const { return m_tsphiList.size(); }

    /// return number of eta track segments used to form the muon candidate
    inline int numberOfTSeta() const { return m_tsetaList.size(); }

    /// return all phi track segments of the muon candidate
    const std::vector<L1MuMBTrackSegPhi>& getTSphi() const { return m_tsphiList; }

    /// return start phi track segment of muon candidate
    const L1MuMBTrackSegPhi& getStartTSphi() const;

    /// return end phi track segment of muon candidate
    const L1MuMBTrackSegPhi& getEndTSphi() const;

    /// return all eta track segments of the muon candidate
    const std::vector<L1MuMBTrackSegEta>& getTSeta() const { return m_tsetaList; }

    /// return start eta track segment of muon candidate
    const L1MuMBTrackSegEta& getStartTSeta() const;

    /// return end eta track segment of muon candidate
    const L1MuMBTrackSegEta& getEndTSeta() const;

    /// enable muon candidate
    inline void enable() { m_empty = false;  };//setType(0);} Giannis

    /// disable muon candidate
    inline void disable() { m_empty = true; }

    /// set name of object
    inline void setName(std::string name) { m_name = name; }

    /// set track-class of muon candidate
    inline void setTC(TrackClass tc) { m_tc = tc; }

    /// set phi-code of muon candidate
    inline void setPhi(int phi) { setHwPhi(phi); }

    /// set eta-code of muon candidate
    void setEta(int eta);

    /// set fine eta bit
    inline void setFineEtaBit() {  }//setFineHalo(true); } Implement later - Giannis

    /// set pt-code of muon candidate
    inline void setPt(int pt) { setHwPt(pt); }

    /// set charge of muon candidate
    inline void setCharge(int charge) { setHwSign(charge); };//setChargeValid(true); } - Giannis

    /// set quality of muon candidate
    inline void setQuality(unsigned int quality) { setHwQual(quality); }

    /// set relative addresses of muon candidate
    inline void setAddresses(const L1MuMBAddressArray& addr) { m_addArray = addr; }

    /// set phi track segments used to form the muon candidate
    void setTSphi(const std::vector<const L1MuMBTrackSegPhi*>& tsList);

    /// set eta track segments used to form the muon candidate
    void setTSeta(const std::vector<const L1MuMBTrackSegEta*>& tsList);

    /// convert  pt value in GeV to pt code
    unsigned int triggerScale(float value, const edm::EventSetup& c) const;

    /// Dummy - Giannis
    //void setBx(int bx) {  }
    //int bx() const { return  0; }


    /// assignment operator
    L1MuMBTrack& operator=(const L1MuMBTrack&);

    /// equal operator
    bool operator==(const L1MuMBTrack&) const;

    /// unequal operator
    bool operator!=(const L1MuMBTrack&) const;

    /// print parameters of muon candidate
    void print() const;

    /// output stream operator
    friend std::ostream& operator<<(std::ostream&, const L1MuMBTrack&);

    /// define a rank for muon candidates
    class Rank : std::binary_function< const L1MuMBTrack*, const L1MuMBTrack*, bool> {
      public :
        bool operator()( const L1MuMBTrack* first, const L1MuMBTrack* second ) const {
         unsigned short int rank_f = 0;  // rank of first
         unsigned short int rank_s = 0;  // rank of second
         if ( first )  rank_f = 10 * first->pt()  + first->quality();
         if ( second ) rank_s = 10 * second->pt() + second->quality();
         return rank_f > rank_s;
       }
    };


  private:

    L1MuMBSecProcId  m_spid;      // which SP found the track
    std::string      m_name;
    bool             m_empty;
    TrackClass       m_tc;

    L1MuMBAddressArray         m_addArray;
    std::vector<L1MuMBTrackSegPhi>  m_tsphiList;
    std::vector<L1MuMBTrackSegEta>  m_tsetaList;

};

#endif
