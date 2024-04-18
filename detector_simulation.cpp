// PHYS30762 Programming in C++
// Project - Detector Simulation: Jade Salisbury

#include<iostream>

#include"particle.h"
#include"photon.h"

int Particle::numberer=0; // Starts the particle numbering from 0.
int main()
{
  Photon test(1500);
  std::cout<<test.identify();
}