#ifndef DEPOSITER_PARTICLE_H_INCLUDED
#define DEPOSITER_PARTICLE_H_INCLUDED

#include"particle.h"

#include<vector>
#include<memory>
using std::vector;

class DepositorParticle : public Particle
{
protected:
  std::shared_ptr<vector<double>> cal_deposits; // Unique pointer to a vector of doubles.
  // Names of the calorimeter inputs are EM_1, EM_2, HAD_1, HAD_2.
public:
  // Getters
  const std::shared_ptr<vector<double>>& get_cal_deposits();
  const double get_EM_1();
  const double get_EM_2();
  const double get_HAD_1();
  const double get_HAD_2();
  
  // Setters
  void set_cal_deposits(std::shared_ptr<vector<double>> setter_cal_deposits);
  void set_cal_deposits(double setter_EM_1, double setter_EM_2, double setter_HAD_1, double setter_HAD_2);
  void set_EM_1(double setter_EM_1);
  void set_EM_2(double setter_EM_2);
  void set_HAD_1(double setter_HAD_1);
  void set_HAD_2(double setter_HAD_2);
};

#endif