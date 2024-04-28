#ifndef DETECTOR_H_INCLUDED
#define DETECTOR_H_INCLUDED

#include"tracker.h"
#include"collision_event.h"

class Detector
{
private:
  //Calorimiter calorimiter;
  Tracker tracker;
  //MuonChamber muon_chamber;
public:
  // Constructor
  // Default
  Detector();
  // Parameterised
  Detector(int con_tracker_percent_chance);
  // Copy

  // Move


  // Destructor


  // Assignment
  // Copy

  // Move


  // Getters

  // Setters


  // Functionality
  void interact(Particle& interacting_particle);
  void interact(CollisionEvent& col_event);
  void see_detections();
};

#endif