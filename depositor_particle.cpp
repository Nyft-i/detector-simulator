#include<iostream>

#include"depositor_particle.h"

// Getters
const std::shared_ptr<vector<double>>& DepositorParticle::get_cal_deposits()
{
  return cal_deposits;
}
const double DepositorParticle::get_EM_1() {return cal_deposits->at(0);}
const double DepositorParticle::get_EM_2() {return cal_deposits->at(1);}
const double DepositorParticle::get_HAD_1() {return cal_deposits->at(2);}
const double DepositorParticle::get_HAD_2() {return cal_deposits->at(3);}

// Setters
void DepositorParticle::set_cal_deposits(std::shared_ptr<vector<double>> setter_cal_deposits)
{
  ///@todo ensure that the full energy in the cal_deposits is equal to the true energy of the particle.
  cal_deposits = setter_cal_deposits;
}
void DepositorParticle::set_cal_deposits(double setter_EM_1, double setter_EM_2, double setter_HAD_1, double setter_HAD_2)
{
  // Implementation where the user can just enter 4 values and the vector is created for them.
  std::shared_ptr<vector<double>> temp = std::make_shared<vector<double>>();
  temp->push_back(setter_EM_1);
  temp->push_back(setter_EM_2);
  temp->push_back(setter_HAD_1);
  temp->push_back(setter_HAD_2);
  cal_deposits = temp;
}