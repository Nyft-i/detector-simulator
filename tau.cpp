#include<iostream>

#include"Tau.h"

// Constructors
// Default

// Parameterised
Tau::Tau(double con_energy, int con_pap, string con_decay_mode)
{
  true_energy = con_energy;
  rest_mass = 1777;
  decay_mode = con_decay_mode;
  decay_mode = con_decay_mode;
  pap_status = con_pap;
  if(pap_status==-1)
  {
    charge = 1;
    name = "antitau";
  }
  else  // Defaults to tau if pap_status is invalid
  {
    charge = -1;
    name = "tau";
  }
}

// Deep Copy Constructor
Tau::Tau(const Tau& copy_from)
{
  true_energy = copy_from.true_energy;
  rest_mass = copy_from.rest_mass;
  charge = copy_from.charge;
  pap_status = copy_from.pap_status;
  decay_mode = copy_from.decay_mode;
  name = copy_from.name;
}

// Move Constructor
Tau::Tau(Tau&& move_from)
{
  true_energy = move_from.true_energy;
  rest_mass = move_from.rest_mass;
  charge = move_from.charge;
  pap_status = move_from.pap_status;
  decay_mode = std::move(move_from.decay_mode);
  name = std::move(move_from.name);

  // Reset the moved-from object
  move_from.true_energy = 0;
  move_from.rest_mass = 0;
  move_from.charge = 0;
  move_from.pap_status = 0;
  move_from.decay_mode = "";
  move_from.name = "";
}


// Destructor


// Assignment
// Deep copy assignment
Tau& Tau::operator=(const Tau& copy_from)
{
  // Make sure we're not copying ourself.
  if(&copy_from==this) return *this;
  
  // Copy the data
  true_energy = copy_from.true_energy;
  rest_mass = copy_from.rest_mass;
  charge = copy_from.charge;
  pap_status = copy_from.pap_status;
  decay_mode = copy_from.decay_mode;
  name = copy_from.name;

  return *this;
}
// Move assignment
Tau& Tau::operator=(Tau&& move_from)
{
  // Make sure we're not moving from ourself.
  if(&move_from == this) return *this;
  
  // Move the data
  true_energy = move_from.true_energy;
  rest_mass = move_from.rest_mass;
  charge = move_from.charge;
  pap_status = move_from.pap_status;
  decay_mode = std::move(move_from.decay_mode);
  name = std::move(move_from.name);
  
  // Reset the moved-from object
  move_from.true_energy = 0;
  move_from.rest_mass = 0;
  move_from.charge = 0;
  pap_status = 0;
  decay_mode = "";
  move_from.name = "moved particle";
  
  return *this;
}

// Getters
const string Tau::get_decay_mode() {return decay_mode;}
// Setters
void Tau::set_decay_mode(string setter_decay_mode) {decay_mode = setter_decay_mode;}

// Functionality
void Tau::print()
{
  std::cout<<"\nparticle is : "<<name<<std::endl;
  Particle::print();
  std::cout<<"decay mode : "<<decay_mode<<std::endl;  
}