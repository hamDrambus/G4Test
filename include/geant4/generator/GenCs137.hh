#pragma once

#include <vector>

#include <G4Event.hh>
#include <G4ParticleTable.hh>
#include <G4ParticleDefinition.hh>
#include <globals.hh>
#include <G4SystemOfUnits.hh>
#include <Randomize.hh>
#include <G4RandomTools.hh>
#include <G4Navigator.hh>
#include <G4TransportationManager.hh>
#include "GlobalSettings.hh"
#include "VGeneratePrimaries.hh"

class GenCs137 : public VGeneratePrimaries
{
public:

  GenCs137();
  ~GenCs137();

public:
  virtual void GeneratePrimaries(G4Event* anEvent) override;
  G4ParticleGun* GetParticleGun() {return fParticleGun;};

protected:
  G4ParticleGun* fParticleGun; //pointer a to G4 service class
};
