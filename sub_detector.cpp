#include<iostream>

#include"sub_detector.h"

// Constructors
// Default
SubDetector::SubDetector()
{
  total_energy_detected = 0;
  efficiency = 1;
}

// Parameterised
SubDetector::SubDetector(double con_efficiency)
{
  total_energy_detected = 0;
  efficiency = con_efficiency;
}

// Getters
double SubDetector::get_total_energy_detected() const {return total_energy_detected;}

// Functionality
void SubDetector::print()
{
  std::cout<<"total energy detected (GeV) : "<<total_energy_detected<<std::endl;
}
