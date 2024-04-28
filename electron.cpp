#include<iostream>

#include"Electron.h"

// Constructors
// Default

// Parameterised
Electron::Electron(double con_energy, int con_pap, vector<double> con_cal_deposits)
{
  true_energy = con_energy;
  rest_mass = 0.511;
  set_cal_deposits(con_cal_deposits);
  if(con_pap==-1)
  {
    charge = 1;
    name = "antielectron";
  }
  else  // Defaults to electron if pap_status is invalid
  {
    charge = -1;
    name = "electron";
  }
}

Electron::Electron(double con_energy, vector<double> con_cal_deposits)
{
  true_energy = con_energy;
  rest_mass = 0.511;
  charge = -1;
  name = "electron";
  pap_status = 1;
  set_cal_deposits(con_cal_deposits);
}

// Deep Copy Constructor
Electron::Electron(const Electron& copy_from)
{
  true_energy = copy_from.true_energy;
  rest_mass = copy_from.rest_mass;
  charge = copy_from.charge;
  name = copy_from.name;
  pap_status = copy_from.pap_status;
  cal_deposits = copy_from.cal_deposits;
}

// Move Constructor
Electron::Electron(Electron&& move_from)
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
Electron& Electron::operator=(const Electron& copy_from)
{
  // Make sure we're not copying ourself.
  if(&copy_from==this) return *this;
  
  // Copy the data
  true_energy = copy_from.true_energy;
  rest_mass = copy_from.rest_mass;
  charge = copy_from.charge;
  name = copy_from.name;
  pap_status = copy_from.pap_status;
  cal_deposits = copy_from.cal_deposits;
  
  return *this;
}
// Move assignment
Electron& Electron::operator=(Electron&& move_from)
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
  pap_status = 0;
  move_from.name = "moved particle";
  
  return *this;
}

// Functionality
void Electron::print()
{
  std::cout<<"\nparticle is : "<<name<<std::endl;
  DepositorParticle::print();
}