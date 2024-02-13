#include <geant4/generator/GenCs137.hh>

GenCs137::GenCs137() :
  VGeneratePrimaries(), fParticleGun(nullptr)
{
  fParticleGun = new G4ParticleGun(1);
  fParticleGun->SetParticleEnergy(0.0 * eV);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
}

GenCs137::~GenCs137()
{
  delete fParticleGun;
}

void GenCs137::GeneratePrimaries(G4Event* anEvent)
{
  SetupNavigator();
  if (fParticleGun->GetParticleDefinition() == G4Geantino::Geantino()) {  
    G4int Z = 55, A = 137;
    G4double ionCharge   = 0.*eplus;
    G4double excitEnergy = 0.*keV;
    
    G4ParticleDefinition* ion = G4IonTable::GetIonTable()->GetIon(Z, A, excitEnergy);
    fParticleGun->SetParticleDefinition(ion);
    fParticleGun->SetParticleCharge(ionCharge);
  }

  int ID = anEvent->GetEventID();
  G4long seed = GetAndFixSeed(); // Results may be reproduced by fixating seed to this value and copying the rest of parameters.
  G4ThreeVector pos = GenPosition(ID);
  fParticleGun->SetParticlePosition(pos);

  fParticleGun->GeneratePrimaryVertex(anEvent);
}

G4ThreeVector GenElectronsPatterns::GenPosition(int event_number) const
{
  // TODO: get radioactive volume parameters dynamically from the geometry.
  const double source_radius = 10 * mm;
  const double source_thickness = 1 * mm;
  const G4ThreeVector source_pos(0.0 * mm, 0.0 * mm, 0.0 * mm); // Source center.
  double phi = 2 * pi * G4UniformRand();
  double R = (settings::general.source_pattern==settings::GenerationPattern::UniformIsotropic) ?
              std::sqrt(G4UniformRand()) * source_radius :
              0.0 * mm;
  double x = R * std::cos(phi),
         y = R * std::sin(phi),
         z = (G4UniformRand() - 0.5) * source_thickness;
  return G4ThreeVector(x, y, z) + source_pos;
}


