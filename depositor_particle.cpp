#include<iostream>
#include<memory>
#include<vector>
#include<string>
#include<cstdlib>

#include"depositor_particle.h"

using std::vector;

// Constructors
// Default

DepositorParticle::DepositorParticle()
{
  std::cout<<"DepositorParticle() called"<<std::endl;
  cal_deposits = std::make_shared<vector<double>>(4, 0);
}

// Parameterised


// Getters
const std::shared_ptr<vector<double>>& DepositorParticle::get_cal_deposits() {return cal_deposits;}
const double DepositorParticle::get_EM_1() {return cal_deposits->at(0);}
const double DepositorParticle::get_EM_2() {return cal_deposits->at(1);}
const double DepositorParticle::get_HAD_1() {return cal_deposits->at(2);}
const double DepositorParticle::get_HAD_2() {return cal_deposits->at(3);}

// Setters
void DepositorParticle::set_cal_deposits(vector<double> set_cal_deposits)
{
  ///@todo ensure that the full energy in the cal_deposits is equal to the true energy of the particle.
  cal_deposits = std::make_shared<vector<double>>(set_cal_deposits);
}

void DepositorParticle::set_cal_deposits(double set_EM_1, double set_EM_2, double set_HAD_1, double set_HAD_2)
{
  // Implementation where the user can just enter 4 values and the vector is created for them.
  std::shared_ptr<vector<double>> temp = std::make_shared<vector<double>>();
  temp->push_back(set_EM_1);
  temp->push_back(set_EM_2);
  temp->push_back(set_HAD_1);
  temp->push_back(set_HAD_2);
  cal_deposits = temp;
}

void DepositorParticle::set_true_energy(double set_energy)
{
  std::cout<<"DepositorParticle::set_true_energy(double) called"<<std::endl;
  // Sets the true energy using the base class method. We benefit from the existing verification in Particle.
  Particle::set_true_energy(set_energy);

  // When the user tries to set the true energy, it is split randomly between the calorimeter deposits.
  vector<double> random_ratio;
  for(int i=0; i<4; i++)
  {
    random_ratio.push_back(std::rand()); // Can be an int between 0 and RAND_MAX which is >32767
  }
  double total = random_ratio[0]+random_ratio[1]+random_ratio[2]+random_ratio[3];
  // Divides each number by the total sum of all random numbers, then it will be out of 1 instead of a random number.
  for(int i=0; i<4; i++)
  {
    random_ratio[i] = random_ratio[i]/total;
  }
  
  // Now the cal_deposits can be altered
  for(int i=0; i<4; i++)
  {
    cal_deposits->at(i) = true_energy*random_ratio[i]; // From the true energy in case set_energy was invalid
  }
}

// Functionality
string DepositorParticle::cal_dep_string()
{
  string return_string;
  return_string = "("+std::to_string(cal_deposits->at(0))+", "+std::to_string(cal_deposits->at(1))+", "+std::to_string(cal_deposits->at(2))+", "+std::to_string(cal_deposits->at(3))+")";
  return return_string;
}

void DepositorParticle::print()
{
  Particle::print();
  std::cout<<"calorimiter deposits (MeV) : "<<cal_dep_string()<<std::endl;
}