#include <filesystem>

#include <geant4/Run.hh>
#include <geant4/generator/GenNBrS_InTHGEM.hh>

using namespace boost::histogram;

Run::Run() : hit_collection_ID(-1)
{
  energy_hist = make_histogram(axis::regular<>(700, 0.0, 700.0));
}

Run::~Run()
{}

void Run::RecordEvent(const G4Event* event)
{
  if (hit_collection_ID < 0 ) {
    G4HCtable* HCtable = G4SDManager::GetSDMpointer()->GetHCtable();
    if (HCtable) // Not calling G4SDManager::GetCollectionID because this approach is quiet when there is no collection
      hit_collection_ID = HCtable->GetCollectionID(DetectorSensor::HitCollectionName);
  }

  const VGeneratePrimaries* generator =
      static_cast<const VGeneratePrimaries*>(G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
  if (!generator) {
    std::cerr << __PRETTY_FUNCTION__ << ": Error: No primary generator found.\n"
              <<"\tCan't gather run results and statistics." << std::endl;
    return G4Run::RecordEvent(event);
  }

  G4HCofThisEvent* HCE = event->GetHCofThisEvent();
  if(!HCE || hit_collection_ID < 0)
     return G4Run::RecordEvent(event);
  G4VHitsCollection* coll = HCE->GetHC(hit_collection_ID);
  if (!coll)
    return G4Run::RecordEvent(event);
  EnergyDepHitCollection* hit_collection = static_cast<EnergyDepHitCollection*>(coll);
  if (!hit_collection)
    return G4Run::RecordEvent(event);
  double total_energy = 0.0 * eV;
  for (std::size_t i = 0, i_end_ = hit_collection->GetSize(); i!=i_end_; ++i) {
    EnergyDepHit* hit = static_cast<EnergyDepHit*>(hit_collection->GetHit(i));
    if (hit) {
      total_energy += hit->energy_deposition;
    }
  }
  energy_hist(total_energy);
  return G4Run::RecordEvent(event);
}

void Run::Merge(const G4Run* aRun)
{
  const Run* localRun = static_cast<const Run*>(aRun);
  energy_hist += localRun->energy_hist;
  G4Run::Merge(aRun);
}

void Run::Merged()
{
  energy_hist.reset();
}

void Run::WriteResultsToFile(std::string filename)
{
  std::filesystem::create_directories(std::filesystem::path(filename).parent_path());
  std::ofstream str(filename, std::ios_base::ate|std::ios_base::out);
  if (!str.is_open()) {
    std::cerr << __PRETTY_FUNCTION__ << ": Error: Failed to open file\n"
              <<"\t\""<<filename<<"\""<<std::endl;
    return;
  }
  for (auto&& x : indexed(energy_hist)) {
    str<< *x <<"\n";
  }
}
