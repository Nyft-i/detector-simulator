#ifndef PHOTON_H_INCLUDED
#define PHOTON_H_INCLUDED

#include"energy_depositer.h"
#include"particle.h"

class Photon : public Particle, public EnergyDepositer
{
public:
  // Constructors
  // Default
  Photon() = default;
  // Parameterised
  Photon(double con_energy);
  // Copy
  Photon(Photon& copy_from);
  // Move
  Photon(Photon&& move_from);

  // Destructor

  // Assignment
  // Copy
  Photon& operator=(Photon& copy_from);
  // Move
  Photon& operator=(Photon&& move_from);

  // Getters
  // Nothing unique to photons.
  // Setters

  // Functionality
};

#endif