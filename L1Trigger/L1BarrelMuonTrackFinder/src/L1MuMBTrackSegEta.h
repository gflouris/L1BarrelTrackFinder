//-------------------------------------------------
//
/**  \class L1MuMBTrackSegEta
 *
 *   ETA Track Segment
 *
 *
 *
 *   N. Neumeister            CERN EP
 */
//
//--------------------------------------------------
#ifndef L1MUMB_TRACK_SEG_ETA_H
#define L1MUMB_TRACK_SEG_ETA_H

//---------------
// C++ Headers --
//---------------

#include <iosfwd>

//----------------------
// Base Class Headers --
//----------------------

//------------------------------------
// Collaborating Class Declarations --
//------------------------------------

#include "L1Trigger/L1BarrelMuonTrackFinder/src/L1MuMBTrackSegLoc.h"

//              ---------------------
//              -- Class Interface --
//              ---------------------

class L1MuMBTrackSegEta {

  public:

    /// default constructor
    L1MuMBTrackSegEta();

    /// constructor
    L1MuMBTrackSegEta(int wheel_id, int sector_id, int station_id,
                      int position = 0, int quality = 0, int bx = 17);

    /// constructor
    L1MuMBTrackSegEta(const L1MuMBTrackSegLoc&,
                      int position = 0, int quality = 0, int bx = 17);

    /// copy constructor
    L1MuMBTrackSegEta(const L1MuMBTrackSegEta&);

    /// destructor
    virtual ~L1MuMBTrackSegEta();

    /// reset eta track segment
    void reset();

    /// return wheel
    inline int wheel() const { return m_location.wheel(); }

    /// return sector
    inline int sector() const { return m_location.sector(); }

    /// return station
    inline int station() const { return m_location.station(); }

    /// return location of eta track segment
    inline const L1MuMBTrackSegLoc& where() const{ return m_location; }

    /// return position
    inline unsigned int position() const { return m_position; }

    /// return quality code
    inline unsigned int quality() const { return m_quality; }

    /// return bunch crossing
    inline int bx() const { return m_bx; }

    /// is it an empty eta track segment?
    inline bool empty() const { return m_position == 0; }

    /// assignment operator
    L1MuMBTrackSegEta& operator=(const L1MuMBTrackSegEta&);

    /// equal operator
    bool operator==(const L1MuMBTrackSegEta&) const;

    /// unequal operator
    bool operator!=(const L1MuMBTrackSegEta&) const;

    /// output stream operator
    friend std::ostream& operator<<(std::ostream&, const L1MuMBTrackSegEta&);

  private:

    L1MuMBTrackSegLoc  m_location;   // logical location of a TS
    unsigned int       m_position;   // 7 bits
    unsigned int       m_quality;    // 7 bits
    int                m_bx;         // bunch crossing identifier

};

#endif
