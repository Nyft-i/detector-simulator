#include<iostream>

#include"sub_detector.h"

// Constructors
// Default
SubDetector::SubDetector()
{
  std::cout<<"SubDetector() called"<<std::endl;
  total_energy_detected = 0;
}

// Functionality
void SubDetector::print()
{
  std::cout<<"SubDetector::print() called"<<std::endl;
  std::cout<<"total energy detected (MeV) : "<<total_energy_detected<<std::endl;
}