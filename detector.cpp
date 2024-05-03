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
  muon_detector = std::make_unique<MuonDetector>();

  current_col = nullptr;
  col_elem = 0;
}

// Copy
Detector::Detector(const Detector& copy_from)
{
  tracker = std::make_unique<Tracker>(*copy_from.tracker);
  calorimeter = std::make_unique<Calorimeter>(*copy_from.calorimeter);  
  muon_detector = std::make_unique<MuonDetector>(*copy_from.muon_detector);

  current_col = std::make_unique<CollisionEvent>(*copy_from.current_col);
  col_elem = copy_from.col_elem;

  current_col = nullptr;
  col_elem = 0;
}

// Move
Detector::Detector(Detector&& move_from)
{
  tracker = std::move(move_from.tracker);
  calorimeter = std::move(move_from.calorimeter);
  muon_detector = std::move(move_from.muon_detector);

  current_col = std::move(move_from.current_col);
  col_elem = move_from.col_elem;

  // Set move_from to 0.
  tracker = nullptr;
  calorimeter = nullptr;
  muon_detector = nullptr;
  current_col = nullptr;
  col_elem = 0;
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
  muon_detector = std::make_unique<MuonDetector>(*copy_from.muon_detector);
  
  current_col = std::make_unique<CollisionEvent>(*copy_from.current_col);
  col_elem = copy_from.col_elem;

  return *this;
}

// Move
Detector& Detector::operator=(Detector&& move_from)
{
  // Self assignment
  if(this == &move_from) return *this;

  tracker = std::move(move_from.tracker);
  calorimeter = std::move(move_from.calorimeter);
  muon_detector = std::move(move_from.muon_detector);

  current_col = std::move(move_from.current_col);
  col_elem = move_from.col_elem;

  // Set move_from to 0.
  tracker = nullptr;
  calorimeter = nullptr;
  muon_detector = nullptr;
  current_col = nullptr;
  col_elem = 0;

  return *this;
}

// Functionality
void Detector::interact(Particle& interacting_particle)
{
  reset();
  tracker->interact(interacting_particle);
  calorimeter->interact(interacting_particle);
  muon_detector->interact(interacting_particle);
}

void Detector::start_collision(unique_ptr<CollisionEvent> p_col_event)
{
  current_col = std::move(p_col_event);
  col_elem = 0;
  step_collision();
}

void Detector::step_collision()
{
  reset();
  interact((*current_col)[col_elem]);
  col_elem++;
}

void Detector::see_detections()
{
  // Uses the information available to guess the particle.
  // Tracker
  std::cout<<"\n\n__ DETECTOR STATUS __"<<std::endl;

  if(tracker->detection_status()) std::cout<<"tracker detection!"<<std::endl;
  else std::cout<<"no tracker detection"<<std::endl;

  // Calorimeter
  calorimeter->print();

  // Muon Detector
  if(muon_detector->detection_status()) std::cout<<"muon detector detection!"<<std::endl;
  else std::cout<<"no muon detector detection"<<std::endl;
}

void Detector::reset()
{
  tracker->reset();
  calorimeter->reset();
  muon_detector->reset();
}