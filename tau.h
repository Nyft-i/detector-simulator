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
public:
  // Constructors
  // Default
  Tau();
  // Parameterised
  Tau(double con_energy, int con_pap = 1, string con_decay_mode="leptonic");
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
  const string get_decay_mode();
  // Setters
  void set_decay_mode(string set_decay_mode);

  // Functionality
  shared_ptr<Particle> decay();
  void print() override;
};

#endif