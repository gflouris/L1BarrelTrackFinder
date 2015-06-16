//-------------------------------------------------
//
/**  \class L1MuMBDataBuffer
 *
 *   Data Buffer:
 *
 *   The Data Buffer stores track 
 *   segment data during the            
 *   execution of the track assembler
 *
 *
 *
 *   N. Neumeister            CERN EP
 */
//
//--------------------------------------------------
#ifndef L1MUMB_DATA_BUFFER_H
#define L1MUMB_DATA_BUFFER_H

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

class L1MuMBSectorProcessor;
class L1MuMBTrackSegPhi;

//              ---------------------
//              -- Class Interface --
//              ---------------------

class L1MuMBDataBuffer {

  public:

    /// container to store phi track segments 
    typedef std::vector<L1MuMBTrackSegPhi*> TSPhivector;

    /// constructor
    L1MuMBDataBuffer(const L1MuMBSectorProcessor& );

    /// destructor
    virtual ~L1MuMBDataBuffer();
    
    /// clear Data Buffer
    void reset(); 

    /// get all track segments from the buffer
    const TSPhivector& getTSphi() const { return *m_tsphi; }

    /// get phi track segment of a given station from the buffer
    const L1MuMBTrackSegPhi* getTSphi(int station, int address) const;
    
    /// add new phi track segment to the Data Buffer
    void addTSphi(int adr, const L1MuMBTrackSegPhi&);
    
    /// print all phi track segments which are in the buffer
    void printTSphi() const;
    
    /// return number of non-empty phi track segments
    int numberTSphi() const;
    
  private:

    const L1MuMBSectorProcessor& m_sp;
    TSPhivector*                 m_tsphi;
   
};
  
#endif
