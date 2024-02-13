#include <geant4/KillProcess.hh>

KillProcess::KillProcess(const G4String& processName, G4ProcessType type)
  : G4VDiscreteProcess(processName, type)
{}

KillProcess::~KillProcess() {}

G4VParticleChange* KillProcess::PostStepDoIt(const G4Track& aTrack, const G4Step& aStep)
{
  aParticleChange.Initialize(aTrack);
  if(aTrack.GetDynamicParticle()->GetDefinition() == G4OpticalPhoton::OpticalPhoton()) {
    if(aTrack.GetLocalTime() > gPars::general.photon_max_time) {
      aParticleChange.ProposeTrackStatus(fStopAndKill);
      aParticleChange.ProposeLocalEnergyDeposit(0.0);
      G4VDiscreteProcess::PostStepDoIt(aTrack, aStep);
    }
  }
  return G4VDiscreteProcess::PostStepDoIt(aTrack, aStep);
}

KillProcess_Betas::KillProcess_Betas(const G4String& processName, G4ProcessType type)
  : G4VDiscreteProcess(processName, type)
{}

KillProcess_Betas::~KillProcess_Betas() {}

G4VParticleChange* KillProcess_Betas::AtRestDoIt(const G4Track& aTrack, const G4Step& aStep)
{
  aParticleChange.Initialize(aTrack);
  if (aParticleChange.GetTrackStatus() == fStopAndKill || aParticleChange.GetTrackStatus() == fStopButAlive) {
    for (int i = 0; i < aParticleChange.GetNumberOfSecondaries(); ++i) {
      G4Track* decay_track = aParticleChange.GetSecondary(i);

      G4ParticleDefinition* decay_particle = decay_track->GetDynamicParticle()->GetPrimaryParticle()->GetParticleDefinition();
      G4ParticleDefinition* electron = G4ParticleTable::GetParticleTable()->FindParticle("electron");
      // G4ParticleDefinition* positron = G4ParticleTable::GetParticleTable()->FindParticle("positron");
      if (decay_particle == electron) {
        // TODO: it is not clear whether modifing secondaries this way works.
        decay_track.SetTrackStatus(fStopAndKill);
      }
    }
  }
  return G4VDiscreteProcess::PostStepDoIt(aTrack, aStep);
}
