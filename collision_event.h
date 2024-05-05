#ifndef COLLISION_EVENT_H_INCLUDED
#define COLLISION_EVENT_H_INCLUDED

#include<vector>
#include<memory>
#include<string>

#include"particle.h"

using std::shared_ptr;
using std::vector;
using std::string;

class CollisionEvent
{
private:
  double collision_energy;
  string event_name;
  vector<shared_ptr<Particle>> input_particles;
  vector<shared_ptr<Particle>> event_particles;
public:
  // Constructor
  // Default
  // Parameterised
  CollisionEvent(string con_event_name="default");
  
  // Copy
  CollisionEvent(const CollisionEvent& copy_from);
  // Move
  CollisionEvent(CollisionEvent&& move_from);

  // Destructor, not needed.

  // Assignment
  // Copy
  CollisionEvent& operator=(const CollisionEvent& copy_from);
  // Move
  CollisionEvent& operator=(CollisionEvent&& move_from);
  
  // Getters
  string get_event_name() const;
  int get_num_particles() const;
  int get_num_input_particles() const;
  double get_collision_energy() const;


  // Setters
  void set_event_name(string set_event_name);

  // Operator overload
  Particle& operator [](int index);
  Particle& init_particle(int index);

  // Functionality
  void add_particle(shared_ptr<Particle> add_particle);
  void print(int index);
  void print();
};

#endif
