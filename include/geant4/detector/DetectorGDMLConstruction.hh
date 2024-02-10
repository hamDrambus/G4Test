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
      fWorld = parser.GetWorldVolume();

      // TODO: there is a question on how to handle auxilary info
      // TODO: there is also an issue on how to handle optical surfaces
    }

    virtual G4VPhysicalVolume *Construct() {
      return fWorld;
    }

  private:
    G4VPhysicalVolume *fWorld;
};

