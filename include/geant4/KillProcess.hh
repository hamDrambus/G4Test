#pragma once

#include <G4VDiscreteProcess.hh>
#include <G4ParallelWorldProcess.hh>
#include <G4TransportationManager.hh>
#include <G4Track.hh>
#include <G4OpticalPhoton.hh>
#include <G4ParticleTable.hh>

#include <GlobalSettings.hh>

//  This process is required only to kill stuck photons.
class KillProcess : public G4VDiscreteProcess
{
 public:
  explicit KillProcess(const G4String& processName = "KillProcess",
                               G4ProcessType type = fUserDefined);
  virtual ~KillProcess();

  virtual G4bool IsApplicable(const G4ParticleDefinition& aParticleType) override;

  virtual G4double GetMeanFreePath(const G4Track&, G4double, G4ForceCondition* condition) override;
  // Returns infinity; i. e. the process does not limit the step, but sets the
  // 'Forced' condition for the DoIt to be invoked at every step. However, only
  // at a boundary will any action be taken.

  G4VParticleChange* PostStepDoIt(const G4Track& aTrack, const G4Step& aStep) override;
  // This is the method implementing boundary processes.
private:
  KillProcess(const KillProcess& right) = delete;
  KillProcess& operator=(const KillProcess& right) = delete;
};

inline G4bool KillProcess::IsApplicable(const G4ParticleDefinition& aParticleType)
{
  return true;
}

inline G4double KillProcess::GetMeanFreePath(const G4Track&, G4double, G4ForceCondition* condition)
{
  *condition = Forced;
  return DBL_MAX;
}

// Kill daughter betas (electrons) from Cs137.
// This action cannot be done in G4UserTrackingAction because tracks are const there.
// The same goes for used G4UserSteppingAction
class KillProcess_Betas : public G4VDiscreteProcess
{
 public:
  explicit KillProcess_Betas(const G4String& processName = "KillProcess_Betas",
                               G4ProcessType type = fUserDefined);
  virtual ~KillProcess_Betas();

  virtual G4bool IsApplicable(const G4ParticleDefinition& aParticleType) override;

  // Returns infinity; i. e. the process does not limit the step
  virtual G4double GetMeanFreePath(const G4Track&, G4double, G4ForceCondition* condition) override;

  G4VParticleChange* AtRestDoIt(const G4Track& aTrack, const G4Step& aStep) override;
private:
  KillProcess(const KillProcess& right) = delete;
  KillProcess& operator=(const KillProcess& right) = delete;
};

inline G4bool KillProcess_Betas::IsApplicable(const G4ParticleDefinition& aParticleType)
{
  return aParticleType->GetAtomicNumber() > 0 && aParticleType->GetAtomicMass() > 0;
}

inline G4double KillProcess_Betas::GetMeanFreePath(const G4Track&, G4double, G4ForceCondition* condition)
{
  return DBL_MAX;
}

