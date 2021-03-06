//-------------------------------------------------
//
/**  \class L1MuMBTrackSegPhi
 *
 *   PHI Track Segment
 *
 *
 *
 *   N. Neumeister            CERN EP
 */
//
//--------------------------------------------------
#ifndef L1MUMB_TRACK_SEG_PHI_H
#define L1MUMB_TRACK_SEG_PHI_H

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

class L1MuMBTrackSegPhi {

  public:

    /// quality code of MBBX phi track segments
    enum TSQuality { Li, Lo, Hi, Ho, LL, HL, HH, Null };

    /// default constructor
    L1MuMBTrackSegPhi();

    /// constructor
    L1MuMBTrackSegPhi(int wheel_id, int sector_id, int station_id,
                      int phi = 0, int phib = 0,
                      TSQuality quality = Null, bool tag = false, int bx = 17,
                      bool etaFlag = false);

    /// constructor
    L1MuMBTrackSegPhi(const L1MuMBTrackSegLoc&,
                      int phi = 0, int phib = 0,
                      TSQuality quality = Null, bool tag = false, int bx = 17,
                      bool etaFlag = false);

    /// copy constructor
    L1MuMBTrackSegPhi(const L1MuMBTrackSegPhi&);

    /// destructor
    virtual ~L1MuMBTrackSegPhi();

    /// reset phi track segment
    void reset();

    /// return phi-value in global coordinates [0,2pi]
    double phiValue() const;

    /// return phib-value in global coordinates [0,2pi]
    double phibValue() const;

    /// return wheel
    inline int wheel() const { return m_location.wheel(); }

    /// return sector
    inline int sector() const { return m_location.sector(); }

    /// return station
    inline int station() const { return m_location.station(); }

    /// return location of phi track segment
    inline const L1MuMBTrackSegLoc& where() const{ return m_location; }

    /// return phi
    inline int phi() const { return m_phi; }

    /// return phib
    inline int phib() const { return m_phib; }

    /// return quality code
    inline int quality() const { return m_quality; }

    /// return tag (second TS tag)
    inline int tag() const { return m_tag; }

    /// return bunch crossing
    inline int bx() const { return m_bx; }

    /// return eta flag
    inline bool etaFlag() const { return m_etaFlag; }

    /// is it an empty phi track segment?
    inline bool empty() const { return m_quality == Null; }

    /// set eta flag
    inline void setEtaFlag(bool flag) { m_etaFlag = flag; }

    /// assignment operator
    L1MuMBTrackSegPhi& operator=(const L1MuMBTrackSegPhi&);

    /// equal operator
    bool operator==(const L1MuMBTrackSegPhi&) const;

    /// unequal operator
    bool operator!=(const L1MuMBTrackSegPhi&) const;

    /// overload output stream operator for phi track segment quality
    friend std::ostream& operator<<(std::ostream&, const TSQuality&);

    /// overload output stream operator for phi track segments
    friend std::ostream& operator<<(std::ostream&, const L1MuMBTrackSegPhi&);

  private:

    L1MuMBTrackSegLoc m_location;   // logical location of TS
    int               m_phi;        // 12 bits
    int               m_phib;       // 10 bits
    TSQuality         m_quality;    // 3 bits
    bool              m_tag;        // tag for second TS (of chamber)
    int               m_bx;         // bunch crossing identifier
    bool              m_etaFlag;    // eta flag (for overlap region)

};

#endif
