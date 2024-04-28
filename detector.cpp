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

void Detector::interact(CollisionEvent& col_event)
{
  tracker.interact(col_event);
  //calorimiter.interact(interacting_event);
  //muon_chamber.interact(interacting_event);
}

void Detector::see_detections()
{
  // Uses the information available to guess the particle.
  // Tracker
  if(tracker.detection_status()) std::cout<<"tracker detection!"<<std::endl;
  else std::cout<<"no tracker detection"<<std::endl;
}

void Detector::reset()
{
  tracker.reset();
  //calorimiter.reset();
  //muon_chamber.reset();
}