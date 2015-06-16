//-------------------------------------------------
//
/**  \class L1MuMBEtaProcessor
 *
 *   Eta Processor:
 *
 *   An Eta Processor consists of :
 *    - one receiver unit,
 *    - one Eta Track Finder (ETF) and
 *    - one Eta Matching Unit (EMU)
 *
 *
 *
 *   N. Neumeister            CERN EP
 *   J. Troconiz              UAM Madrid
 */
//
//--------------------------------------------------
#ifndef L1MUMB_ETA_PROCESSOR_H
#define L1MUMB_ETA_PROCESSOR_H

//---------------
// C++ Headers --
//---------------

#include <vector>

//----------------------
// Base Class Headers --
//----------------------

//------------------------------------
// Collaborating Class Declarations --
//------------------------------------

#include <DataFormats/Common/interface/Handle.h>
#include <FWCore/Framework/interface/Event.h>
#include <FWCore/Framework/interface/ESHandle.h>
#include <FWCore/Framework/interface/EventSetup.h>
#include "L1Trigger/L1BarrelMuonTrackFinder/src/L1MuMBAddressArray.h"
class L1MuMBTrackSegEta;
class L1MuMBTrackFinder;
class L1MuMBTrack;
class L1MuDTEtaPatternLut;
class L1MuDTQualPatternLut;
class L1MuDTTFMasks;

//              ---------------------
//              -- Class Interface --
//              ---------------------

class L1MuMBEtaProcessor {

  public:

    /// constructor
    L1MuMBEtaProcessor(const L1MuMBTrackFinder&, int id );

    /// destructor
    virtual ~L1MuMBEtaProcessor();

    /// return Eta Processor identifier (0-11)
    inline int id() const { return m_epid; }

    /// run the Eta Processor
    virtual void run(int bx, const edm::Event& e, const edm::EventSetup& c);

    /// reset the Eta Processor
    virtual void reset();

    /// print muon candidates found by the Eta Processor
    void print() const;

    /// return reference to barrel MTTF
    inline const L1MuMBTrackFinder& tf() const { return m_tf; }

    /// return eta values, index [0,11]
    inline int eta(int id) const { return m_eta[id]; }

    /// return fine bit, index [0,11]
    inline bool fineBit(int id) const { return m_fine[id]; }

  private:

    /// receive data (eta trigger primitives)
    void receiveData(int bx, const edm::Event& e, const edm::EventSetup& c);

    /// receive addresses (from 6 Sector Processors)
    void receiveAddresses();

    /// run Eta Track Finder (ETF)
    void runEtaTrackFinder(const edm::EventSetup& c);

    /// run Eta Matching Unit (EMU)
    void runEtaMatchingUnit(const edm::EventSetup& c);

    /// assign eta and etaFineBit
    void assign();

    /// get quality code; id [0,26], stat [1,3]
    static int quality(int id, int stat);

  private:

    const L1MuMBTrackFinder&                  m_tf;
    int                                       m_epid;

    int                                       m_mask;

    int                                       m_eta[12];
    bool                                      m_fine[12];

    std::vector<int>                          m_foundPattern;
    int                                       m_pattern[12];

    int                                       m_address[12];
    L1MuMBTrack*                              m_TrackCand[12];
    L1MuMBTrack*                              m_TracKCand[12];
    std::vector<const L1MuMBTrackSegEta*>     m_tseta;

    edm::ESHandle< L1MuDTEtaPatternLut >  theEtaPatternLUT;  // ETF look-up table
    edm::ESHandle< L1MuDTQualPatternLut > theQualPatternLUT; // EMU look-up tables
    edm::ESHandle< L1MuDTTFMasks >        msks;

};

#endif
