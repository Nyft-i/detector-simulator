#ifndef COL_RESULT_CONTAINER_H_INCLUDED
#define COL_RESULT_CONTAINER_H_INCLUDED

#include<vector>
#include<string>
#include<list>

using std::vector;
using std::string;
using std::list;

class ColResultContainer
{
private:
  string collision_name;
  double input_energy;
  double total_energy_detected;
  vector<list<string>> potential_particles;
public:
  // Constructor
  // Default
  // Parameterised
  ColResultContainer(string con_col_name, double con_input_energy, double con_detected_energy, vector<list<string>> con_potential_particles);
  
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
  int get_num_particles_detected() const;
  double get_total_energy_detected() const;
  double get_input_energy() const;
  list<string> get_potential_particles(int index) const;

  // Setters
  void set_input_energy(double set_input_energy);
  void set_potential_particle_elem(int index, list<string> set_potential_particle_elem);

  // Functionality
  void print();
};

#endif
