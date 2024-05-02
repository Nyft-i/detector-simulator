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
  Particle(const Particle& copy_from);
  // Move
  Particle(Particle&& move_from);

  // Destructor

  // Assignment
  // Copy
  Particle& operator=(const Particle& copy_from);
  // Move
  Particle& operator=(Particle&& move_from);

  // Getters
  int identify() const;
  double get_true_energy() const;
  double get_rest_mass() const;
  int get_charge() const;
  string get_name() const;

  // Setters
  virtual void set_true_energy(double set_energy);
  void set_rest_mass(double set_rm);
  void set_charge(int set_char);
  void set_name(string set_name);

  // Functionality
  virtual void print();
};

#endif