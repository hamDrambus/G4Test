#pragma once

#include <iostream>

#include <G4SystemOfUnits.hh>
#include <globals.hh>

#include <G4UnitsTable.hh>
#include <G4LossTableManager.hh>
#include <G4Region.hh>
#include <G4RegionStore.hh>

#include <G4VModularPhysicsList.hh>
#include <G4OpticalPhoton.hh>
#include <G4OpAbsorption.hh>
#include <G4OpRayleigh.hh>
#include <G4OpBoundaryProcess.hh>
#include <G4OpWLS.hh>
#include <G4ProcessManager.hh>

class LowGammaPhysicsList: public G4VModularPhysicsList
{
public:
  LowGammaPhysicsList(G4int verbosity = 0);
  virtual ~LowGammaPhysicsList() = default;

  LowGammaPhysicsList(const LowGammaPhysicsList &) = delete;
  LowGammaPhysicsList & operator=(const LowGammaPhysicsList &) = delete;
};
