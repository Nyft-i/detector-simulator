#include<iostream>

#include"photon.h"

// Constructors
// Default

// Parameterised
Photon::Photon(double con_energy)
{
  rest_mass = 0;
  charge = 0;
  pap_status = 0;
  name = "photon";
  set_true_energy(con_energy);
}

// Deep Copy Constructor
Photon::Photon(const Photon& copy_from)
{
  true_energy = copy_from.true_energy;
  rest_mass = copy_from.rest_mass;
  charge = copy_from.charge;
  pap_status = copy_from.pap_status;
  from_tau = copy_from.from_tau;
  name = copy_from.name;
  cal_deposits = std::make_unique<vector<double>>(*copy_from.cal_deposits);
  detected_energies = std::make_unique<vector<double>>(*copy_from.detected_energies);
}

// Move Constructor
Photon::Photon(Photon&& move_from)
{
  true_energy = move_from.true_energy;
  rest_mass = move_from.rest_mass;
  charge = move_from.charge;
  name = std::move(move_from.name);
  pap_status = move_from.pap_status;
  from_tau = move_from.from_tau;
  cal_deposits = std::move(move_from.cal_deposits);
  detected_energies = std::move(move_from.detected_energies);
  
  // Set attributes of move_from to nothing.
  move_from.true_energy = 0;
  move_from.rest_mass = 0;
  move_from.charge = 0;
  move_from.pap_status = 0;
  move_from.from_tau = false;
  move_from.name = "";
  move_from.cal_deposits = nullptr;
  move_from.detected_energies = nullptr;
}


// Destructor


// Assignment
// Deep copy assignment
Photon& Photon::operator=(const Photon& copy_from)
{
  // Make sure we're not copying ourself.
  if(&copy_from==this) return *this;
  
  // Copy the data
  true_energy = copy_from.true_energy;
  rest_mass = copy_from.rest_mass;
  charge = copy_from.charge;
  pap_status = copy_from.pap_status;
  from_tau = copy_from.from_tau;
  name = copy_from.name;
  cal_deposits = std::make_unique<vector<double>>(*copy_from.cal_deposits);
  detected_energies = std::make_unique<vector<double>>(*copy_from.detected_energies);
  
  return *this;
}
// Move assignment
Photon& Photon::operator=(Photon&& move_from)
{
  // Make sure we're not moving from ourself.
  if(&move_from == this) return *this;
  
  // Move the data
  true_energy = move_from.true_energy;
  rest_mass = move_from.rest_mass;
  charge = move_from.charge;
  name = std::move(move_from.name);
  pap_status = move_from.pap_status;
  from_tau = move_from.from_tau;
  cal_deposits = std::move(move_from.cal_deposits);
  detected_energies = std::move(move_from.detected_energies);
  
  // Set attributes of move_from to nothing.
  move_from.true_energy = 0;
  move_from.rest_mass = 0;
  move_from.charge = 0;
  move_from.pap_status = 0;
  move_from.from_tau = false;
  move_from.name = "moved particle";
  move_from.cal_deposits = nullptr;
  move_from.detected_energies = nullptr;
  
  return *this;
}

// Functionality
void Photon::print()
{
  std::cout<<"\nparticle is : "<<name<<std::endl;
  DepositorParticle::print();
}

void Photon::set_true_energy(double set_energy)
{
  // This overrides the method in DepositorParticle, photons and electrons only deposit in the EM layers.
  // Sets the true energy using the base class method. We benefit from the existing verification in Particle.
  Particle::set_true_energy(set_energy);

  // When the user tries to set the true energy, it is split randomly between the calorimeter deposits.
  vector<double> random_ratio;
  for(int i=0; i<2; i++)
  {
    random_ratio.push_back(std::rand()); // Can be an int between 0 and RAND_MAX which is >32767
  }
  double total = random_ratio[0]+random_ratio[1];
  // Divides each number by the total sum of all random numbers, then it will be out of 1 instead of a random number.
  for(int i=0; i<2; i++)
  {
    random_ratio[i] = random_ratio[i]/total;
  }
  
  // Now the cal_deposits can be altered
  for(int i=0; i<2; i++)
  {
    cal_deposits->at(i) = true_energy*random_ratio[i]; // From the true energy in case set_energy was invalid
  }
}