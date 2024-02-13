#include <geant4/generator/VGeneratePrimaries.hh>

VGeneratePrimaries::VGeneratePrimaries()
{
  mNavigator = nullptr;
}

VGeneratePrimaries::~VGeneratePrimaries()
{
  if (nullptr!=mNavigator)
    delete mNavigator;
}

void VGeneratePrimaries::SetupNavigator(void)
{
  G4Navigator* theNavigator = G4TransportationManager::GetTransportationManager()->GetNavigatorForTracking();
  G4VPhysicalVolume* world = theNavigator->GetWorldVolume();
  if (nullptr != mNavigator)
    delete mNavigator;
  mNavigator = new G4Navigator();
  mNavigator->SetWorldVolume(world);
}

G4long VGeneratePrimaries::GetAndFixSeed(void)
{
  G4long seed = G4Random::getTheEngine()->operator unsigned int();
  G4Random::setTheSeed(seed);
  return seed;
}

