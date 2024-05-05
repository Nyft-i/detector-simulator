#include<iostream>

#include"tau.h"
#include"electron.h"
#include"muon.h"
#include"neutrino.h"
#include"nucleon.h"

// Constructors
// Default
Tau::Tau()
{
  true_energy = 0;
  rest_mass = 1.777;
  decay_mode = "hadronic";
  decay_products = construct_decay_particles(decay_mode);
  pap_status = 1;
  charge = -1;
  name = "tau";
}

// Parameterised
Tau::Tau(double con_energy, int con_pap, string con_decay_mode)
{
  true_energy = con_energy;
  rest_mass = 1.777;
  decay_mode = con_decay_mode;
  decay_products = construct_decay_particles(decay_mode);
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
  decay_products = copy_from.decay_products;
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
  decay_products = std::move(move_from.decay_products);
  name = std::move(move_from.name);

  // Set attributes of move_from to nothing.
  move_from.true_energy = 0;
  move_from.rest_mass = 0;
  move_from.charge = 0;
  move_from.pap_status = 0;
  move_from.decay_mode = "";
  move_from.decay_products.clear();
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
  decay_products = copy_from.decay_products;
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
  decay_products = std::move(move_from.decay_products);
  name = std::move(move_from.name);
  
  // Set attributes of move_from to nothing.
  move_from.true_energy = 0;
  move_from.rest_mass = 0;
  move_from.charge = 0;
  pap_status = 0;
  decay_mode = "";
  decay_products.clear();
  move_from.name = "moved particle";
  
  return *this;
}

// Getters
string Tau::get_decay_mode() const {return decay_mode;}
vector<shared_ptr<Particle>> Tau::get_decay_products() const {return decay_products;}
// Setters
void Tau::set_decay_mode(string set_decay_mode) {decay_mode = set_decay_mode;}

// Functionality
void Tau::print()
{
  std::cout<<"\nparticle is : "<<name<<std::endl;
  Particle::print();
  std::cout<<"decay mode : "<<decay_mode<<std::endl;  
  std::cout<<"decay products : ";
  for(shared_ptr<Particle>& particle : decay_products)
  {
    std::cout<<particle->get_name()<<", ";
  }
}

vector<shared_ptr<Particle>> Tau::construct_decay_particles(string decay_products)
{
  // Code mostly copied and altered from Assignment-5
  vector<shared_ptr<Particle>> return_vector;

  // Accepted values of decay_products are "hadronic", "electron" & "muon".

  // The code on its own deals with antiparticles, so the user needn't worry.
  if(decay_products=="antielectron") decay_products ="electron";
  if(decay_products=="antimuon") decay_products="muon";

  // Random energy distribution
  // Code similar to that in DepositorParticle

  vector<double> energy_distro;
  for(int i=0; i<3; i++)
  {
    energy_distro.push_back(std::rand()); // Can be an int between 0 and RAND_MAX which is >32767 (system specific)
  }
  double total = energy_distro[0]+energy_distro[1]+energy_distro[2];
  // Divides each number by the total sum of all random numbers, then it will be out of 1 instead of a random number.
  for(int i=0; i<3; i++)
  {
    energy_distro[i] = energy_distro[i]*true_energy/total;
  }

  // Defaults to hadronic if the user 

  if(decay_products=="electron")
  {
    if(pap_status==-1) // antielectron, electron neutrino, tau antineutrino
    {
      return_vector.push_back(std::make_shared<Electron>(energy_distro[0], -1));
      return_vector.push_back(std::make_shared<Neutrino>(energy_distro[1], 1, 1, false));
      return_vector.push_back(std::make_shared<Neutrino>(energy_distro[2], -1, 3, false));
    }
    else // electron, electron antineutrino, tau neutrino
    {
      return_vector.push_back(std::make_shared<Electron>(energy_distro[0], 1));
      return_vector.push_back(std::make_shared<Neutrino>(energy_distro[0], -1, 1, false));
      return_vector.push_back(std::make_shared<Neutrino>(energy_distro[0], 1, 3, false));
    }
  }
  else if(decay_products=="muon")
  {
    if(pap_status==-1) // antimuon, muon neutrino, tau antineutrino
    {
      return_vector.push_back(std::make_shared<Muon>(energy_distro[0], -1));
      return_vector.push_back(std::make_shared<Neutrino>(energy_distro[0], 1, 2, false));
      return_vector.push_back(std::make_shared<Neutrino>(energy_distro[0], -1, 3, false));
    }
    else // muon, muon antineutrino, tau neutrino
    {
      return_vector.push_back(std::make_shared<Muon>(energy_distro[0], 1));
      return_vector.push_back(std::make_shared<Neutrino>(energy_distro[0], -1, 2, false));
      return_vector.push_back(std::make_shared<Neutrino>(energy_distro[0], 1, 3, false));
    }
  }
  else if(decay_products=="hadronic") // proton-like, tau neutrino
  {
    // Hadronically decaying Taus interact like protons, so we will just use protons, under a different name.
    // Only 2 products so split the energy_distro[2] into the other two
    energy_distro[0] += energy_distro[2]/2;
    energy_distro[1] += energy_distro[2]/2;
    return_vector.push_back(std::make_shared<Nucleon>(energy_distro[0], "decaying_tau")); 
    return_vector.push_back(std::make_shared<Neutrino>(energy_distro[1], 1, 3, false));
  }

  return return_vector;
}