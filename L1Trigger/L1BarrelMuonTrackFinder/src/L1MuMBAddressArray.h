//-------------------------------------------------
//
/**  \class L1MuMBAddressArray
 *
 *   Array of relative addresses
 *
 *   Array of 4 relative addresses (one per station);<BR>
 *   the valid range of a relative address is 0 - 11
 *   thus a relative address is a 4 bit word;<BR>
 *   address = 15 indicates a negative extrapolation result
 *
 *   \verbatim
 *         ------------------------
 *         |   4    5  |   6   7  |
 *      P  ------------+-----------
 *      H  |   0    1  |   2   3  |
 *      I  ------------+-----------
 *         |   8    9  |  10  11  |
 *         ------------+-----------
 *            my Wheel  next Wheel
 *   \endverbatim
 *
 *
 *
 *   N. Neumeister            CERN EP
 */
//
//--------------------------------------------------
#ifndef L1MUMB_ADDRESS_ARRAY_H
#define L1MUMB_ADDRESS_ARRAY_H

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

class L1MuMBAddressArray {

  public:

    /// default constructor
    L1MuMBAddressArray();

    /// copy constructor
    L1MuMBAddressArray(const L1MuMBAddressArray&);

    /// destructor
    virtual ~L1MuMBAddressArray();

    /// assignment operator
    L1MuMBAddressArray& operator=(const L1MuMBAddressArray&);

    /// equal operator
    bool operator==(const L1MuMBAddressArray&) const;
   
    /// unequal operator
    bool operator!=(const L1MuMBAddressArray&) const;

    /// reset address array
    void reset();

    /// set address of a given station [1-4]
    void setStation(int stat, int adr);
    
    /// set addresses of all four stations
    void setStations(int adr1, int adr2, int adr3, int adr4);

    /// get address of a given station [1-4]
    inline unsigned short station(int stat) const { return m_station[stat-1]; } 

    /// get track address code (for eta track finder)
    int trackAddressCode() const;

    /// get converted Addresses
    L1MuMBAddressArray converted() const;

    /// output stream operator for address array
    friend std::ostream& operator<<(std::ostream&, const L1MuMBAddressArray&);

    /// convert address to corresponding VHDL addresse
    static unsigned short int convert(unsigned short int adr);
    
    /// is it a same wheel address?
    static bool sameWheel(unsigned short int adr);
    
    /// is it a next wheel address?
    static bool nextWheel(unsigned short int adr);

  private:
  
    unsigned short int m_station[4];

};

#endif
