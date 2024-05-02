#ifndef DETECTOR_H_INCLUDED
#define DETECTOR_H_INCLUDED

#include<memory>

#include"tracker.h"
#include"calorimeter.h"
#include"collision_event.h"

using std::unique_ptr;

class Detector
{
private:
  unique_ptr<Tracker> tracker;
  unique_ptr<Calorimeter> calorimeter;
  //MuonChamber muon_chamber;
public:
  // Constructor
  // Default
  Detector();
  // Parameterised
  Detector(int con_tracker_percent_chance);
  // Copy
  Detector(const Detector& copy_from);
  // Move
  Detector(Detector&& move_from);

  // Destructor

  // Assignment
  // Copy
  Detector& operator=(const Detector& copy_from);
  // Move
  Detector& operator=(Detector&& move_from);

  // Getters
  Tracker& get_tracker();
  //Calorimeter& get_calorimeter();
  //MuonDetector& get_muon_detector();
  // Setters
  void set_tracker(shared_ptr<Tracker> set_tracker);

  // Functionality

  void interact(Particle& interacting_particle);
  void interact(CollisionEvent& col_event);
  void see_detections();
  void reset();
};

#endif