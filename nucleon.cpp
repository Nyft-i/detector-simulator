#include<iostream>

#include"nucleon.h"

// Constructors
// Default
Nucleon::Nucleon()
{
  // Assume neutron if not told otherwise
  nuc_type = "neutron";
  rest_mass = 0.939565;
  charge = 0;
  name = "nucleon";
  set_true_energy(939.565);
}

// Parameterised
Nucleon::Nucleon(double con_energy, string con_nuc_type)
{
  // Case insensitivity, converting user input to lowercase.
  for(int i=0; i<con_nuc_type.length(); i++) {con_nuc_type[i] = tolower(con_nuc_type[i]);}
  // Checking for user input.
  if(con_nuc_type=="proton")
  {
    nuc_type = con_nuc_type;
    rest_mass = 0.938272;
    charge = 1;
    name = "nucleon";
    set_true_energy(con_energy);
  }
  else if(con_nuc_type=="decaying_tau")
  {
    nuc_type = con_nuc_type;
    rest_mass = 0.938272;
    charge = 1;
    name = "decaying_tau";
    set_true_energy(con_energy);
  }
  else if(con_nuc_type=="neutron")
  {
    nuc_type = con_nuc_type;
    rest_mass = 0.939565;
    charge = 0;
    name = "nucleon";
    set_true_energy(con_energy);
  }
  else
  {
    // Error message and default to neutron user doesn't enter a valid nucleon type.
    std::cout<<"Invalid nucleon type. Defaulting to neutron."<<std::endl;
    nuc_type="neutron";
    rest_mass = 0.939565;
    charge = 0;
    name = "nucleon";
    set_true_energy(con_energy);
  }
}

// Copy
Nucleon::Nucleon(const Nucleon& copy_from)
{
  true_energy = copy_from.true_energy;
  rest_mass = copy_from.rest_mass;
  charge = copy_from.charge;
  name = copy_from.name;
  nuc_type = copy_from.nuc_type;
}

// Move
Nucleon::Nucleon(Nucleon&& move_from)
{
  true_energy = move_from.true_energy;
  rest_mass = move_from.rest_mass;
  charge = move_from.charge;
  name = std::move(move_from.name);
  nuc_type = std::move(move_from.nuc_type);

  // Set attributes of move_from to nothing.
  move_from.true_energy = 0;
  move_from.rest_mass = 0;
  move_from.charge = 0;
  move_from.name = "";
  move_from.nuc_type = "";
}

// Destructor 

// Assignment
// Copy
Nucleon& Nucleon::operator=(const Nucleon& copy_from)
{
  // Make sure we're not copying ourself.
  if(&copy_from==this) return *this;
  
  // Copy the data
  true_energy = copy_from.true_energy;
  rest_mass = copy_from.rest_mass;
  charge = copy_from.charge;
  name = copy_from.name;
  nuc_type = copy_from.nuc_type;

  return *this;
}

// Move
Nucleon& Nucleon::operator=(Nucleon&& move_from)
{
  // Make sure we're not moving from ourself.
  if(&move_from == this) return *this;
  
  // Move the data
  true_energy = move_from.true_energy;
  rest_mass = move_from.rest_mass;
  charge = move_from.charge;
  name = std::move(move_from.name);
  nuc_type = std::move(move_from.nuc_type);

  // Set attributes of move_from to nothing.
  move_from.true_energy = 0;
  move_from.rest_mass = 0;
  move_from.charge = 0;
  move_from.name = "";
  move_from.nuc_type = "";

  return *this;
}

// Destructor

// Getters
string Nucleon::get_nuc_type() const {return nuc_type;}

// Functionality
void Nucleon::print()
{
  std::cout<<"particle is : "<<nuc_type<<std::endl;
  DepositorParticle::print();
}
