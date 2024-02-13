#pragma once

#include <G4VHit.hh>
#include <G4THitsCollection.hh>
#include <G4Allocator.hh>
#include <G4ThreeVector.hh>
#include <G4UnitsTable.hh>
#include <G4VVisManager.hh>
#include <G4Circle.hh>
#include <G4Colour.hh>
#include <G4VisAttributes.hh>

using namespace CLHEP;

class EnergyDepHit : public G4VHit
{
  public:
    EnergyDepHit();
    EnergyDepHit(double energy);
    virtual ~EnergyDepHit();
    G4int operator==(const EnergyDepHit&) const;
    void Draw();
    void Print(std::ostream &stream = G4cout);

    void* operator new(size_t);
    void operator delete(void *hit);

  public:
    G4double energy_deposition;
};

typedef G4THitsCollection<EnergyDepHit> EnergyDepHitCollection;
extern G4ThreadLocal G4Allocator<EnergyDepHit>* EnergyDepHitAllocator;

inline void* EnergyDepHit::operator new(size_t)
{
  if(!EnergyDepHitAllocator)
    EnergyDepHitAllocator = new G4Allocator<EnergyDepHit>;
  return (void *) EnergyDepHitAllocator->MallocSingle();
}

inline void EnergyDepHit::operator delete(void *hit)
{
  EnergyDepHitAllocator->FreeSingle((EnergyDepHit*) hit);
}

