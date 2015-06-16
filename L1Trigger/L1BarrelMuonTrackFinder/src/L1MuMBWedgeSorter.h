//-------------------------------------------------
//
/**  \class L1MuMBWedgeSorter
 *
 *   Wedge Sorter:
 *
 *   A Wedge Sorter receives 2 muon candidates
 *   from each of the 6 Sector Processors of a
 *   wedge and forwards the 2 highest rank
 *   candidates per wedge to the MB Muon Sorter
 *
 *
 *
 *   N. Neumeister            CERN EP
 */
//
//--------------------------------------------------
#ifndef L1MUMB_WEDGE_SORTER_H
#define L1MUMB_WEDGE_SORTER_H

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

class L1MuMBWedgeSorter : public L1AbstractProcessor {

  public:

    /// constructor
    L1MuMBWedgeSorter(const L1MuMBTrackFinder&, int id );

    /// destructor
    virtual ~L1MuMBWedgeSorter();

    /// return Wedge Sorter identifier (0-11)
    inline int id() const { return m_wsid; }

    /// run Wedge Sorter
    virtual void run();

    /// reset Wedge Sorter
    virtual void reset();

    /// print results after sorting
    void print() const;

    /// return vector of muon candidates
    inline const std::vector<const L1MuMBTrack*>& tracks() const { return m_TrackCands; }

  private:

    /// run the Cancel Out Logic of the wedge sorter
    void runCOL(std::vector<L1MuMBTrack*>&) const;

    /// are there any non-empty muon candidates in the Wedge Sorter?
    bool anyTrack() const;

    /// find out if two Sector Processors are neighbours in the same wedge
    static bool neighbour(const L1MuMBSecProcId& spid1, const L1MuMBSecProcId& spid2);

  private:

    const L1MuMBTrackFinder&        m_tf;
    int                             m_wsid;

    std::vector<const L1MuMBTrack*> m_TrackCands;

};

#endif
