#include<cstdlib>
#include<iostream>
#include<ctime>
#include<chrono>

#include"tracker.h"
#include"sub_detector.h"
#include"particle.h"
#include"muon.h"

// Constructors
// Default

Tracker::Tracker()
{
  hit_layers = std::make_shared<vector<bool>>(3);
  hit_layers->at(INNER_PIXEL_LAYER) = false;
  hit_layers->at(OUTER_PIXEL_LAYER) = false;
  hit_layers->at(STRIP_LAYER) = false;
  percent_chance = 1;
}

// Parameterised
Tracker::Tracker(double con_efficiency, double con_chance):
SubDetector(con_efficiency),
percent_chance(con_chance)
{
  hit_layers = std::make_shared<vector<bool>>(3);
  hit_layers->at(INNER_PIXEL_LAYER) = false;
  hit_layers->at(OUTER_PIXEL_LAYER) = false;
  hit_layers->at(STRIP_LAYER) = false;
}

// Copy
Tracker::Tracker(const Tracker& copy_from)
{
  total_energy_detected = copy_from.total_energy_detected;
  num_particles_detected = copy_from.num_particles_detected;
  efficiency = copy_from.efficiency;
  hit_layers = copy_from.hit_layers;
  percent_chance = copy_from.percent_chance;
}

// Move
Tracker::Tracker(Tracker&& move_from)
{
  total_energy_detected = move_from.total_energy_detected;
  num_particles_detected = move_from.num_particles_detected;
  efficiency = move_from.efficiency;
  hit_layers = std::move(move_from.hit_layers);
  percent_chance = move_from.percent_chance;

  // Set move_from to 0.
  move_from.total_energy_detected = 0;
  move_from.hit_layers = nullptr;
  move_from.num_particles_detected = 0;
  move_from.efficiency = 0;
  move_from.percent_chance = 0;
}

// Destructor

// Assignment
// Copy
Tracker& Tracker::operator=(const Tracker& copy_from)
{
  // Check for self assignment
  if(this == &copy_from) return *this;

  // Copy data
  total_energy_detected = copy_from.total_energy_detected;
  num_particles_detected = copy_from.num_particles_detected;
  efficiency = copy_from.efficiency;
  hit_layers = copy_from.hit_layers;
  percent_chance = copy_from.percent_chance;

  return *this;
}

// Move
Tracker& Tracker::operator=(Tracker&& move_from)
{
  // Check for self assignment
  if(this == &move_from) return *this;
  
  // Steal data
  total_energy_detected = move_from.total_energy_detected;
  hit_layers = std::move(move_from.hit_layers);
  num_particles_detected = move_from.num_particles_detected;
  efficiency = move_from.efficiency;
  percent_chance = move_from.percent_chance;

  // Set move_from to 0.
  move_from.total_energy_detected = 0;
  move_from.hit_layers = nullptr;
  move_from.num_particles_detected = 0;
  move_from.efficiency = 0;
  move_from.percent_chance = 0;

  return *this;
}

// Getters
vector<bool> Tracker::get_hit_layers() const {return *hit_layers;}
bool Tracker::get_hit_layer(int hit_layer) const {return hit_layers->at(hit_layer);}
int Tracker::get_percent_chance() const {return percent_chance;}

// Setters
void Tracker::set_hit_layers(vector<bool> set_layers)
{
  hit_layers->at(INNER_PIXEL_LAYER) = set_layers.at(INNER_PIXEL_LAYER);
  hit_layers->at(OUTER_PIXEL_LAYER) = set_layers.at(OUTER_PIXEL_LAYER); 
  hit_layers->at(STRIP_LAYER) = set_layers.at(STRIP_LAYER);
}
void Tracker::set_inner_pixel_layer(bool set_inner) {hit_layers->at(INNER_PIXEL_LAYER) = set_inner;}
void Tracker::set_outer_pixel_layer(bool set_outer) {hit_layers->at(OUTER_PIXEL_LAYER) = set_outer;}
void Tracker::set_strip_layer(bool set_strip) {hit_layers->at(STRIP_LAYER) = set_strip;}
void Tracker::set_percent_chance(int set_percent_chance) {percent_chance = set_percent_chance;}

// Functionality
void Tracker::print()
{
  std::cout<<"\nprinting tracker..."<<std::endl;
  SubDetector::print();
  std::cout<<"INNER_PIXEL_LAYER hit? : "<<hit_layers->at(INNER_PIXEL_LAYER)<<std::endl;
  std::cout<<"OUTER_PIXEL_LAYER hit? : "<<hit_layers->at(OUTER_PIXEL_LAYER)<<std::endl;
  std::cout<<"STRIP_LAYER hit? : "<<hit_layers->at(STRIP_LAYER)<<std::endl;
}

void Tracker::interact(Particle& interacting_particle)
{
  // Only particles with a charge can interact with the tracker.
  if(interacting_particle.get_charge() == 0) return;
  else
  {
    // This code randomly determines, with percent_chance% probability if each layer has been hit
    for(int i=0; i<3; i++)
    {
      int random_value = std::rand();
      if(random_value/RAND_MAX < percent_chance) hit_layers->at(i) = true;
    }

    // more than 2 hits
    if(get_num_hits()>=2) 
    { 
      num_particles_detected++;
      // The amount of energy deposited, not a muon
      if(typeid(&interacting_particle)!=typeid(Muon)) 
      {
        total_energy_detected += interacting_particle.get_true_energy()*efficiency;
        interacting_particle.set_detected_energy(0, interacting_particle.get_true_energy()*efficiency); // Only detected at efficency*energy if 2 or more hit layers
      }
      else 
      {
        // If the particle is a muon, it deposits a different amount of energy in detector + tracker
        Muon& interacting_muon = dynamic_cast<Muon&>(interacting_particle);
        total_energy_detected += interacting_muon.get_tracker_energy()*efficiency;
        interacting_muon.set_detected_energy(0, interacting_muon.get_tracker_energy()*efficiency); // Only detected at efficency*energy if 2 or more hit layers
      }
    }
  }
}

int Tracker::get_num_hits()
{
  // Counts the number of pixel layers that have been hit. This can be 0, 1 or 2.
  int num_hits = 0;
  for(int i=0; i<3; i++)
  {
    if(hit_layers->at(i)) num_hits++;
  }
  return num_hits;
}

bool Tracker::detection_status()
{
  // Returns true if the tracker has detected a particle.
  if(get_num_hits()>=2) return true;
  else return false;
}

void Tracker::see_detection()
{
  // Prints a message if the tracker has detected a particle.
  if(detection_status()) std::cout<<"tracker detection!"<<std::endl;
  else std::cout<<"no tracker detection"<<std::endl;
}

void Tracker::reset()
{
  hit_layers->at(INNER_PIXEL_LAYER) = false;
  hit_layers->at(OUTER_PIXEL_LAYER) = false;
  hit_layers->at(STRIP_LAYER) = false;
}

void Tracker::total_reset()
{
  reset();
  total_energy_detected = 0;
  num_particles_detected = 0;
}