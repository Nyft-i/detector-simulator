#ifndef PARTICLE_H_INCLUDED
#define PARTICLE_H_INCLUDED

#include<string>
#include<vector>
#include<memory>

using std::string;
using std::vector;
using std::unique_ptr;


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

  unique_ptr<vector<double>> detected_energies; // Variable that takes efficiency into account. Tells the collision event what energy it was detected at.
public:
  // Constructors
  // Default - This is an abstract class therefore doesn't need parameterised constructors
  Particle();
  // Parameterised
  Particle(double con_energy, double con_rm, int con_charge, string con_name, int con_pap);
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
  int get_pap_status() const;
  double get_detected_energy(int index) const;

  // Setters
  virtual void set_true_energy(double set_energy);
  void set_rest_mass(double set_rm);
  void set_charge(int set_char);
  void set_name(string set_name);
  void set_pap_status(int set_pap);
  void set_detected_energy(int index, double set_energy);

  // Functionality
  virtual void print();
};

#endif