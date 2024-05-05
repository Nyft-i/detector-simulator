#include<iostream>

#include"col_result_container.h"

// Constructors
// Parameterised
ColResultContainer::ColResultContainer(string con_col_name, double con_input_energy, double con_detected_energy, vector<list<string>> con_potential_particles):
  collision_name(con_col_name),
  input_energy(con_input_energy),
  total_energy_detected(con_detected_energy), 
  potential_particles(con_potential_particles)
{}

// Copy
ColResultContainer::ColResultContainer(const ColResultContainer& copy_from)
{
  collision_name = copy_from.collision_name;
  input_energy = copy_from.input_energy;
  total_energy_detected = copy_from.total_energy_detected;
  potential_particles = copy_from.potential_particles;
}

// Move
ColResultContainer::ColResultContainer(ColResultContainer&& move_from)
{
  collision_name = std::move(move_from.collision_name);
  input_energy = move_from.input_energy;
  total_energy_detected = move_from.total_energy_detected;
  potential_particles = std::move(move_from.potential_particles);

  // Set move_from to 0.
  move_from.collision_name = "";
  move_from.input_energy = 0;
  move_from.total_energy_detected = 0;
  move_from.potential_particles = {};
}

// Assignment
// Copy
ColResultContainer& ColResultContainer::operator=(const ColResultContainer& copy_from)
{
  // Make sure we're not copying ourself.
  if(&copy_from==this) return *this;
  
  // Copy the data
  collision_name = copy_from.collision_name;
  input_energy = copy_from.input_energy;
  total_energy_detected = copy_from.total_energy_detected;
  potential_particles = copy_from.potential_particles;
  
  return *this;
}

// Move
ColResultContainer& ColResultContainer::operator=(ColResultContainer&& move_from)
{
  // Make sure we're not copying ourself.
  if(&move_from==this) return *this;
  
  // Move the data
  collision_name = std::move(move_from.collision_name);
  input_energy = move_from.input_energy;
  total_energy_detected = move_from.total_energy_detected;
  potential_particles = std::move(move_from.potential_particles);
  
  // Set move_from to 0.
  move_from.collision_name = "";
  move_from.input_energy = 0;
  move_from.total_energy_detected = 0;
  move_from.potential_particles = {};
  
  return *this;
}

// Getters

// Setters
void ColResultContainer::set_input_energy(double set_input_energy) {input_energy = set_input_energy;}

// Fucntionality
void ColResultContainer::print()
{
  std::cout<<"collision results for event : \""<<collision_name<<"\""<<std::endl;
  std::cout<<"input energy (MeV) : "<< input_energy<<std::endl;
  std::cout<<"total energy detected (MeV) : "<<total_energy_detected<<std::endl;
  std::cout<<"potential particles (for a non-ideal detector) : "<<std::endl;
  for(int i=0; i<potential_particles.size(); i++)
  {
    std::cout<<"particle "<<i<<" : ";
    for(auto& particle : potential_particles[i])
    {
      std::cout<<particle<<", ";
    }
    std::cout<<std::endl;
  }
}
