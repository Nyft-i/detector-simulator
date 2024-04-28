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
  name = copy_from.name;
  cal_deposits = copy_from.cal_deposits;
}

// Move Constructor
Photon::Photon(Photon&& move_from)
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
  name = copy_from.name;
  cal_deposits = copy_from.cal_deposits;
  
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
  cal_deposits = std::move(move_from.cal_deposits);
  
  // Set attributes of move_from to nothing.
  move_from.true_energy = 0;
  move_from.rest_mass = 0;
  move_from.charge = 0;
  move_from.pap_status = 0;
  move_from.name = "moved particle";
  
  return *this;
}

// Functionality
void Photon::print()
{
  std::cout<<"\nparticle is : "<<name<<std::endl;
  DepositorParticle::print();
}