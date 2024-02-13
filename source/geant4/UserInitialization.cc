#include <geant4/UserInitialization.hh>

UserInitialization::UserInitialization(G4RunManager *run_manager) :
  runManager(run_manager)
{
  if (nullptr != runManager) {
    runManager->SetNumberOfEventsToBeStored(0);
    runManager->SetNumberOfThreads(settings::general.thread_number);
    // Create detector depending on settings given
    VDetectorConstruction* detector = new DetectorGDMLConstruction(settings::general.data_path + settings::general.geometry_fname);
    
    // G4Exception("UserInitialization::UserInitialization: ",
    //     "InvalidSetup", FatalException, "Unimplemented detector type is used.");
    // return;
    
    // Set mandatory initialization classes
    runManager->SetUserInitialization(detector);
    runManager->SetUserInitialization(new PhysicsList);
    runManager->SetUserInitialization(new UserWorkerThread); // Only responsible for clearing merged runs.
    runManager->SetUserInitialization(this);
  }
}

UserInitialization::~UserInitialization()
{}

void UserInitialization::BuildForMaster() const
{
  SetUserAction(new RunAction);
}

void UserInitialization::Build() const
{
  // Create generator depending on settings given
  VGeneratePrimaries* generator = new GenCs137();
  SetUserAction(new RunAction);
  SetUserAction(generator);
  // SetUserAction(new SteppingAction);
  // SetUserAction(new TrackingAction);
}

UserWorkerThread::UserWorkerThread()
{}

G4WorkerRunManager* UserWorkerThread::CreateWorkerRunManager() const
{
  return new CleanerWorkerRunManager;
}
