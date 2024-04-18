#ifndef PARTICLE_H_INCLUDED
#define PARTICLE_H_INCLUDED

#include<string>
using std::string;

class Particle
{
protected:
  int identifier;
  static int numberer;
  double true_energy;
  double rest_mass;
  int charge; // There are only particles with integer charges required in this assignment.
  string name;
public:
  // Constructors
  // Default - This is an abstract class therefore doesn't need parameterised constructors
  Particle();
  // Parameterised
  // Copy
  Particle(const Particle& other_particle) 
  {
    identifier = other_particle.identifier;
    true_energy = other_particle.true_energy;
    rest_mass = other_particle.rest_mass;
    charge = other_particle.charge;
    name = other_particle.name;
  }
  // Move

  // Destructor

  // Assignment
  // Copy
  // Move

  // Getters
  int identify();
  double get_true_energy();
  double get_rest_mass();
  int get_charge();
  string get_name();

  // Setters
  void set_true_energy(double setter_energy);
  void set_rest_mass(double setter_rm);
  void set_charge(int setter_char);
  void set_name(string setter_name);

  // Functionality
};

#endif