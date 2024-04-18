#ifndef PHOTON_H_INCLUDED
#define PHOTON_H_INCLUDED

#include"depositor_particle.h"
#include"particle.h"

class Photon : public DepositorParticle
{
public:
  // Constructors
  // Default
  Photon() = default;
  // Parameterised
  Photon(double con_energy);
  // Copy
  Photon(const Photon& copy_from);
  // Move
  Photon(Photon&& move_from);

  // Destructor, don't need

  // Assignment
  // Copy
  Photon& operator=(const Photon& copy_from);
  // Move
  Photon& operator=(Photon&& move_from);

  // Nothing unique to photons to get or set.

  // Functionality
};

#endif