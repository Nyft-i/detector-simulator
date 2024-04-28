#include<iostream>
#include<memory>

#include"detector.h"

// Constructors
// Default

// Parameterised
Detector::Detector(int con_percent_chance)
{
  tracker = std::make_shared<Tracker>(con_percent_chance);
  //calorimiter = Calorimiter();
  //muon_chamber = MuonChamber();
}

// Copy
Detector::Detector(const Detector& copy_from)
{
  tracker = std::make_shared<Tracker>(*copy_from.tracker);
  //calorimiter = copy_from.calorimiter;
  //muon_chamber = copy_from.muon_chamber;
}

// Move
Detector::Detector(Detector&& move_from)
{
  tracker = std::move(move_from.tracker);
  //calorimiter = std::move(move_from.calorimiter);
  //muon_chamber = std::move(move_from.muon_chamber);

  // Set move_from to 0.
  tracker = nullptr;
  //calorimiter = nullptr;
  //muon_chamber = nullptr;
}

// Destructor

// Assignment
// Copy
Detector& Detector::operator=(const Detector& copy_from)
{
  // Self assignment
  if(this == &copy_from) return *this;

  tracker = std::make_shared<Tracker>(*copy_from.tracker);
  //calorimiter = copy_from.calorimiter;
  //muon_chamber = copy_from.muon_chamber;
  return *this;
}

// Move
Detector& Detector::operator=(Detector&& move_from)
{
  // Self assignment
  if(this == &move_from) return *this;

  tracker = std::move(move_from.tracker);
  //calorimiter = std::move(move_from.calorimiter);
  //muon_chamber = std::move(move_from.muon_chamber);

  // Set move_from to 0.
  tracker = nullptr;
  //calorimiter = nullptr;
  //muon_chamber = nullptr;
  return *this;
}

// Functionality
void Detector::interact(Particle& interacting_particle)
{
  tracker->interact(interacting_particle);
  //calorimiter.interact(interacting_particle);
  //muon_chamber.interact(interacting_particle);
}

void Detector::interact(CollisionEvent& col_event)
{
  tracker->interact(col_event);
  //calorimiter.interact(interacting_event);
  //muon_chamber.interact(interacting_event);
}

void Detector::see_detections()
{
  // Uses the information available to guess the particle.
  // Tracker
  if(tracker->detection_status()) std::cout<<"tracker detection!"<<std::endl;
  else std::cout<<"no tracker detection"<<std::endl;
}

void Detector::reset()
{
  tracker->reset();
  //calorimiter.reset();
  //muon_chamber.reset();
}