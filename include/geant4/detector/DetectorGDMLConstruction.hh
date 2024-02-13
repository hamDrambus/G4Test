#pragma once

#include <G4VUserDetectorConstruction.hh>
#include <G4GDMLParser.hh>

/// Detector construction that uses the geometry read from the GDML file
class DetectorGDMLConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorGDMLConstruction(const std::string &filename) {
      // See geant4-v.../examples/extended/persistency/gdml
      G4GDMLParser parser;
      // Uncomment the following if you wish to avoid names stripping
      // parser.SetStripFlag(false);
      parser.SetOverlapCheck(true);
      parser.Read(filename);
      world_volume = parser.GetWorldVolume();
      logic_scintillator = FindScintillator(parser, settings::general.sensor_volume_name);
      // TODO: there is a question on how to handle auxilary info
      // TODO: there is also an issue on how to handle optical surfaces
    }

    virtual G4VPhysicalVolume *Construct() {
      ConstructSDandField();
      return world_volume;
    }

    virtual void ConstructSDandField(void) override {
      DetectorSensor *theScintillator = new DetectorSensor("/detector/sensitiveDetector");
      G4SDManager::GetSDMpointer()->AddNewDetector(theScintillator);
      SetSensitiveDetector(logic_scintillator, theScintillator);
    }
  
  protected:
    G4LogicalVolume* FindScintillator(G4GDMLParser& parser, std::string phys_name) const {
      G4PhysicalVolumeStore* geometry_store = G4PhysicalVolumeStore::GetInstance();
      G4VPhysicalVolume* phys_vol = geometry_store->GetVolume(phys_name, false);
      // Can't return G4LogicalVolume from phys_vol because it is const.
      std::string logical_name = phys_vol->GetLogicalVolume()->GetName();
      return parser.GetVolume(logical_name);
    } 

  private:
    G4VPhysicalVolume *world_volume;
    G4LogicalVolume *logic_scintillator;
};

