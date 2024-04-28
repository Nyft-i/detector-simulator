#include<iostream>

#include"particle.h"

// Constructor
Particle::Particle()
{
  //std::cout<<"Particle() called."<<std::endl;
  // Number Management
  identifier = numberer;
  numberer++;

  true_energy = 0;
  rest_mass = 0;
  charge = 0;
  pap_status = 0; // Particle/antiparticle status
  name = "unknown particle";
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