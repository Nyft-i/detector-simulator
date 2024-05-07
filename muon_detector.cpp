#include<cstdlib>
#include<iostream>
#include<ctime>
#include<chrono>

#include"muon.h"
#include"muon_detector.h"
#include"sub_detector.h"

// Constructors
// Default

MuonDetector::MuonDetector()
{
  hit_layers = std::make_unique<vector<bool>>(2, false);
  percent_chance = 0.7;
}

// Parameterised
MuonDetector::MuonDetector(double con_efficiency, double con_chance):
SubDetector(con_efficiency)
{
  hit_layers = std::make_unique<vector<bool>>(2, false);
  percent_chance = con_chance;
}

// Copy
MuonDetector::MuonDetector(const MuonDetector& copy_from)
{
  total_energy_detected = copy_from.total_energy_detected;
  num_particles_detected = copy_from.num_particles_detected;
  efficiency = copy_from.efficiency;
  hit_layers = std::make_unique<vector<bool>>(*copy_from.hit_layers);
  percent_chance = copy_from.percent_chance;
}

// Move
MuonDetector::MuonDetector(MuonDetector&& move_from)
{
  total_energy_detected = move_from.total_energy_detected;
  num_particles_detected = move_from.num_particles_detected;
  efficiency = move_from.efficiency;
  hit_layers = std::move(move_from.hit_layers);
  percent_chance = move_from.percent_chance;

  // Set move_from to 0.
  move_from.total_energy_detected = 0;
  move_from.num_particles_detected = 0;
  move_from.efficiency = 0;
  move_from.hit_layers = nullptr;
  move_from.percent_chance = 0;
}

// Destructor

// Assignment
// Copy
MuonDetector& MuonDetector::operator=(const MuonDetector& copy_from)
{
  // Check for self assignment
  if(this == &copy_from) return *this;

  // Copy data
  total_energy_detected = copy_from.total_energy_detected;
  num_particles_detected = copy_from.num_particles_detected;
  efficiency = copy_from.efficiency;
  hit_layers = std::make_unique<vector<bool>>(*copy_from.hit_layers);
  percent_chance = copy_from.percent_chance;

  return *this;
}

// Move
MuonDetector& MuonDetector::operator=(MuonDetector&& move_from)
{
  // Check for self assignment
  if(this == &move_from) return *this;
  
  // Steal data
  total_energy_detected = move_from.total_energy_detected;
  num_particles_detected = move_from.num_particles_detected;
  efficiency = move_from.efficiency;
  hit_layers = std::move(move_from.hit_layers);
  percent_chance = move_from.percent_chance;

  // Set move_from to 0.
  move_from.total_energy_detected = 0;
  move_from.num_particles_detected = 0;
  move_from.efficiency = 0;
  move_from.hit_layers = nullptr;
  move_from.percent_chance = 0;

  return *this;
}

// Getters
vector<bool> MuonDetector::get_hit_layers() const {return *hit_layers;}
bool MuonDetector::get_hit_layer(int hit_layer) const {return hit_layers->at(hit_layer);}
int MuonDetector::get_percent_chance() const {return percent_chance;}

// Setters
void MuonDetector::set_hit_layers(vector<bool> set_layers)
{
  hit_layers->at(INNER_MUON_LAYER) = set_layers.at(OUTER_MUON_LAYER);
  hit_layers->at(OUTER_MUON_LAYER) = set_layers.at(OUTER_MUON_LAYER); 
}
void MuonDetector::set_inner_muon_layer(bool set_inner) {hit_layers->at(INNER_MUON_LAYER) = set_inner;}
void MuonDetector::set_outer_muon_layer(bool set_outer) {hit_layers->at(OUTER_MUON_LAYER) = set_outer;}
void MuonDetector::set_percent_chance(int set_percent_chance) {percent_chance = set_percent_chance;}

// Functionality
void MuonDetector::print()
{
  std::cout<<"\nprinting muondetector..."<<std::endl;
  SubDetector::print();
  std::cout<<"INNER_MUON_LAYER hit? : "<<hit_layers->at(INNER_MUON_LAYER)<<std::endl;
  std::cout<<"OUTER_MUON_LAYER hit? : "<<hit_layers->at(OUTER_MUON_LAYER)<<std::endl;
}

void MuonDetector::interact(Particle& interacting_particle)
{
  // Only muons can interact with muon detector
  if(dynamic_cast<Muon*>(&interacting_particle))
  {
    Muon& interacting_muon = dynamic_cast<Muon&>(interacting_particle);
    // This code randomly determines, with percent_chance% probability if each layer has been hit
    
    for(int i=0; i<2; i++)
    { 
      double random_value = ((double) std::rand()) / RAND_MAX;
      if(random_value < percent_chance) hit_layers->at(i) = true;
    }

    // Also the energies from the muon are added to the chamber energies.
    if(get_num_hits()>=1)
    {
      num_particles_detected++;
      total_energy_detected += interacting_muon.get_chamber_energy()*efficiency;
      interacting_muon.set_detected_energy(5, interacting_muon.get_chamber_energy()*efficiency);
    }
  }
}

int MuonDetector::get_num_hits()
{
  // Counts the number of muon layers that have been hit. This can be 0 or 1 or 2.
  int num_hits = 0;
  for(int i=0; i<2; i++)
  {
    if(hit_layers->at(i)) num_hits++;
  }
  return num_hits;
}

bool MuonDetector::detection_status()
{
  // Returns true if the MuonDetector has detected a particle.
  if(get_num_hits()>=1) return true;
  else return false;
}

void MuonDetector::see_detection()
{
  // Prints a message if the MuonDetector has detected a particle.
  if(detection_status()) std::cout<<"MuonDetector detection!"<<std::endl;
  else std::cout<<"no MuonDetector detection"<<std::endl;
}

void MuonDetector::reset()
{
  hit_layers->at(INNER_MUON_LAYER) = false;
  hit_layers->at(OUTER_MUON_LAYER) = false;
}

void MuonDetector::total_reset()
{
  reset();
  total_energy_detected = 0;
  num_particles_detected = 0;
}