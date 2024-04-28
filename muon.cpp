#include<iostream>

#include"muon.h"

// Constructors
// Default

// Parameterised
Muon::Muon(double con_energy, int con_pap, double con_tracker_energy, double con_chamber_energy)
{
  true_energy = con_energy;
  rest_mass = 105.66;
  tracker_energy = con_tracker_energy;
  chamber_energy = con_chamber_energy;
  pap_status = con_pap;
  if(pap_status==-1)
  {
    charge = 1;
    name = "antimuon";
  }
  else  // Defaults to muon if pap_status is invalid
  {
    charge = -1;
    name = "muon";
  }
}

// Deep Copy Constructor
Muon::Muon(const Muon& copy_from)
{
  true_energy = copy_from.true_energy;
  rest_mass = copy_from.rest_mass;
  charge = copy_from.charge;
  name = copy_from.name;
  pap_status = copy_from.pap_status;
  tracker_energy = copy_from.tracker_energy;
  chamber_energy = copy_from.chamber_energy;
}

// Move Constructor
Muon::Muon(Muon&& move_from)
{
  true_energy = move_from.true_energy;
  rest_mass = move_from.rest_mass;
  charge = move_from.charge;
  name = std::move(move_from.name);
  pap_status = move_from.pap_status;
  tracker_energy = move_from.tracker_energy;
  chamber_energy = move_from.chamber_energy;

  // Set attributes of move_from to nothing.
  move_from.true_energy = 0;
  move_from.rest_mass = 0;
  move_from.charge = 0;
  move_from.pap_status = 0;
  move_from.tracker_energy = 0;
  move_from.chamber_energy = 0;
  move_from.name = "";
}


// Destructor


// Assignment
// Deep copy assignment
Muon& Muon::operator=(const Muon& copy_from)
{
  // Make sure we're not copying ourself.
  if(&copy_from==this) return *this;
  
  // Copy the data
  true_energy = copy_from.true_energy;
  rest_mass = copy_from.rest_mass;
  charge = copy_from.charge;
  name = copy_from.name;
  pap_status = copy_from.pap_status;
  tracker_energy = copy_from.tracker_energy;
  chamber_energy = copy_from.chamber_energy;

  return *this;
}
// Move assignment
Muon& Muon::operator=(Muon&& move_from)
{
  // Make sure we're not moving from ourself.
  if(&move_from == this) return *this;
  
  // Move the data
  true_energy = move_from.true_energy;
  rest_mass = move_from.rest_mass;
  charge = move_from.charge;
  name = std::move(move_from.name);
  pap_status = move_from.pap_status;
  tracker_energy = move_from.tracker_energy; 
  chamber_energy = move_from.chamber_energy;
  
  // Set attributes of move_from to nothing.
  move_from.true_energy = 0;
  move_from.rest_mass = 0;
  move_from.charge = 0;
  pap_status = 0;
  tracker_energy = 0;
  chamber_energy = 0;
  move_from.name = "moved particle";
  
  return *this;
}

// Getters
const double Muon::get_tracker_energy() {return tracker_energy;}
const double Muon::get_chamber_energy() {return chamber_energy;}

// Setters
void Muon::set_tracker_energy(double set_tracker_energy) {tracker_energy = set_tracker_energy;}
void Muon::set_chamber_energy(double set_chamber_energy) {chamber_energy = set_chamber_energy;}

// Functionality
void Muon::print()
{
  std::cout<<"\nparticle is : "<<name<<std::endl;
  Particle::print();
  std::cout<<"tracker energy (MeV) : "<<tracker_energy<<std::endl;
  std::cout<<"chamber energy (MeV) : "<<chamber_energy<<std::endl;
}