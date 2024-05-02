#ifndef DEPOSITER_PARTICLE_H_INCLUDED
#define DEPOSITER_PARTICLE_H_INCLUDED

#include"particle.h"

#include<vector>
#include<memory>
using std::vector;

class DepositorParticle : public Particle
{
protected:
  std::unique_ptr<vector<double>> cal_deposits; // Unique pointer to a vector so that it maintains ownership
  // Names of the calorimeter inputs are EM_1, EM_2, HAD_1, HAD_2.

  // These don't have validation the same way that set_true_energy does, so they are dangerous for external use and can result in the user setting cal_deposits to not add up to the true energy.
  // Therefore they are protected. The user is only allowed to set the true energies, and from that the cal_deposits are calculated. They are used in derived rule of 5 methods.
  void set_cal_deposits(vector<double> set_cal_deposits);
  void set_cal_deposits(double set_EM_1, double set_EM_2, double set_HAD_1, double set_HAD_2);
  void set_EM_1(double set_EM_1);
  void set_EM_2(double set_EM_2);
  void set_HAD_1(double set_HAD_1);
  void set_HAD_2(double set_HAD_2);
public:
  // Constructors
  // Default
  DepositorParticle();
  // Parameterised

  // Copy
  // Copy
  DepositorParticle(const DepositorParticle& other);
  // Move
  DepositorParticle(DepositorParticle&& other);


  // Destructor, not needed.

  // Assignment
  // Copy
  DepositorParticle& operator=(const DepositorParticle& other);
  // Move
  DepositorParticle& operator=(DepositorParticle&& other);

  // Getters
  vector<double> get_cal_deposits() const;
  double get_EM_1() const;
  double get_EM_2() const;
  double get_HAD_1() const;
  double get_HAD_2() const;
  
  // Setters
  void set_true_energy(double set_energy) override;

  // Functionality
  string cal_dep_string() const;
  virtual void print() override;
};



#endif