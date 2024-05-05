#ifndef SUB_DETECTOR_H_INCLUDED
#define SUB_DETECTOR_H_INCLUDED

#include"particle.h"
#include"collision_event.h"

class SubDetector
{
protected:
  double total_energy_detected;
  int num_particles_detected;
  double efficiency;
public:
  // Constructor
  // Default
  SubDetector();
  // Parameterised
  SubDetector(double con_efficiency);

  // Copy

  // Move

  // Destructor, not needed.

  // Assignment
  // Copy

  // Move

  // Getters
  double get_total_energy_detected() const;
  int get_num_particles_detected() const;

  // Setters

  // Functionality
  virtual void print();
  virtual void interact(Particle& interacting_particle)=0;
  virtual void reset()=0;
};

#endif