#include<iostream>

#include"particle.h"

// Constructor
Particle::Particle():
  identifier(numberer),
  true_energy(1),
  rest_mass(0),
  charge(0),
  pap_status(0),
  name("unknown particle"),
  from_tau(false)
{
  // Number Management
  numberer++;
  detected_energies = std::make_unique<vector<double>>(6, 0);
}

// Parameterised
Particle::Particle(double con_energy, double con_rm, int con_charge, string con_name, int con_pap):
  identifier(numberer),
  rest_mass(con_rm),
  charge(con_charge),
  pap_status(con_pap),
  name(con_name),
  from_tau(false)
{
  // Number Management
  numberer++;
  set_true_energy(con_energy);
  detected_energies = std::make_unique<vector<double>>(6, 0);
}

// Copy
Particle::Particle(const Particle& copy_from)
{
  // Copy the data
  true_energy = copy_from.true_energy;
  rest_mass = copy_from.rest_mass;
  charge = copy_from.charge;
  name = copy_from.name;
  pap_status = copy_from.pap_status;
  from_tau = copy_from.from_tau;
  detected_energies = std::make_unique<vector<double>>(*copy_from.detected_energies);
}

// Move
Particle::Particle(Particle&& move_from)
{
  // Move data/steal
  true_energy = move_from.true_energy;
  rest_mass = move_from.rest_mass;
  charge = move_from.charge;
  name = std::move(move_from.name);
  pap_status = move_from.pap_status;
  from_tau = move_from.from_tau;
  detected_energies = std::move(move_from.detected_energies);

  // Set attributes of move_from to nothing.
  move_from.true_energy = 0;
  move_from.rest_mass = 0;
  move_from.charge = 0;
  move_from.pap_status = 0;
  move_from.name = "";
  move_from.from_tau = false;
  move_from.detected_energies = std::make_unique<vector<double>>(6, 0);
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
  from_tau = copy_from.from_tau;
  detected_energies = std::make_unique<vector<double>>(*copy_from.detected_energies);

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
  from_tau = move_from.from_tau;
  detected_energies = std::move(move_from.detected_energies);

  // Set attributes of move_from to nothing.
  move_from.true_energy = 0;
  move_from.rest_mass = 0;
  move_from.charge = 0;
  move_from.pap_status = 0;
  move_from.name = "";
  move_from.from_tau = false;
  move_from.detected_energies = std::make_unique<vector<double>>(6, 0);

  return *this;
}
  
// Getters
int Particle::identify() const {return identifier;}
double Particle::get_true_energy() const {return true_energy;}
double Particle::get_rest_mass() const {return rest_mass;}
int Particle::get_charge() const {return charge;}
string Particle::get_name() const {return name;}
int Particle::get_pap_status() const {return pap_status;}
double Particle::get_detected_energy(int index) const {return detected_energies->at(index);}
bool Particle::get_from_tau() const {return from_tau;}

// Setters
void Particle::set_true_energy(double set_energy) 
{
  // True energy is all energy that is not the rest mass in this simulation, so only must be greater than.
  if(set_energy<0) true_energy = 0;
  else true_energy = set_energy;  
}

void Particle::set_rest_mass(double set_rm)
{
  // Ensures that the rest mass cannot be negative.
  rest_mass = std::abs(set_rm);
}
void Particle::set_charge(int set_char) {charge = set_char;}
void Particle::set_name(string set_name) {name = set_name;}
void Particle::set_pap_status(int set_pap) {pap_status = set_pap;}
void Particle::set_detected_energy(int index, double set_energy) {detected_energies->at(index) = set_energy;}
void Particle::set_from_tau(bool set_from_tau) {from_tau = set_from_tau;}

void Particle::print()
{
  //Overidden print functions call this one at the end. So this needs to print everything that is not unique to any particle.
  std::cout<<"this particle is identified by : "<<identifier<<std::endl;
  std::cout<<"true energy (GeV) : "<<true_energy<<std::endl;
  std::cout<<"rest mass (GeV) : "<<rest_mass<<std::endl;
  std::cout<<"charge (e) : "<<charge<<std::endl;
  std::cout<<"name : "<<name<<std::endl;
}

// Virtual Members