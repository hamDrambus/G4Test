#include <geant4/PhysicsList.hh>

#include <G4SystemOfUnits.hh>
#include <G4UnitsTable.hh>

#include <G4EmStandardPhysics.hh>
#include <G4EmExtraPhysics.hh>
#include <G4EmParameters.hh>
#include <G4DecayPhysics.hh>
#include <G4NuclideTable.hh>
#include <G4RadioactiveDecayPhysics.hh>
#include <G4HadronElasticPhysics.hh>
#include <G4HadronPhysicsFTFP_BERT.hh>
#include <G4HadronInelasticQBBC.hh>
#include <G4HadronPhysicsINCLXX.hh>
#include <G4IonElasticPhysics.hh>
#include <G4IonPhysics.hh>
#include <G4IonINCLXXPhysics.hh>

// particles
#include <G4BosonConstructor.hh>
#include <G4LeptonConstructor.hh>
#include <G4MesonConstructor.hh>
#include <G4BosonConstructor.hh>
#include <G4BaryonConstructor.hh>
#include <G4IonConstructor.hh>
#include <G4ShortLivedConstructor.hh>

#include <KillProcess.hh>

LowGammaPhysicsList::LowGammaPhysicsList(G4int verbosity) : G4VModularPhysicsList()
{
  // see examples/extended/radioactivedecay
  // TODO: there is a lot optimzation potential here.
  // it would probably be more effective to enable particles
  // and processes by hand, but it will require accurate and long work.

  defaultCutValue = 0.01 * mm; 
	SetVerboseLevel(verbosity);

  // EM Physics
  // RegisterPhysics( new G4EmStandardPhysics(verbosity) );
  RegisterPhysics( new G4EmPenelopePhysics(verbosity) );
  // RegisterPhysics( new G4EmLivermorePhysics(verbosity) );

  // Synchroton Radiation & GN Physics
  G4EmExtraPhysics* gnuc = new G4EmExtraPhysics(verbosity);
  gnuc->ElectroNuclear(false);
  gnuc->MuonNuclear(false);
  RegisterPhysics(gnuc);

  // Ion Physics
  RegisterPhysics( new G4IonPhysics(verbosity));

  // Decays
  RegisterPhysics(new G4DecayPhysics(verbosity));

  // Radioactive decays
  RegisterPhysics(new G4RadioactiveDecayPhysics(verbosity));

  // Hadron Elastic scattering
  RegisterPhysics( new G4HadronElasticPhysics(verbosity) );
  
  // Hadron Inelastic physics
  RegisterPhysics( new G4HadronPhysicsFTFP_BERT(verbosity));
  ////RegisterPhysics( new G4HadronInelasticQBBC(verbosity));        
  ////RegisterPhysics( new G4HadronPhysicsINCLXX(verbosity));
  
  // Ion Elastic scattering
  RegisterPhysics( new G4IonElasticPhysics(verbosity));
      
  // Ion Inelastic physics
  RegisterPhysics( new G4IonPhysics(verbosity));
  ////RegisterPhysics( new G4IonINCLXXPhysics(verbosity));

  G4EmParameters::Instance()->SetAuger(true);
  G4EmParameters::Instance()->SetFluo(true);
  G4EmParameters::Instance()->SetPixe(true);

  G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(20*eV, 1*GeV);

  // Mandatory for G4NuclideTable
  // Half-life threshold must be set small or many short-lived isomers 
  // will not be assigned life times (default to 0)
  G4NuclideTable::GetInstance()->SetThresholdOfHalfLife(0.1*picosecond);
  G4NuclideTable::GetInstance()->SetLevelTolerance(1.0*eV);

  //read new PhotonEvaporation data set 
  G4DeexPrecoParameters* deex = 
    G4NuclearLevelData::GetInstance()->GetParameters();
  deex->SetCorrelatedGamma(false);
  deex->SetStoreAllLevels(true);
  deex->SetIsomerProduction(true);  
  deex->SetMaxLifeTime(G4NuclideTable::GetInstance()->GetThresholdOfHalfLife()
                /std::log(2.));

  // TODO: need to get G4RadioactiveDecay process somehow set only specific volume as radioactive:
  // G4RadioactiveDecay * radioactive_decay_proc = ...; // Find("RadioactiveDecay")?
  // radioactive_decay_proc->DeselectAllVolumes();
  // radioactive_decay_proc->SelectAVolume(const G4String aVolume);
}

void LowGammaPhysicsList::ConstructParticle(void)
{
  G4BosonConstructor  pBosonConstructor;
  pBosonConstructor.ConstructParticle();

  G4LeptonConstructor pLeptonConstructor;
  pLeptonConstructor.ConstructParticle();

  G4MesonConstructor pMesonConstructor;
  pMesonConstructor.ConstructParticle();

  G4BaryonConstructor pBaryonConstructor;
  pBaryonConstructor.ConstructParticle();

  G4IonConstructor pIonConstructor;
  pIonConstructor.ConstructParticle();

  G4ShortLivedConstructor pShortLivedConstructor;
  pShortLivedConstructor.ConstructParticle();  
}

void LowGammaPhysicsList::ConstructProcess(void) override
{
  G4VModularPhysicsList::ConstructProcess();
  G4ProcessManager* pManager = G4GenericIon()::GenericIon()->GetProcessManager();
  pManager->AddDiscreteProcess(new KillProcess_Betas());
}

void LowGammaPhysicsList::SetCuts(void)
{
  SetCutValue(0.1 * mm, "proton");
  SetCutValue(0.1 * mm, "e-");
  SetCutValue(0.1 * mm, "e+");
  SetCutValue(0.1 * mm, "gamma");      
}

LowGammaPhysicsList::~LowGammaPhysicsList()
{}
