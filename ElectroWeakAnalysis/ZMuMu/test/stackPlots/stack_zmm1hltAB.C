// stack macro
// Pasquale Noli
#include <sstream>
#include <string>
#include "stack_common.h"

void stack_zmm1hltAB() {


TCut cut_zGolden("zGoldenDau1Pt> 20 && zGoldenDau2Pt>20 && zGoldenDau1TrkIso< 3.0 && zGoldenDau1TrkIso < 3.0 && ( abs(zGoldenDau1Eta)>2.1 || abs(zGoldenDau2Eta)>2.1 ) && zGoldenDau1Chi2<10 && zGoldenDau2Chi2<10 && abs(zGoldenDau1dxyFromBS)<0.2 && abs(zGoldenDau2dxyFromBS)<0.2 && (zGoldenDau1NofStripHits + zGoldenDau1NofPixelHits)>=10 && (zGoldenDau2NofStripHits + zGoldenDau2NofPixelHits)>=10 && zGoldenDau1NofMuonHits>0 && zGoldenDau2NofMuonHits>0 && zGoldenDau1TrackerMuonBit==1 && zGoldenDau2TrackerMuonBit==1 && (zGoldenDau1HLTBit==0 || zGoldenDau2HLTBit==0) ");

 makePlots("zGoldenMass", cut_zGolden,  5, "zGolden1hltAB",  0.001, 200, 0 ,200, true);
}


