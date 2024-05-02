#include<iostream>
#include<memory>

#include"detector.h"
#include"tracker.h"
#include"calorimeter.h"

// Constructors
// Default

// Parameterised
Detector::Detector(int con_percent_chance)
{
  tracker = std::make_unique<Tracker>(con_percent_chance);
  calorimeter = std::make_unique<Calorimeter>();
  //muon_chamber = MuonChamber();
}

// Copy
Detector::Detector(const Detector& copy_from)
{
  tracker = std::make_unique<Tracker>(*copy_from.tracker);
  calorimeter = std::make_unique<Calorimeter>(*copy_from.calorimeter);  
  //muon_chamber = copy_from.muon_chamber;
}

// Move
Detector::Detector(Detector&& move_from)
{
  tracker = std::move(move_from.tracker);
  calorimeter = std::move(move_from.calorimeter);
  //muon_chamber = std::move(move_from.muon_chamber);

  // Set move_from to 0.
  tracker = nullptr;
  calorimeter = nullptr;
  //muon_chamber = nullptr;
}

// Destructor

// Assignment
// Copy
Detector& Detector::operator=(const Detector& copy_from)
{
  // Self assignment
  if(this == &copy_from) return *this;

  tracker = std::make_unique<Tracker>(*copy_from.tracker);
  calorimeter = std::make_unique<Calorimeter>(*copy_from.calorimeter);
  //muon_chamber = copy_from.muon_chamber;
  return *this;
}

// Move
Detector& Detector::operator=(Detector&& move_from)
{
  // Self assignment
  if(this == &move_from) return *this;

  tracker = std::move(move_from.tracker);
  calorimeter = std::move(move_from.calorimeter);
  //muon_chamber = std::move(move_from.muon_chamber);

  // Set move_from to 0.
  tracker = nullptr;
  calorimeter = nullptr;
  //muon_chamber = nullptr;
  return *this;
}

// Functionality
void Detector::interact(Particle& interacting_particle)
{
  tracker->interact(interacting_particle);
  calorimeter->interact(interacting_particle);
  //muon_chamber.interact(interacting_particle);
}

void Detector::interact(CollisionEvent& col_event)
{
  tracker->SubDetector::interact(col_event); // Overloads hidden by default in c++, stupid rule IMO. see "hiding rule".
  calorimeter->SubDetector::interact(col_event);
  //muon_chamber.interact(interacting_event);
}

void Detector::see_detections()
{
  // Uses the information available to guess the particle.
  // Tracker
  if(tracker->detection_status()) std::cout<<"tracker detection!"<<std::endl;
  else std::cout<<"no tracker detection"<<std::endl;

  // Calorimeter
  calorimeter->print();
}

void Detector::reset()
{
  tracker->reset();
  calorimeter->reset();
  //muon_chamber.reset();
}