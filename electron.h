#ifndef ELECTRON_H_INCLUDED
#define ELECTRON_H_INCLUDED

#include"depositor_particle.h"

class Electron : public DepositorParticle
{
private:
  // Electron has nothing unique! It just deposits in the calorimiter layer, so it inherits from DepositorParticle.
public:
  // Constructors
  // Default
  Electron();
  // Parameterised
  Electron(double con_energy, int con_pap=1);
  // Copy
  Electron(const Electron& copy_from);
  // Move
  Electron(Electron&& move_from);

  // Destructor, don't need.

  // Assignment
  // Copy
  Electron& operator=(const Electron& copy_from);
  // Move
  Electron& operator=(Electron&& move_from);

  // Functionality
  void print() override;
  void set_true_energy(double set_energy) override;
};

#endif