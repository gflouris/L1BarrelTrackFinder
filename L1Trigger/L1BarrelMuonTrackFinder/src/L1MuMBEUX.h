//-------------------------------------------------
//
/**  \class L1MuMBEUX
 *
 *   Extrapolator:
 *
 *   The Extrapolator receives a start and
 *   a target track segment and performs the
 *   actual extrapolation
 *
 *
 *
 *   N. Neumeister            CERN EP
 */
//
//--------------------------------------------------
#ifndef L1MUMB_EUX_H
#define L1MUMB_EUX_H

//---------------
// C++ Headers --
//---------------

#include <utility>
#include <map>

//----------------------
// Base Class Headers --
//----------------------

#include "L1Trigger/L1BarrelMuonTrackFinder/interface/L1AbstractProcessor.h"

//------------------------------------
// Collaborating Class Declarations --
//------------------------------------

#include <FWCore/Framework/interface/ESHandle.h>
class L1MuMBTrackSegPhi;
class L1MuMBSectorProcessor;
class L1MuMBSEU;
class L1MuDTExtLut;
class L1MuDTTFParameters;

//              ---------------------
//              -- Class Interface --
//              ---------------------

class L1MuMBEUX : public L1AbstractProcessor {

  public:

    /// constructor
    L1MuMBEUX(const L1MuMBSectorProcessor& sp, const L1MuMBSEU& seu, int id );

    /// destructor
    virtual ~L1MuMBEUX();

    /// equal operator
    bool operator==(const L1MuMBEUX&) const;

    /// run Extrapolator
    virtual void run(const edm::EventSetup& c);

    /// reset Extrapolator
    virtual void reset();

    /// load data into EUX
    void load(const L1MuMBTrackSegPhi* start_ts, const L1MuMBTrackSegPhi* target_ts);

    /// return pointer to start and target track segment
    std::pair<const L1MuMBTrackSegPhi*, const L1MuMBTrackSegPhi*> ts() const;

    /// helper class for finding the best and second best extrapolation
    class EUX_Comp : std::binary_function< L1MuMBEUX*, L1MuMBEUX*, bool> {
      public :
        EUX_Comp( const L1MuMBEUX* k = 0 ) : _not(k) {}
        bool operator()( const L1MuMBEUX* first, const L1MuMBEUX* second ) const {
          if ( !second->result() ) return false;
          if ( _not != 0 && *first  == *_not ) return true;
          if ( _not != 0 && *second == *_not ) return false;
          return ( first->quality() < second->quality() );
        }
      private:
        const L1MuMBEUX* _not;
    };

    /// return Extrapolation identifier
    inline int id() const { return m_id; }

    /// return extrapolation result
    inline bool result() const { return m_result; }

    /// return extrapolation quality
    inline unsigned int quality() const { return m_quality; }

    /// return extrapolation address (0-11) (address = 15 indicates negative ext. result)
    inline unsigned short int address() const { return m_address; }

  private:

    /// output sector numbers in the range -6 to +5
    int sec_mod(int) const;

  private:

    const L1MuMBSectorProcessor& m_sp;
    const L1MuMBSEU& m_seu;           // reference to Single Extrapolation Unit
    int              m_id;            // index of start TS

    bool               m_result;      //@@ 1 bit
    unsigned short int m_quality;     //@@ 1 bit
    unsigned short int m_address;     //@@ 4 bits

    const L1MuMBTrackSegPhi* m_start;       // start track segment
    const L1MuMBTrackSegPhi* m_target;      // target track segment

    edm::ESHandle< L1MuDTExtLut > theExtLUTs;  // extrapolation look-up tables
    int            const   theExtFilter = 1;        // extrapolation quality filter
    unsigned short const   nbit_phi = 12;           // number of bits used for phi
    unsigned short const   nbit_phib = 10;          // number of bits used for phib

    edm::ESHandle< L1MuDTTFParameters > pars;

};

#endif
