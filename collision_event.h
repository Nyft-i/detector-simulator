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
  string event_name;
  vector<shared_ptr<Particle>> event_particles;
public:
  // Constructor
  // Default
  CollisionEvent();
  // Parameterised
  CollisionEvent(string con_event_name);
  
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

  // Setters

  // Operator overload
  Particle& operator [](int index);

  // Functionality
  void add_particle(Particle& add_particle);
  void print(int index);
  void print();
};

#endif
