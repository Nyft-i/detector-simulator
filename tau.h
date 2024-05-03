#ifndef TAU_H_INCLUDED
#define TAU_H_INCLUDED

#include<vector>
#include<memory>

#include"particle.h"

using std::vector;
using std::shared_ptr;

class Tau : public Particle
{
private:
  string decay_mode;
  vector<shared_ptr<Particle>> decay_products;
public:
  // Constructors
  // Default
  Tau();
  // Parameterised
  Tau(double con_energy, int con_pap = 1, string con_decay_mode="hadronic");
  // Copy
  Tau(const Tau& copy_from);
  // Move
  Tau(Tau&& move_from);
  
  // Destructor, don't need.

  // Assignment
  // Copy
  Tau& operator=(const Tau& copy_from);
  // Move
  Tau& operator=(Tau&& move_from);

  // Getters
  string get_decay_mode() const;
  vector<shared_ptr<Particle>> get_decay_products() const;
  // Setters
  void set_decay_mode(string set_decay_mode);

  // Functionality
  vector<shared_ptr<Particle>> construct_decay_particles(string decay_mode="leptonic");
  void print() override;
};

#endif