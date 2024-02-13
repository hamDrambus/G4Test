#include <geant4/PhotonHit.hh>

G4ThreadLocal G4Allocator<EnergyDepHit>* EnergyDepHitAllocator=0;

EnergyDepHit::EnergyDepHit()
  : energy_deposition(0.0 * eV)
{}

EnergyDepHit(double energy)
  : energy_deposition(energy)
{}

EnergyDepHit::~EnergyDepHit() {}

G4int EnergyDepHit::operator==(const EnergyDepHit& right) const
{
  return (this==&right) ? 1 : 0;
}

void EnergyDepHit::Draw()
{
  // G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  // if(pVVisManager) {
  //   G4Circle circle(_pos);
  //   circle.SetScreenSize(2.);
  //   circle.SetFillStyle(G4Circle::filled);
  //   G4Colour colour(1.,0.,0.);
  //   G4VisAttributes attribs(colour);
  //   circle.SetVisAttributes(attribs);
  //   circle.SetScreenDiameter(4.0);
  //   pVVisManager->Draw(circle);
  // }
}

void EnergyDepHit::Print(std::ostream &stream)
{
  stream << energy_deposition / eV;
  stream << std::endl;
}
