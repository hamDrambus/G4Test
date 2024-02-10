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
#include <G4VUserPrimaryGeneratorAction.hh>

#include "utilities/PolynomialFit.hh"
#include "geant4/PhotonHit.hh"
#include "PrimaryGenerator.hh"

/*
 *  Helper class. Defining useful functions which are reused in concrete generators
 */
class VGeneratePrimaries : public G4VUserPrimaryGeneratorAction
{
public:
  VGeneratePrimaries();
  ~VGeneratePrimaries();

public:
  virtual void GeneratePrimaries(G4Event* anEvent) = 0;

protected:
  void SetupNavigator(void);
  G4long GetAndFixSeed(void);

  G4Navigator* mNavigator; // Separate from tracking navigator and is used to locate points before particle generation.
};

