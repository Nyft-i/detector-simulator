#ifndef SUB_DETECTOR_H_INCLUDED
#define SUB_DETECTOR_H_INCLUDED

#include"particle.h"
#include"collision_event.h"

class SubDetector
{
protected:
  double total_energy_detected;
public:
  // Constructor
  // Default
  SubDetector();
  // Parameterised

  // Copy

  // Move

  // Destructor, not needed.

  // Assignment
  // Copy

  // Move

  // Getters

  // Setters

  // Functionality
  virtual void print();
  virtual void interact(Particle& interacting_particle)=0;
  void interact(CollisionEvent& interacting_event);
  virtual void reset()=0;
};

#endif