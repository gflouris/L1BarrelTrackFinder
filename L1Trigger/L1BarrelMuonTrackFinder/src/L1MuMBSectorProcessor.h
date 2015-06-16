//-------------------------------------------------
//
/**  \class L1MuMBSectorProcessor
 *
 *   Sector Processor:
 *
 *   A Sector Processor consists of:
 *    - one Data Buffer,
 *    - one Extrapolation Unit (EU),
 *    - one Track Assembler (TA) and
 *    - two Assignment Units (AU)
 *
 *
 *
 *   N. Neumeister            CERN EP
 *   J. Troconiz              UAM Madrid
 */
//
//--------------------------------------------------
#ifndef L1MUMB_SECTOR_PROCESSOR_H
#define L1MUMB_SECTOR_PROCESSOR_H

//---------------
// C++ Headers --
//---------------

#include <vector>

//----------------------
// Base Class Headers --
//----------------------

#include "L1Trigger/L1BarrelMuonTrackFinder/src/L1MuMBSecProcId.h"

//------------------------------------
// Collaborating Class Declarations --
//------------------------------------

#include <FWCore/Framework/interface/Event.h>
class L1MuMBSectorReceiver;
class L1MuMBDataBuffer;
class L1MuMBExtrapolationUnit;
class L1MuMBTrackAssembler;
class L1MuMBAssignmentUnit;
class L1MuMBTrackFinder;
class L1MuMBTrack;

//              ---------------------
//              -- Class Interface --
//              ---------------------

class L1MuMBSectorProcessor {

  public:

    /// constructor
    L1MuMBSectorProcessor(const L1MuMBTrackFinder&, const L1MuMBSecProcId& );

    /// destructor
    virtual ~L1MuMBSectorProcessor();

    /// run the Sector Processor
    virtual void run(int bx, const edm::Event& e, const edm::EventSetup& c);

    /// reset the Sector Processor
    virtual void reset();

    /// print muon candidates found by the Sector Processor
    void print() const;

    /// return pointer to the next wheel neighbour
    const L1MuMBSectorProcessor* neighbour() const;

    /// return Sector Processor identifier
    inline const L1MuMBSecProcId& id() const { return m_spid; }

    /// return reference to barrel MTTF
    inline const L1MuMBTrackFinder& tf() const { return m_tf; }

    /// is it a barrel-only Sector Processor?
    inline bool brl() const { return !m_spid.ovl(); }

    /// is it an overlap region Sector Processor?
    inline bool ovl() const { return m_spid.ovl(); }

    /// return pointer to Data Buffer
    inline const L1MuMBDataBuffer* data() const { return m_DataBuffer; }
    inline L1MuMBDataBuffer* data() { return m_DataBuffer; }

    /// return pointer to Extrapolation Unit
    inline const L1MuMBExtrapolationUnit* EU() const { return m_EU; }

    /// return pointer to Track Assembler
    inline const L1MuMBTrackAssembler* TA() const { return m_TA; }

    /// return pointer to Assignment Unit, index [0,1]
    inline const L1MuMBAssignmentUnit* AU(int id) const { return m_AUs[id]; }

    /// return pointer to muon candidate, index [0,1]
    inline L1MuMBTrack* track(int id) const { return m_TrackCands[id]; }

    /// return pointer to muon candidate, index [0,1]
    inline L1MuMBTrack* tracK(int id) const { return m_TracKCands[id]; }

  private:

    /// are there any non-empty muon candidates?
    bool anyTrack() const;

  private:

    const L1MuMBTrackFinder&            m_tf;
    L1MuMBSecProcId                     m_spid;

    L1MuMBSectorReceiver*               m_SectorReceiver;
    L1MuMBDataBuffer*                   m_DataBuffer;
    L1MuMBExtrapolationUnit*            m_EU;
    L1MuMBTrackAssembler*               m_TA;
    std::vector<L1MuMBAssignmentUnit*>  m_AUs;

    std::vector<L1MuMBTrack*>           m_TrackCands;
    std::vector<L1MuMBTrack*>           m_TracKCands;

};

#endif
