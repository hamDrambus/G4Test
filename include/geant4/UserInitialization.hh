#pragma once

#include <G4VUserActionInitialization.hh>
#include <G4UserWorkerInitialization.hh>
#include <G4UserWorkerThreadInitialization.hh>
#include <Randomize.hh>
#include <G4MTRunManager.hh>

#include <GlobalSettings.hh>
#include "RunAction.hh"
#include "CleanerWorkerRunManager.hh"
#include "PhysicsList.hh"
#include "detector/DetectorGDMLConstruction.hh"
#include "generator/GenCs137.hh"

class UserInitialization : public G4VUserActionInitialization
{
public:
  UserInitialization(G4RunManager *run_manager);
  ~UserInitialization();

  void BuildForMaster() const override;
  void Build() const override;
protected:
  G4RunManager *runManager;
};

class UserWorkerThread : public G4UserWorkerThreadInitialization
{
public:
  UserWorkerThread();
  virtual G4WorkerRunManager* CreateWorkerRunManager() const override;
};

