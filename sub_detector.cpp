#include<iostream>

#include"sub_detector.h"

// Constructors
// Default
SubDetector::SubDetector()
{
  total_energy_detected = 0;
}

// Functionality
void SubDetector::print()
{
  std::cout<<"SubDetector::print() called"<<std::endl;
  std::cout<<"total energy detected (MeV) : "<<total_energy_detected<<std::endl;
}

void SubDetector::interact(CollisionEvent& interacting_event)
{
  for(int i=0; i<interacting_event.get_num_particles(); i++)
  {
    interact(interacting_event[i]);
  }
}
