#include<cstdlib>
#include<iostream>
#include<ctime>

#include"tracker.h"
#include"sub_detector.h"

// Constructors
// Default

Tracker::Tracker()
{
  std::cout<<"Tracker() called"<<std::endl;
  hit_layers = std::make_shared<vector<bool>>(3);
  hit_layers->at(INNER_PIXEL_LAYER) = false;
  hit_layers->at(OUTER_PIXEL_LAYER) = false;
  hit_layers->at(STRIP_LAYER) = false;
}

// Parameterised

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
bool Tracker::get_hit_layer(int hit_layer) {return hit_layers->at(hit_layer);}

// Setters
void Tracker::set_hit_layers(vector<bool> setter_layers)
{
  hit_layers->at(INNER_PIXEL_LAYER) = setter_layers.at(INNER_PIXEL_LAYER);
  hit_layers->at(OUTER_PIXEL_LAYER) = setter_layers.at(OUTER_PIXEL_LAYER); 
  hit_layers->at(STRIP_LAYER) = setter_layers.at(STRIP_LAYER);
}
void Tracker::set_inner_pixel_layer(bool setter_inner) {hit_layers->at(INNER_PIXEL_LAYER) = setter_inner;}
void Tracker::set_outer_pixel_layer(bool setter_outer) {hit_layers->at(OUTER_PIXEL_LAYER) = setter_outer;}
void Tracker::set_strip_layer(bool setter_strip) {hit_layers->at(STRIP_LAYER) = setter_strip;}

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
  ///@todo find out if this is the correct way to do this from piazza. Works for now
  int percent_chance = 70;
  // This code randomly determines, with percent_chance% probability if each layer has been hit
  std::srand(std::time(nullptr)); // use current time as seed for random generator
  for(int i=0; i<3; i++)
  {
    int random_value = std::rand();
    if(random_value%100 < percent_chance) hit_layers->at(i) = true;
  }
}