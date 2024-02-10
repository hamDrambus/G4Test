#pragma once

#include <G4WorkerRunManager.hh>
#include <G4MTRunManager.hh>
#include <G4ScoringManager.hh>

#include "Run.hh"

/*
*  This class is a subtitution of default G4WorkerRunManager so that Run class is informed when merging has finished
*  via calling Run->Merged(). It allows it to free the local data.
*/
class CleanerWorkerRunManager : public G4WorkerRunManager
{
public:
  CleanerWorkerRunManager();
 ~CleanerWorkerRunManager();

protected:
  virtual void MergePartialResults() override; // Only calls Run->Merged() function
};

