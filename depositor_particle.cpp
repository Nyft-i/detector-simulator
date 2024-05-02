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
  cal_deposits = std::make_unique<vector<double>>(4, 0);
}
// Copy
DepositorParticle::DepositorParticle(const DepositorParticle& copy_from)
{
  true_energy = copy_from.true_energy;
  rest_mass = copy_from.rest_mass;
  charge = copy_from.charge;
  name = copy_from.name;
  pap_status = copy_from.pap_status;
  cal_deposits = std::make_unique<vector<double>>(copy_from.cal_deposits);
}

// Move
DepositorParticle::DepositorParticle(DepositorParticle&& move_from)
{
  true_energy = move_from.true_energy;
  rest_mass = move_from.rest_mass;
  charge = move_from.charge;
  name = std::move(move_from.name);
  pap_status = move_from.pap_status;
  cal_deposits = std::move(move_from.cal_deposits);
  
  // Set attributes of move_from to nothing.
  move_from.true_energy = 0;
  move_from.rest_mass = 0;
  move_from.charge = 0;
  move_from.pap_status = 0;
  move_from.name = "";
  move_from.cal_deposits = std::make_unique<vector<double>>(4, 0);
}

// Destructor, don't need

// Assignment
// Copy
DepositorParticle& DepositorParticle::operator=(const DepositorParticle& copy_from)
{
  // Make sure we're not copying ourself.
  if(&copy_from==this) return *this;
  
  // Copy the data
  true_energy = copy_from.true_energy;
  rest_mass = copy_from.rest_mass;
  charge = copy_from.charge;
  name = copy_from.name;
  pap_status = copy_from.pap_status;
  cal_deposits = std::make_unique<vector<double>>(copy_from.cal_deposits);
  
  return *this;
}

// Move
DepositorParticle& DepositorParticle::operator=(DepositorParticle&& move_from)
{
  // Make sure we're not moving ourself.
  if(&move_from==this) return *this;

  true_energy = move_from.true_energy;
  rest_mass = move_from.rest_mass;
  charge = move_from.charge;
  name = std::move(move_from.name);
  pap_status = move_from.pap_status;
  cal_deposits = std::move(move_from.cal_deposits);
  
  // Set attributes of move_from to nothing.
  move_from.true_energy = 0;
  move_from.rest_mass = 0;
  move_from.charge = 0;
  move_from.pap_status = 0;
  move_from.name = "";
  move_from.cal_deposits = std::make_unique<vector<double>>(4, 0);

  return *this;
}


// Getters
vector<double> DepositorParticle::get_cal_deposits() const {return *cal_deposits;}
double DepositorParticle::get_EM_1() const {return cal_deposits->at(0);}
double DepositorParticle::get_EM_2() const {return cal_deposits->at(1);}
double DepositorParticle::get_HAD_1() const {return cal_deposits->at(2);}
double DepositorParticle::get_HAD_2() const {return cal_deposits->at(3);}

// Setters
void DepositorParticle::set_cal_deposits(vector<double> set_cal_deposits)
{
  ///@todo ensure that the full energy in the cal_deposits is equal to the true energy of the particle.
  cal_deposits = std::make_unique<vector<double>>(set_cal_deposits);
}

void DepositorParticle::set_cal_deposits(double set_EM_1, double set_EM_2, double set_HAD_1, double set_HAD_2)
{
  // Implementation where the user can just enter 4 values and the vector is created for them.
  std::unique_ptr<vector<double>> temp = std::make_unique<vector<double>>();
  temp->push_back(set_EM_1);
  temp->push_back(set_EM_2);
  temp->push_back(set_HAD_1);
  temp->push_back(set_HAD_2);
  cal_deposits = std::move(temp);
}

void DepositorParticle::set_true_energy(double set_energy)
{
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
string DepositorParticle::cal_dep_string() const
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