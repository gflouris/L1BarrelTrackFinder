#include <DataFormats/L1MBTrackFinder/interface/L1MuMBChambPhDigi.h>
#include <DataFormats/L1MBTrackFinder/interface/L1MuMBChambThDigi.h>
#include <DataFormats/L1MBTrackFinder/interface/L1MuMBTrackCand.h>
#include <DataFormats/L1MBTrackFinder/interface/L1MuMBChambPhContainer.h>
#include <DataFormats/L1MBTrackFinder/interface/L1MuMBChambThContainer.h>
#include <DataFormats/L1MBTrackFinder/interface/L1MuMBTrackContainer.h>
#include <DataFormats/Common/interface/Wrapper.h>

namespace DataFormats_L1MBTrackFinder {
  struct dictionary {
    L1MuMBChambPhDigi ph_S;
    L1MuMBChambThDigi th_S;
    L1MuMBTrackCand   tr_S;

    std::vector<L1MuMBChambPhDigi> ph_V;
    std::vector<L1MuMBChambThDigi> th_V;
    std::vector<L1MuMBTrackCand>   tr_V;

    L1MuMBChambPhContainer ph_K;
    L1MuMBChambThContainer th_K;
    L1MuMBTrackContainer   tr_K;

    edm::Wrapper<L1MuMBChambPhContainer> ph_W;
    edm::Wrapper<L1MuMBChambThContainer> th_W;
    edm::Wrapper<L1MuMBTrackContainer>   tr_W;
  };
}
