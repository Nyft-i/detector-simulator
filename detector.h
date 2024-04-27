#ifndef DETECTOR_H_INCLUDED
#define DETECTOR_H_INCLUDED

#include"tracker.h"
#include"collision_event.h"

class Detector
{
private:
  Tracker tracker;
public:
  // Constructor
  // Default

  // Parameterised

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
  void interact(CollisionEvent& interacting_event);
};

#endif