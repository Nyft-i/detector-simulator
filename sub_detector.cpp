#include<iostream>

#include"sub_detector.h"

// Constructors
// Default
SubDetector::SubDetector()
{
  total_energy_detected = 0;
  efficiency = 0;
}

// Parameterised
SubDetector::SubDetector(double con_efficiency)
{
  total_energy_detected = 0;
  efficiency = con_efficiency;
}

// Functionality
void SubDetector::print()
{
  std::cout<<"total energy detected (MeV) : "<<total_energy_detected<<std::endl;
}
