//-------------------------------------------------
//
/**  \class L1MuMBERS
 *
 *   Extrapolation Result Selector (Quality Sorter Unit):
 *
 *   selects the 2 best (highest target quality)
 *   out of the 12 (6) extrapolations
 *   performed per start track segment
 *
 *
 *
 *   N. Neumeister            CERN EP
 */
//
//--------------------------------------------------
#ifndef L1MUMB_ERS_H
#define L1MUMB_ERS_H

//---------------
// C++ Headers --
//---------------

#include <utility>

//----------------------
// Base Class Headers --
//----------------------

#include "L1Trigger/L1BarrelMuonTrackFinder/interface/L1AbstractProcessor.h"

//------------------------------------
// Collaborating Class Declarations --
//------------------------------------

class L1MuMBTrackSegPhi;
class L1MuMBSEU;

//              ---------------------
//              -- Class Interface --
//              ---------------------

class L1MuMBERS : public L1AbstractProcessor {

  public:

    /// constructor
    L1MuMBERS(const L1MuMBSEU& );

    /// destructor
    virtual ~L1MuMBERS();

    /// run L1MuMBERS
    virtual void run();

    /// reset ERS
    virtual void reset();

    /// return extrapolation quality
    inline unsigned int quality(int id) const { return m_quality[id]; }

    /// return extrapolation address; (address = 15 indicates negative ext. result)
    inline unsigned short int address(int id) const { return m_address[id]; }

    /// return pointer to start and target track segment
    std::pair<const L1MuMBTrackSegPhi*, const L1MuMBTrackSegPhi*> ts(int id) const;

  private:

    const L1MuMBSEU& m_seu;

    unsigned short int m_quality[2];   //@@ 1 bit
    unsigned short int m_address[2];   //@@ 4 bits

    const L1MuMBTrackSegPhi* m_start[2];
    const L1MuMBTrackSegPhi* m_target[2];

};

#endif
