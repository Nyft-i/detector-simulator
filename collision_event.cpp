#include<iostream>

#include"collision_event.h"
#include"particle.h"

// Constructors
// Default
CollisionEvent::CollisionEvent()
{
  event_particles = {}; // Empty vector.
}

// Parameterised
CollisionEvent::CollisionEvent(string con_event_name)
{
  event_name = con_event_name;
  event_particles = {}; // Empty vector.
}

// Copy
CollisionEvent::CollisionEvent(const CollisionEvent& copy_from)
{
  event_name = copy_from.event_name;
  event_particles = copy_from.event_particles;
}

// Move
CollisionEvent::CollisionEvent(CollisionEvent&& move_from)
{
  event_name = std::move(move_from.event_name);
  event_particles = std::move(move_from.event_particles);

  // Set attributes of move_from to nothing.
  move_from.event_name = "";
  move_from.event_particles = {};
}

// Destructor


// Assignment
// Copy
CollisionEvent& CollisionEvent::operator=(const CollisionEvent& copy_from)
{
  // Self assignment
  if(this == &copy_from) return *this;

  event_name = copy_from.event_name;
  event_particles = copy_from.event_particles;
  return *this;
}

// Move
CollisionEvent& CollisionEvent::operator=(CollisionEvent&& move_from)
{
  // Self assignment
  if(this == &move_from) return *this;

  event_name = std::move(move_from.event_name);
  event_particles = std::move(move_from.event_particles);

  // Set attributes of move_from to nothing.
  move_from.event_name = "";
  move_from.event_particles = {};
  return *this;
}


// Getters
string CollisionEvent::get_event_name() {return event_name;}
int CollisionEvent::get_num_particles() {return event_particles.size();}

// Setters
void CollisionEvent::set_event_name(string set_event_name) {event_name = set_event_name;}

// Operator overload
Particle& CollisionEvent::operator [](int index)
{
  return *event_particles[index];
}  

// Functionality
void CollisionEvent::add_particle(Particle& add_particle)
{
  event_particles.push_back(std::make_shared<Particle>(add_particle));
}

void CollisionEvent::print(int index)
{
  // Prints a single particle.
  std::cout<<"printing particle index "<<index<<" from event \""<<event_name<<"\""<<std::endl;
  event_particles[index]->print();
}

void CollisionEvent::print()
{
  // Prints all when no index given
  std::cout<<"no number given, printing all particles in event \""<<event_name<<"\"\n"<<std::endl;
  for(int i=0; i<event_particles.size(); i++)
  {
    std::cout<<"printing particle index "<<i<<std::endl;
    event_particles[i]->print();
    std::cout<<std::endl;
  }
}