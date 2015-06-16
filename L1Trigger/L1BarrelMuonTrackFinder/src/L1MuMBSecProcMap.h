//-------------------------------------------------
//
/**  \class L1MuMBSecProcMap
 *
 *   Sector Processor container
 *   map which contains all sector processors
 *
 *
 *
 *   N. Neumeister            CERN EP
 */
//
//--------------------------------------------------
#ifndef L1MUMB_SEC_PROC_MAP_H
#define L1MUMB_SEC_PROC_MAP_H

//---------------
// C++ Headers --
//---------------

#include <map>

//----------------------
// Base Class Headers --
//----------------------

//------------------------------------
// Collaborating Class Declarations --
//------------------------------------

#include "L1Trigger/L1BarrelMuonTrackFinder/src/L1MuMBSecProcId.h"
class L1MuMBSectorProcessor;

//              ---------------------
//              -- Class Interface --
//              ---------------------

class L1MuMBSecProcMap {

  public:

    typedef std::map<L1MuMBSecProcId, L1MuMBSectorProcessor*, std::less<L1MuMBSecProcId> >  SPmap;
    typedef SPmap::iterator                                   SPmap_iter;

    /// constructor
    L1MuMBSecProcMap();

    /// destructor
    virtual ~L1MuMBSecProcMap();

    /// return pointer to Sector Processor
    L1MuMBSectorProcessor* sp(const L1MuMBSecProcId& ) const;

    /// insert a Sector Processor into the container
    void insert(const L1MuMBSecProcId&, L1MuMBSectorProcessor* sp);

    /// return number of entries present in the container
    inline int size() const { return m_map.size(); }

    /// return iterator which points to the first entry of the container
    inline SPmap_iter begin() { return m_map.begin(); }

    /// return iterator which points to the one-past-last entry of the container
    inline SPmap_iter end() { return m_map.end(); }

  private:

    SPmap m_map;

};

#endif
