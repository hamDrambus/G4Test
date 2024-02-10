#include <geant4/PhysicsList.hh>

#include <geant4/G4EmStandardPhysics.hh>
#include <geant4/G4EmPenelopePhysics.hh>
#include <geant4/G4EmLivermorePhysics.hh>

LowGammaPhysicsList::LowGammaPhysicsList(G4int verbosity) : G4VModularPhysicsList()
{
  defaultCutValue = 0.01 * mm; 
	SetVerboseLevel(verbosity);

  // EM Physics
  // RegisterPhysics( new G4EmStandardPhysics(ver) );
  RegisterPhysics( new G4EmPenelopePhysics(ver) );
  // RegisterPhysics( new G4EmLivermorePhysics(ver) );

  // Synchroton Radiation & GN Physics
  RegisterPhysics( new G4EmExtraPhysics(ver) );

  // Ion Physics
  RegisterPhysics( new G4IonPhysics(ver));

  // Decays
  RegisterPhysics( new G4DecayPhysics(ver) );

  G4EmParameters::Instance()->SetAuger(true);
  G4EmParameters::Instance()->SetFluo(true);
  G4EmParameters::Instance()->SetPixe(true);

  G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(20*eV, 1*GeV);
}


LowGammaPhysicsList::~LowGammaPhysicsList()
{}
