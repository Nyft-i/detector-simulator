#include<iostream>

#include"detector.h"

// Constructors
// Default

// Parameterised
Detector::Detector(int con_percent_chance)
{
  tracker = Tracker(con_percent_chance);
  //calorimiter = Calorimiter();
  //muon_chamber = MuonChamber();
}


void Detector::interact(Particle& interacting_particle)
{
  tracker.interact(interacting_particle);
  //calorimiter.interact(interacting_particle);
  //muon_chamber.interact(interacting_particle);
}

Particle Detector::guess_particle()
{
  // Uses the information available to guess the particle.
  // Tracker
  if(tracker.get_num_hits()>=2)
  {
    std::cout<<"tracker detection!"<<std::endl;
  } // Particle can be a charged particle.
}