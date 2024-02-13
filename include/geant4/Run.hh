#pragma once

#include <boost/histogram.hpp>

#include <G4Run.hh>
#include <globals.hh>
#include <G4StatAnalysis.hh>
#include <G4RunManager.hh>
#include <G4Event.hh>

#include <G4SDManager.hh>
#include <G4HCofThisEvent.hh>
#include <G4THitsMap.hh>
#include <G4SystemOfUnits.hh>

#include <GlobalSettings.hh>
#include "EnergyDepHit.hh"
#include "DetectorSensor.hh"

using namespace boost::histogram;

class Run : public G4Run
{
  public:
    Run();
    ~Run() override;
    virtual void RecordEvent(const G4Event*) override;
    virtual void Merge(const G4Run*) override; // Note that merged info is still in storage until local run destruction
    virtual void Merged(void);
    void WriteResultsToFile(std::string filename);
  protected:
    histogram<axis::regular<>, default_storage> energy_hist;
    int hit_collection_ID;
};



