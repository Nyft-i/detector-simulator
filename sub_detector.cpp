#include<iostream>

#include"sub_detector.h"

// Constructors
// Default
SubDetector::SubDetector()
{
  total_energy_detected = 0;
  efficiency = 1;
  num_particles_detected = 0;
}

// Parameterised
SubDetector::SubDetector(double con_efficiency)
{
  total_energy_detected = 0;
  efficiency = con_efficiency;
  num_particles_detected = 0;
}

// Copy
SubDetector::SubDetector(const SubDetector& copy_from)
{
  total_energy_detected = copy_from.total_energy_detected;
  efficiency = copy_from.efficiency;
  num_particles_detected = copy_from.num_particles_detected;
}

// Move
SubDetector::SubDetector(SubDetector&& move_from)
{
  total_energy_detected = move_from.total_energy_detected;
  efficiency = move_from.efficiency;
  num_particles_detected = move_from.num_particles_detected;

  // Set move_from to 0.
  move_from.total_energy_detected = 0;
  move_from.efficiency = 0;
  move_from.num_particles_detected = 0;
}

// Destructor, not needed.

// Assignment
// Copy
SubDetector& SubDetector::operator=(const SubDetector& copy_from)
{
  // Make sure we're not copying ourself.
  if(&copy_from==this) return *this;
  
  // Copy the data
  total_energy_detected = copy_from.total_energy_detected;
  efficiency = copy_from.efficiency;
  num_particles_detected = copy_from.num_particles_detected;
  
  return *this;
}

// Move
SubDetector& SubDetector::operator=(SubDetector&& move_from)
{
  // Make sure we're not moving from ourself.
  if(&move_from == this) return *this;
  
  // Move the data
  total_energy_detected = move_from.total_energy_detected;
  efficiency = move_from.efficiency;
  num_particles_detected = move_from.num_particles_detected;
  
  // Set move_from to 0.
  move_from.total_energy_detected = 0;
  move_from.efficiency = 0;
  move_from.num_particles_detected = 0;
  
  return *this;
}

// Getters
double SubDetector::get_total_energy_detected() const {return total_energy_detected;}
int SubDetector::get_num_particles_detected() const {return num_particles_detected;}

// Functionality
void SubDetector::print()
{
  std::cout<<"total energy detected (GeV) : "<<total_energy_detected<<std::endl;
  std::cout<<"number of particles detected : "<<num_particles_detected<<std::endl;
}