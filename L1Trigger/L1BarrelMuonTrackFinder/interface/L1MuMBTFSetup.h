//-------------------------------------------------
//
/**  \class L1MuMBTFSetup
 *
 *   Setup the L1 barrel Muon Trigger Track Finder
 *
 *
 *
 *   N. Neumeister            CERN EP
 */
//
//--------------------------------------------------
#ifndef L1MUMB_TF_SETUP_H
#define L1MUMB_TF_SETUP_H

//---------------
// C++ Headers --
//---------------

//----------------------
// Base Class Headers --
//----------------------


//------------------------------------
// Collaborating Class Declarations --
//------------------------------------

#include <FWCore/ParameterSet/interface/ParameterSet.h>
#include <FWCore/Framework/interface/ConsumesCollector.h>
class L1MuMBTrackFinder;

//              ---------------------
//              -- Class Interface --
//              ---------------------

class L1MuMBTFSetup {

  public:

    /// constructor
    L1MuMBTFSetup(const edm::ParameterSet & ps,edm::ConsumesCollector && ix);

    /// destructor
    virtual ~L1MuMBTFSetup();

    /// perform action per run

    /// return the main trigger object
    L1MuMBTrackFinder* TrackFinder() { return m_tf; }

  private:

    L1MuMBTrackFinder* m_tf;

};

#endif
