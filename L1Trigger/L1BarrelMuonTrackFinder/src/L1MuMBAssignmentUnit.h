//-------------------------------------------------
//
/**  \class L1MuMBAssignmentUnit
 *
 *   Assignment Unit:
 *
 *   assigns pt, charge, phi
 *   and quality to a muon candidate
 *   found by the Track Assembler
 *
 *
 *
 *   N. Neumeister            CERN EP
 *   J. Troconiz              UAM Madrid
 */
//
//--------------------------------------------------
#ifndef L1MUMB_ASSIGNMENT_UNIT_H
#define L1MUMB_ASSIGNMENT_UNIT_H

//---------------
// C++ Headers --
//---------------

#include <vector>
#include <iosfwd>

//----------------------
// Base Class Headers --
//----------------------

#include "L1Trigger/L1BarrelMuonTrackFinder/interface/L1AbstractProcessor.h"

//------------------------------------
// Collaborating Class Declarations --
//------------------------------------
#include "CondFormats/L1TObjects/interface/L1MuDTPtaLut.h"
#include "CondFormats/L1TObjects/interface/L1MuDTPhiLut.h"


#include <FWCore/Framework/interface/ESHandle.h>
#include "CondFormats/L1TObjects/interface/L1MuDTAssParam.h"
#include "L1Trigger/L1BarrelMuonTrackFinder/src/L1MuMBAddressArray.h"
//class L1MuMBPhiLut;
//class L1MuMBPtaLut;
class L1MuMBTrackSegPhi;
class L1MuMBSectorProcessor;
//typedef L1MuMBPhiLut::L1MuMBPhiLut L1PhiLUT;
//              ---------------------
//              -- Class Interface --
//              ---------------------

class L1MuMBAssignmentUnit : public L1AbstractProcessor {

  public:

    /// constructor
    L1MuMBAssignmentUnit(L1MuMBSectorProcessor& sp, int id );

    /// destructor
    virtual ~L1MuMBAssignmentUnit();

    /// run Assignment Unit
    virtual void run(const edm::EventSetup& c);

    /// reset Assignment Unit
    virtual void reset();

    /// assign phi
    void PhiAU(const edm::EventSetup& c);

    /// assign pt and charge
    void PtAU(const edm::EventSetup& c);

    /// assign quality
    void QuaAU();

    /// set precision of phi and phib
    static void setPrecision();

  private:

    /// Track Segment Router
    void TSR();

    /// get track segment from a given station
    const L1MuMBTrackSegPhi* getTSphi(int station) const;

    /// convert sector Id to 8 bit code (= sector center)
    static int convertSector(int);

    /// determine charge
    static int getCharge(PtAssMethod);

    /// determine pt assignment method
    PtAssMethod getPtMethod() const;

    /// calculate bend angle
    int getPtAddress(PtAssMethod, int bendcharge=0) const;

    /// build difference of two phi values
    int phiDiff(int stat1, int stat2) const;

  private:

    L1MuMBSectorProcessor& m_sp;
    int                    m_id;

    L1MuMBAddressArray                    m_addArray;
    std::vector<const L1MuMBTrackSegPhi*> m_TSphi;
    PtAssMethod                           m_ptAssMethod;

    //edm::ESHandle< L1MuMBPhiLut > thePhiLUTs;  ///< phi-assignment look-up tables
    //edm::ESHandle< L1MuMBPtaLut > thePtaLUTs;  ///< pt-assignment look-up tables
    L1MuDTPtaLut  *thePtaLUTs =  new typename L1MuDTPtaLut::L1MuDTPtaLut();   ///< pt-assignment look-up tables Giannis
    L1MuDTPhiLut  *thePhiLUTs =  new typename L1MuDTPhiLut::L1MuDTPhiLut();  ///< phi-assignment look-up tables Giannis
    static unsigned short      nbit_phi;       ///< # of bits used for pt-assignment
    static unsigned short      nbit_phib;      ///< # of bits used for pt-assignment

};

#endif
