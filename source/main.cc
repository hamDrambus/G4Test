#include <time.h>
#include <iostream>
#include <filesystem>
#include <G4RunManager.hh>
#include <G4MTRunManager.hh>
#include <G4UImanager.hh>
#include <G4UIterminal.hh>

#ifdef G4VIS_USE
#include <G4VisExecutive.hh>
#endif

#include <GlobalSettings.hh>
#include <Randomize.hh>
#include <geant4/UserInitialization.hh>


int main(int argc, char** argv)
{
  // TODO: inputs handling with boost
  std::string settings_fname;
  if (argc != 1) {
    if (argc>2)
      std::cout << "Warning! Only single parameter (settings filename) is used." << std::endl;
    settings_fname = argv[1];
  } else {
    std::cout << "Using default settings file \"settings.xml\"" << std::endl;
    settings_fname = "settings.xml";
  }
  // Initialize detector and run parameters
  if (!settings::Initialize(settings_fname)) {
    std::cerr<<"Failed to initialize globals."<<std::endl;
    return -1;
  }
  // Choose the Random engine
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  // Seed the random number generator manually
  G4Random::setTheSeed(settings::general.initial_seed);

  // Construct the default run manager
  G4MTRunManager *runManager = new G4MTRunManager;
  // Changed standard approach a little so that everything for
  // run manager is set up either in UserInitialization constructor or its overloaded methods.
  UserInitialization* userInitialization = new UserInitialization(runManager);

  // Initialize G4 kernel
  runManager->Initialize();
  gData.Initialize();
  // Visualization manager

  G4VisManager* visManager = nullptr;
  if (settings::general.do_view) {
    visManager = new G4VisExecutive;
    visManager->SetVerboseLevel(0);
    visManager->Initialize();
  }

  // Get the pointer to the User Interface manager
  G4UImanager* UI = G4UImanager::GetUIpointer();
  UI->SetVerboseLevel(0);
  UI->ApplyCommand("/run/verbose 0");
  UI->ApplyCommand("/event/verbose 0");
  UI->ApplyCommand("/tracking/verbose 0");
  UI->ApplyCommand("/tracking/storeTrajectory 2");
  if (settings::general.do_view) {
    UI->ApplyCommand("/control/execute vis.mac");
  }

  runManager->BeamOn(settings::general.N_events);

  if (settings::general.do_view) {
    UI->ApplyCommand("vis/viewer/update");
    std::filesystem::path old_fname("g4_00.wrl");
    std::filesystem::path new_fname(settings::general.output_folder + "g4_00.wrl");
    std::filesystem::rename(old_fname, new_fname);
  }

  if (visManager)
    delete visManager;
  delete runManager;
  return 0;
}
