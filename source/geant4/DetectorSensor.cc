#include <geant4/DetectorSensor.hh>

const std::string DetectorSensor::HitCollectionName = "EnergyDepHitCollection";

DetectorSensor::DetectorSensor(G4String name) :
	G4VSensitiveDetector(name)
{
	collectionName.insert(HitCollectionName);
}

DetectorSensor::~DetectorSensor()
{}

void DetectorSensor::Initialize(G4HCofThisEvent* HCE)
{
	hitCollection = new PhotonHitCollection(GetName(), collectionName[0]);
	static G4int HCID = -1;
	if (HCID < 0)
		HCID = GetCollectionID(0);
	HCE->AddHitsCollection(HCID, hitCollection);
}

G4bool DetectorSensor::ProcessHits(G4Step* aStep, G4TouchableHistory* touchHist)
{
	G4VPhysicalVolume* post_vol = aStep->GetPostStepPoint()->GetTouchable()->GetVolume();
	G4VPhysicalVolume* pre_vol = aStep->GetPreStepPoint()->GetTouchable()->GetVolume();
	if (post_vol == pre_vol && nullptr != post_vol && post_vol->GetName() == settings::general.sensor_volume_name) {
		double energy_deposition = aStep->GetTotalEnergyDeposit();
		if (energy_deposition > 0.0) {
			EnergyDepHit *hit = new EnergyDepHit(energy_deposition);
			hitCollection->insert(hit);
		}
	}
	return true;
}


void DetectorSensor::EndOfEvent(G4HCofThisEvent* HCE)
{}
