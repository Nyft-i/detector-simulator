#include<iostream>

#include"particle.h"

// Constructor
Particle::Particle()
{
  // Number Management
  identifier = numberer;
  numberer++;

  true_energy = 0;
  rest_mass = 0;
  charge = 0;
  pap_status = 0; // Particle/antiparticle status
  name = "unknown particle";
}

// Copy
Particle::Particle(const Particle& copy_from)
{
  true_energy = copy_from.true_energy;
  rest_mass = copy_from.rest_mass;
  charge = copy_from.charge;
  name = copy_from.name;
  pap_status = copy_from.pap_status;
}

// Move
Particle::Particle(Particle&& move_from)
{
  true_energy = move_from.true_energy;
  rest_mass = move_from.rest_mass;
  charge = move_from.charge;
  name = std::move(move_from.name);
  pap_status = move_from.pap_status;

  // Set attributes of move_from to nothing.
  move_from.true_energy = 0;
  move_from.rest_mass = 0;
  move_from.charge = 0;
  move_from.pap_status = 0;
  move_from.name = "";
}

// Destructor

// Assignment
// Copy
Particle& Particle::operator=(const Particle& copy_from)
{
  // Make sure we're not copying ourself.
  if(&copy_from==this) return *this;
  
  // Copy the data
  true_energy = copy_from.true_energy;
  rest_mass = copy_from.rest_mass;
  charge = copy_from.charge;
  name = copy_from.name;
  pap_status = copy_from.pap_status;

  return *this;
}

// Move
Particle& Particle::operator=(Particle&& move_from)
{
  // Make sure we're not moving from ourself.
  if(&move_from == this) return *this;

  true_energy = move_from.true_energy;
  rest_mass = move_from.rest_mass;
  charge = move_from.charge;
  name = std::move(move_from.name);
  pap_status = move_from.pap_status;

  // Set attributes of move_from to nothing.
  move_from.true_energy = 0;
  move_from.rest_mass = 0;
  move_from.charge = 0;
  move_from.pap_status = 0;
  move_from.name = "";

  return *this;
}
  
// Getters
int Particle::identify() {return identifier;}
double Particle::get_true_energy() {return true_energy;}
double Particle::get_rest_mass() {return rest_mass;}
int Particle::get_charge() {return charge;}
string Particle::get_name() {return name;}

// Setters
void Particle::set_true_energy(double set_energy) 
{
  // Makes sure that the energy is not less than the rest mass.
  // For photons, which have 0 rest mass, it is ensuring that its true energy is not negative.
  if(set_energy>rest_mass) true_energy = set_energy;
  else true_energy = rest_mass;  
}

void Particle::set_rest_mass(double set_rm)
{
  // Ensures that the rest mass cannot be negative.
  if(set_rm<0) rest_mass = std::abs(set_rm);
  // Also the rest mass shouldn't be larger than the true energy.
  else if(set_rm>true_energy) rest_mass = true_energy;
  else rest_mass = set_rm;

}
void Particle::set_charge(int set_char) {charge = set_char;}
void Particle::set_name(string set_name) {name = set_name;}

void Particle::print()
{
  //Overidden print functions call this one at the end. So this needs to print everything that is not unique to any particle.
  std::cout<<"this particle is identified by : "<<identifier<<std::endl;
  std::cout<<"true energy (MeV) : "<<true_energy<<std::endl;
  std::cout<<"rest mass (MeV) : "<<rest_mass<<std::endl;
  std::cout<<"charge (e) : "<<charge<<std::endl;
  std::cout<<"name : "<<name<<std::endl;
}