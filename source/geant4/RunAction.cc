#include <geant4/RunAction.hh>

RunAction::RunAction()
{}

RunAction::~RunAction()
{}

G4Run* RunAction::GenerateRun()
{
  return new Run;
}

void RunAction::BeginOfRunAction(const G4Run* aRun)
{
  const Run* run = static_cast<const Run*>(aRun);
  G4cout << "### Run " << run->GetRunID() << " started." << G4endl;
  // Inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
}

void RunAction::EndOfRunAction(const G4Run* aRun)
{
  const Run* run = static_cast<const Run*>(aRun);
  if (IsMaster()) {
    G4cout << G4endl
        << "-----------------Writing results to files--------------------" << G4endl;
    run->WriteResultsToFile(settings::general.output_folder + settings::general.energy_deposition_filename);
    G4cout << G4endl
    << "--------------------End of Global Run-----------------------"
    << "  #" << run->GetRunID() << " Event#: "<< run->GetNumberOfEvent() << G4endl;
  }
}
