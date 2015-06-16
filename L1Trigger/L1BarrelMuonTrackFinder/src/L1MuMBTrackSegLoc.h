//-------------------------------------------------
//
/**  \class L1MuMBTrackSegLoc
 *
 *   Logical location of a Track Segment:
 *
 *   The location of a track segment is
 *   given by a triple (wheel, sector, station)
 *   with wheel: -3, -2, -1, 0, +1, +2, +3
 *   ( -3, +3 : are forward- and backward-endcaps),<BR>
 *   sector: 0-11 (30 deg sectors!)<BR>
 *   station: 1-5 (station 5=ME13)
 *
 *
 *
 *   N. Neumeister            CERN EP 
 */
//
//--------------------------------------------------
#ifndef L1MUMB_TRACK_SEG_LOC_H
#define L1MUMB_TRACK_SEG_LOC_H

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

//              ---------------------
//              -- Class Interface --
//              ---------------------

class L1MuMBTrackSegLoc {

  public:
 
    /// default constructor
    L1MuMBTrackSegLoc();

    /// constructor
    L1MuMBTrackSegLoc(int wheel_id, 
                      int sector_id,
                      int station_id); 
  
    /// copy constructor
    L1MuMBTrackSegLoc(const L1MuMBTrackSegLoc&);

    /// destructor
    virtual ~L1MuMBTrackSegLoc();

    /// return wheel 
    inline int wheel() const { return m_wheel; }
    
    /// return sector (30 deg)
    inline int sector() const { return m_sector; }
    
    /// return station
    inline int station() const { return m_station; }

    /// assignment operator
    L1MuMBTrackSegLoc& operator=(const L1MuMBTrackSegLoc&);

    /// equal operator
    bool operator==(const L1MuMBTrackSegLoc&) const;
    
    /// unequal operator
    bool operator!=(const L1MuMBTrackSegLoc&) const;
    
    /// less operator
    bool operator<(const L1MuMBTrackSegLoc&) const;
  
    /// output stream operator
    friend std::ostream& operator<<(std::ostream&, const L1MuMBTrackSegLoc&);

  private:
 
    int m_wheel;
    int m_sector;
    int m_station;
  
};
  
#endif
