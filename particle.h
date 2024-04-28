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
  int pap_status; // 1 for particle, -1 for antiparticle and 0 for a particle that is its own antiparticle.
  string name;
public:
  // Constructors
  // Default - This is an abstract class therefore doesn't need parameterised constructors
  Particle();
  // Parameterised
  // Copy
  
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
  virtual void set_true_energy(double set_energy);
  void set_rest_mass(double set_rm);
  void set_charge(int set_char);
  void set_name(string set_name);

  // Functionality
  virtual void print();
};

#endif