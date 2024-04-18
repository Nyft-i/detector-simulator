#include<iostream>

#include"particle.h"

// Constructor
Particle::Particle()
{
  std::cout<<"Particle() called."<<std::endl;
  // Number Management
  identifier = numberer;
  numberer++;

  true_energy = 0;
  rest_mass = 0;
  charge = 0;
  name = "unknown particle";
}

// Getters
int Particle::identify() {return identifier;}

double Particle::get_true_energy() {return true_energy;}
double Particle::get_rest_mass() {return rest_mass;}
int Particle::get_charge() {return charge;}
string Particle::get_name() {return name;}

// Setters
void Particle::set_true_energy(double setter_energy) 
{
  // Makes sure that the energy is not less than the rest mass.
  if(setter_energy>rest_mass) true_energy = setter_energy;
  else true_energy = rest_mass;  
}
void Particle::set_rest_mass(double setter_rm)
{
  // Ensures that the rest mass cannot be negative.
  if(setter_rm<0) rest_mass = std::abs(setter_rm);
  // Also the rest mass shouldn't be larger than the true energy.
  else if(setter_rm>true_energy) rest_mass = true_energy;
  else rest_mass = setter_rm;

}
void Particle::set_charge(int setter_char) {charge = setter_char;}
void Particle::set_name(string setter_name) {name = setter_name;}