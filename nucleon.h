#ifndef NUCLEON_H_INCLUDED
#define NUCLEON_H_INCLUDED

#include"particle.h"
#include"depositor_particle.h"

#include<string>
using std::string;

class Nucleon : public DepositorParticle
{
private:
  string nuc_type;
public:
  // Constructors
  // Default
  Nucleon() = default;
  // Parameterised
  Nucleon(string con_nuc_type, double con_energy);
  // Copy
  Nucleon(const Nucleon& copy_from);
  // Move
  Nucleon(Nucleon&& move_from);

  // Destructor, don't need

  // Assignment
  // Copy
  Nucleon& operator=(const Nucleon& copy_from);
  // Move
  Nucleon& operator=(Nucleon&& move_from);

  // Functionality
};


#endif