//-------------------------------------------------
//
/**  \class L1MuMBTrackFinder
 *
 *   L1 barrel Muon Trigger Track Finder (MTTF)
 *
 *   The barrel MTTF consists of:
 *      - 72 Sector Processors (SP),
 *      - 12 Eta Processors,
 *      - 12 Wedge Sorters (WS) and
 *      -  1 MB Muon Sorter (MS)
 *
 *
 *
 *   N. Neumeister            CERN EP
 *   J. Troconiz              UAM Madrid
 */
//
//--------------------------------------------------
#ifndef L1MUMB_TRACK_FINDER_H
#define L1MUMB_TRACK_FINDER_H

//---------------
// C++ Headers --
//---------------

#include <vector>
#include <iostream>
//----------------------
// Base Class Headers --
//----------------------


//------------------------------------
// Collaborating Class Declarations --
//------------------------------------

#include <FWCore/Framework/interface/Event.h>
#include <FWCore/ParameterSet/interface/ParameterSet.h>
#include "FWCore/Framework/interface/ConsumesCollector.h"

#include "DataFormats/L1TMuon/interface/L1TRegionalMuonCandidate.h"

class L1MuMBTFConfig;
class L1MuMBSecProcMap;
class L1MuMBSecProcId;
class L1MuMBSectorProcessor;
class L1MuMBEtaProcessor;
class L1MuMBWedgeSorter;
class L1MuMBMuonSorter;
class L1MuDTTrackCand;
class L1MuRegionalCand;

//              ---------------------
//              -- Class Interface --
//              ---------------------


class L1MuMBTrackFinder {

  public:

    /// container for muon candidates
    //typedef std::vector<L1MuRegionalCand>::const_iterator TFtracks_const_iter;
    //typedef std::vector<L1MuRegionalCand>::iterator       TFtracks_iter;

    typedef std::vector<l1t::L1TRegionalMuonCandidate>::const_iterator TFtracks_const_iter;
    typedef std::vector<l1t::L1TRegionalMuonCandidate>::iterator       TFtracks_iter;

    /// constructor
    L1MuMBTrackFinder(const edm::ParameterSet & ps, edm::ConsumesCollector && iC);

    /// destructor
    virtual ~L1MuMBTrackFinder();

    /// build the structure of the barrel MTTF
    void setup();

    /// run the barrel MTTF
    void run(const edm::Event& e, const edm::EventSetup& c);

    /// reset the barrel MTTF
    void reset();

    /// get a pointer to a Sector Processor
    const L1MuMBSectorProcessor* sp(const L1MuMBSecProcId&) const;

    /// get a pointer to an Eta Processor, index [0-11]
    inline const L1MuMBEtaProcessor* ep(int id) const { return m_epvec[id]; }

    /// get a pointer to a Wedge Sorter, index [0-11]
    inline const L1MuMBWedgeSorter* ws(int id) const { return m_wsvec[id]; }

    /// get a pointer to the MB Muon Sorter
    inline const L1MuMBMuonSorter* ms() const { return m_ms; }

    /// get number of muon candidates found by the barrel MTTF
    int numberOfTracks();

    TFtracks_const_iter begin();

    TFtracks_const_iter end();

    void clear();

    /// get number of muon candidates found by the barrel MTTF at a given bx
    int numberOfTracks(int bx);

    /// return configuration
    static L1MuMBTFConfig* config() { return m_config; }

    std::vector<L1MuDTTrackCand>& getcache0() { return _cache0; }

    //std::vector<L1MuRegionalCand>& getcache() { return _cache; } -->
    std::vector<l1t::L1TRegionalMuonCandidate>& getcache() { return _cache; }

  private:

    /// run Track Finder and store candidates in cache
    virtual void reconstruct(const edm::Event& e, const edm::EventSetup& c) { reset(); run(e,c); }

  private:

    std::vector<L1MuDTTrackCand>     _cache0;
    //std::vector<L1MuRegionalCand>    _cache;
    std::vector<l1t::L1TRegionalMuonCandidate> _cache;
    L1MuMBSecProcMap*                m_spmap;        ///< Sector Processors
    std::vector<L1MuMBEtaProcessor*> m_epvec;        ///< Eta Processors
    std::vector<L1MuMBWedgeSorter*>  m_wsvec;        ///< Wedge Sorters
    L1MuMBMuonSorter*                m_ms;           ///< MB Muon Sorter

    static L1MuMBTFConfig*           m_config;       ///< Track Finder configuration

};

#endif
