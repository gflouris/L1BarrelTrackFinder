//-------------------------------------------------
//
/**  \class L1MuMBMuonSorter
 *
 *   MB Muon Sorter:
 *
 *   The MB Muon Sorter receives 2 muon
 *   candidates from each of the
 *   12 Wedge Sorters and sorts out the
 *   4 best (highest pt, highest quality) muons
 *
 *
 *
 *   N. Neumeister            CERN EP
 */
//
//--------------------------------------------------
#ifndef L1MUMB_MUON_SORTER_H
#define L1MUMB_MUON_SORTER_H

//---------------
// C++ Headers --
//---------------

#include <vector>

//----------------------
// Base Class Headers --
//----------------------

#include "L1Trigger/L1BarrelMuonTrackFinder/interface/L1AbstractProcessor.h"

//------------------------------------
// Collaborating Class Declarations --
//------------------------------------

class L1MuMBTrackFinder;
class L1MuMBTrack;
class L1MuMBSecProcId;

//              ---------------------
//              -- Class Interface --
//              ---------------------

class L1MuMBMuonSorter : public L1AbstractProcessor {

  public:

    /// constructor
    L1MuMBMuonSorter(const L1MuMBTrackFinder&);

    /// destructor
    virtual ~L1MuMBMuonSorter();

    /// run Muon Sorter
    virtual void run();

    /// reset Muon Sorter
    virtual void reset();

    /// print results after sorting
    void print() const;

    /// return number of found muon candidates after sorter
    inline int numberOfTracks() const { return m_TrackCands.size(); }

    /// return pointer to a muon candidate
    inline const L1MuMBTrack* track(int id) const { return m_TrackCands[id]; }

    /// return vector of muon candidates
    inline const std::vector<const L1MuMBTrack*>& tracks() const { return m_TrackCands; }

  private:

    /// run the Cancel Out Logic of the muon sorter
    void runCOL(std::vector<L1MuMBTrack*>&) const;

    /// find out if two Sector Processors are neighbours
    static int neighbour(const L1MuMBSecProcId& spid1, const L1MuMBSecProcId& spid2);

  private:

    const L1MuMBTrackFinder&        m_tf;
    std::vector<const L1MuMBTrack*> m_TrackCands;

};

#endif
