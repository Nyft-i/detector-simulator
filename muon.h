#ifndef MUON_H_INCLUDED
#define MUON_H_INCLUDED

#include"particle.h"

class Muon : public Particle
{
private:
  double tracker_energy;
  double chamber_energy;
public:
  // Constructors
  // Default
  Muon();
  // Parameterised
  Muon(double con_energy, int con_pap=1, double con_tracker_energy=0, double con_chamber_energy=0);
  // Copy
  Muon(const Muon& copy_from);
  // Move
  Muon(Muon&& move_from);

  // Destructor, don't need.

  // Assignment
  // Copy
  Muon& operator=(const Muon& copy_from);
  // Move
  Muon& operator=(Muon&& move_from);

  // Getters
  const double get_tracker_energy();
  const double get_chamber_energy();

  // Setters
  void set_tracker_energy(double set_tracker_energy);
  void set_chamber_energy(double set_chamber_energy);

  // Functionality
  void print() override;
};

#endif