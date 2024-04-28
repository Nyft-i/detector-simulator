#include<iostream>

#include"neutrino.h"

// Constructors
// Default

// Parameterised
Neutrino::Neutrino(double con_energy, int con_pap, int con_flavour, bool con_interacted)
{
  true_energy = con_energy;
  charge = 0;
  pap_status = con_pap;
  if(pap_status==-1) name = "antineutrino";
  else name = "neutrino"; // Defaults to neutrino if pap_status is invalid
  has_interacted = con_interacted;
  set_flavour(con_flavour); // Using setter so reduce code duplication.
}

// Deep Copy Constructor
Neutrino::Neutrino(const Neutrino& copy_from)
{
  true_energy = copy_from.true_energy;
  rest_mass = copy_from.rest_mass;
  charge = copy_from.charge;
  name = copy_from.name;
  pap_status = copy_from.pap_status;
  flavour = copy_from.flavour;
  has_interacted = copy_from.has_interacted;
}

// Move Constructor
Neutrino::Neutrino(Neutrino&& move_from)
{
  true_energy = move_from.true_energy;
  rest_mass = move_from.rest_mass;
  charge = move_from.charge;
  name = std::move(move_from.name);
  pap_status = move_from.pap_status;
  flavour = move_from.flavour;
  has_interacted = move_from.has_interacted;

  // Set attributes of move_from to nothing.
  move_from.true_energy = 0;
  move_from.rest_mass = 0;
  move_from.charge = 0;
  move_from.pap_status = 0;
  move_from.flavour = 0;
  move_from.has_interacted = false;
  move_from.name = "";
}


// Destructor


// Assignment
// Deep copy assignment
Neutrino& Neutrino::operator=(const Neutrino& copy_from)
{
  // Make sure we're not copying ourself.
  if(&copy_from==this) return *this;
  
  // Copy the data
  true_energy = copy_from.true_energy;
  rest_mass = copy_from.rest_mass;
  charge = copy_from.charge;
  name = copy_from.name;
  pap_status = copy_from.pap_status;
  flavour = copy_from.flavour;
  has_interacted = copy_from.has_interacted;

  return *this;
}
// Move assignment
Neutrino& Neutrino::operator=(Neutrino&& move_from)
{
  // Make sure we're not moving from ourself.
  if(&move_from == this) return *this;
  
  // Move the data
  true_energy = move_from.true_energy;
  rest_mass = move_from.rest_mass;
  charge = move_from.charge;
  name = std::move(move_from.name);
  pap_status = move_from.pap_status;
  flavour = move_from.flavour;
  has_interacted = move_from.has_interacted;
  
  // Set attributes of move_from to nothing.
  move_from.true_energy = 0;
  move_from.rest_mass = 0;
  move_from.charge = 0;
  pap_status = 0;
  flavour = 0;
  has_interacted = false;
  move_from.name = "moved particle";
  
  return *this;
}

// Getters
int Neutrino::get_flavour() {return flavour;}
bool Neutrino::get_interaction_status() {return has_interacted;}
string Neutrino::get_flavour_name()
{
  switch(flavour)
  {
  case ELECTRON:
    return "electron";
    break;
  case MUON:
    return "muon";
    break;
  case TAU:
    return "tau";
    break;
  default:
    return "unknown";
    break;
  }
}

// Setters
void Neutrino::set_interaction_status(bool set_interacted) {has_interacted = set_interacted;}
void Neutrino::set_flavour(int set_flavour)
{
  switch(set_flavour)
  {
  case ELECTRON:
    flavour = ELECTRON;
    rest_mass = 0; // Use 0 instead of 1e-6.
    break;
  case MUON:
    flavour = MUON;
    rest_mass = 0.17;
    break;
  case TAU:
    flavour = TAU;
    rest_mass = 18.2;
    break;
  default: // Defaults to electron if flavour is invalid
    flavour = ELECTRON;
    rest_mass = 0;
    break;
  }
}


// Functionality
void Neutrino::print()
{
  std::cout<<"\nparticle is : "<<get_flavour_name()<<" "<<name<<std::endl;
  Particle::print();
  std::cout<<"flavour : "<<flavour<<std::endl;
  std::cout<<"interacted? : "<<has_interacted<<std::endl;
}