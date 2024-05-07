#ifndef MUON_H_INCLUDED
#define MUON_H_INCLUDED

#include"particle.h"

class Muon : public Particle
{
private:
  double tracker_energy;
  double chamber_energy;
  bool interacted_with_muon_detector;
public:
  // Constructors
  // Default
  Muon();
  // Parameterised
  Muon(double con_energy, int con_pap=1);
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
  double get_tracker_energy() const;
  double get_chamber_energy() const;
  bool get_interacted_with_detector() const;

  // Setters
  void set_tracker_energy(double set_tracker_energy);
  void set_chamber_energy(double set_chamber_energy);
  void set_true_energy(double set_energy) override;
  void set_interacted_with_detector(bool set_interacted_with_muon);

  // Functionality
  void print() override;
};

#endif