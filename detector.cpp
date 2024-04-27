#include"detector.h"

void Detector::interact(Particle& interacting_particle)
{
  tracker.interact(interacting_particle);
  //calorimiter.interact(interacting_particle);
  //muon_chamber.interact(interacting_particle);
}