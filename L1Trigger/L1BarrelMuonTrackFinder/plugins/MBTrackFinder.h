//-------------------------------------------------
//
/**  \class MBTrackFinder
 *
 *   L1 MB Track Finder EDProducer
 *
 *
 *
 *   J. Troconiz              UAM Madrid
 */
//
//--------------------------------------------------
#ifndef MBTrackFinder_h
#define MBTrackFinder_h

#include <FWCore/Framework/interface/one/EDProducer.h>
#include <FWCore/ParameterSet/interface/ParameterSet.h>

#include <string>

class L1MuMBTFSetup;


class MBTrackFinder: public edm::one::EDProducer<edm::one::SharedResources> {
 public:
  /// Constructor
  MBTrackFinder(const edm::ParameterSet & pset);

  /// Destructor
  virtual ~MBTrackFinder();

  /// Produce digis out of raw data
  void produce(edm::Event & e, const edm::EventSetup& c);

 private:

  L1MuMBTFSetup* setup1;

};

#endif
