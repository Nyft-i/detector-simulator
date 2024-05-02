#include<cstdlib>
#include<iostream>
#include<ctime>
#include<chrono>

#include"tracker.h"
#include"sub_detector.h"

// Constructors
// Default

Tracker::Tracker()
{
  hit_layers = std::make_shared<vector<bool>>(3);
  hit_layers->at(INNER_PIXEL_LAYER) = false;
  hit_layers->at(OUTER_PIXEL_LAYER) = false;
  hit_layers->at(STRIP_LAYER) = false;
  percent_chance = 70;
}

// Parameterised
Tracker::Tracker(int con_percent_chance)
{
  hit_layers = std::make_shared<vector<bool>>(3);
  hit_layers->at(INNER_PIXEL_LAYER) = false;
  hit_layers->at(OUTER_PIXEL_LAYER) = false;
  hit_layers->at(STRIP_LAYER) = false;
  percent_chance = con_percent_chance;
}

// Copy
Tracker::Tracker(const Tracker& copy_from)
{
  total_energy_detected = copy_from.total_energy_detected;
  hit_layers = copy_from.hit_layers;
}

// Move
Tracker::Tracker(Tracker&& move_from)
{
  total_energy_detected = move_from.total_energy_detected;
  hit_layers = std::move(move_from.hit_layers);

  // Set move_from to 0.
  move_from.total_energy_detected = 0;
  move_from.hit_layers = nullptr;

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
  hit_layers = copy_from.hit_layers;

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

  // Set move_from to 0.
  move_from.total_energy_detected = 0;
  move_from.hit_layers = nullptr;

  return *this;
}

// Getters
std::shared_ptr<vector<bool>>& Tracker::get_hit_layers() {return hit_layers;}
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
  std::cout<<"Tracker::print() called"<<std::endl;
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
      if(random_value%100 < percent_chance) hit_layers->at(i) = true;
    }
  }
}

void Tracker::interact(CollisionEvent& col_event)
{
  for(int i=0; i<col_event.get_num_particles(); i++)
  {
    interact(col_event[i]);
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
  total_energy_detected = 0;
}