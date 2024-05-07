#ifndef COL_RESULT_CONTAINER_H_INCLUDED
#define COL_RESULT_CONTAINER_H_INCLUDED

#include<vector>
#include<string>
#include<list>
#include<memory>

class Detector;
#include"particle.h"
#include"collision_event.h"

using std::vector;
using std::string;
using std::list;
using std::shared_ptr;
using std::unique_ptr;

class ColResultContainer
{
private:
  string collision_name;
  double input_energy;
  double total_energy_detected;
  unique_ptr<CollisionEvent> input_event;
  vector<string> potential_particles;
  shared_ptr<Detector> p_detector;

  int tracker_particles;
  int calorimeter_particles;
  int muon_particles;

  double tracker_energy;
  double calorimeter_energy;
  double muon_energy;

  int correct_guesses;
public:
  // Constructor
  // Default
  // Parameterised
  ColResultContainer(string con_col_name, double con_input_energy, double con_detected_energy, vector<string> con_potential_particles, unique_ptr<CollisionEvent> con_input_event, shared_ptr<Detector> con_p_detector);
  
  // Copy
  ColResultContainer(const ColResultContainer& copy_from);
  // Move
  ColResultContainer(ColResultContainer&& move_from);

  // Destructor, not needed.

  // Assignment
  // Copy
  ColResultContainer& operator=(const ColResultContainer& copy_from);
  // Move
  ColResultContainer& operator=(ColResultContainer&& move_from);
  
  // Getters
  string get_collision_name() const;
  CollisionEvent& get_input_event() const;
  int get_num_particles_detected() const;
  double get_total_energy_detected() const;
  double get_input_energy() const;

  int get_tracker_particles() const;
  int get_calorimeter_particles() const;
  int get_muon_particles() const;

  double get_tracker_energy() const;
  double get_calorimeter_energy() const;
  double get_muon_energy() const;

  int get_correct_guesses() const;

  // Setters
  void set_input_energy(double set_input_energy);
  void set_potential_particle_elem(int index, vector<string> set_potential_particle_elem);

  // Functionality
  void print_individual(int index);
  void print();
};

#endif
