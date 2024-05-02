#ifndef NEUTRINO_H_INCLUDED
#define NEUTRINO_H_INCLUDED

#include"particle.h"

class Neutrino : public Particle
{
private:
  enum flavours{ELECTRON=1, MUON=2, TAU=3}; 
  int flavour; // Analogous to generation. 
  bool has_interacted; 
public:
  // Constructors
  // Default
  Neutrino();
  // Parameterised
  Neutrino(double con_energy, int con_pap=1, int con_flavour=ELECTRON, bool con_interacted=false);
  // Copy
  Neutrino(const Neutrino& copy_from);
  // Move
  Neutrino(Neutrino&& move_from);

  // Destructor, don't need

  // Assignment
  // Copy
  Neutrino& operator=(const Neutrino& copy_from);
  // Move
  Neutrino& operator=(Neutrino&& move_from);
  
  // Getters
  int get_flavour() const;
  bool get_interaction_status() const;
  string get_flavour_name() const;
  // Setters
  void set_interaction_status(bool set_interacted);
  void set_flavour(int set_flavour);

  // Functionality
  void print() override;  
};

#endif