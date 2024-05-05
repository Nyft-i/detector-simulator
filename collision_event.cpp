#include<iostream>

#include"collision_event.h"
#include"particle.h"
#include"tau.h"

// Constructors
// Default
// Parameterised
CollisionEvent::CollisionEvent(string con_event_name)
{
  event_name = con_event_name;
  input_particles = {};
  event_particles = {}; // Empty vector.
  collision_energy = 0;
}

// Copy
CollisionEvent::CollisionEvent(const CollisionEvent& copy_from)
{
  event_name = copy_from.event_name;
  event_particles = copy_from.event_particles;
  input_particles = copy_from.input_particles;
  collision_energy = copy_from.collision_energy;
}

// Move
CollisionEvent::CollisionEvent(CollisionEvent&& move_from)
{
  event_name = std::move(move_from.event_name);
  event_particles = std::move(move_from.event_particles);
  input_particles = std::move(move_from.input_particles);
  collision_energy = move_from.collision_energy;

  // Set attributes of move_from to nothing.
  move_from.event_name = "";
  move_from.event_particles = {};
  move_from.input_particles = {};
  move_from.collision_energy = 0;
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
  input_particles = copy_from.input_particles;
  collision_energy = copy_from.collision_energy;

  return *this;
}

// Move
CollisionEvent& CollisionEvent::operator=(CollisionEvent&& move_from)
{
  // Self assignment
  if(this == &move_from) return *this;

  event_name = std::move(move_from.event_name);
  event_particles = std::move(move_from.event_particles);
  input_particles = std::move(move_from.input_particles);
  collision_energy = move_from.collision_energy;

  // Set attributes of move_from to nothing.
  move_from.event_name = "";
  move_from.event_particles = {};
  move_from.input_particles = {};
  move_from.collision_energy = 0;
  return *this;
}


// Getters
string CollisionEvent::get_event_name() const {return event_name;}
int CollisionEvent::get_num_particles() const {return event_particles.size();}
int CollisionEvent::get_num_input_particles() const {return input_particles.size();}
double CollisionEvent::get_collision_energy() const {return collision_energy;}

// Setters
void CollisionEvent::set_event_name(string set_event_name) {event_name = set_event_name;}

// Operator overload
Particle& CollisionEvent::operator [](int index)
{
  return *event_particles[index];
} 

Particle& CollisionEvent::init_particle(int index)
{
  return *input_particles[index];
}

// Functionality
void CollisionEvent::add_particle(shared_ptr<Particle> add_particle)
{
  // Copy the energy from the particles into the event.
  collision_energy += add_particle->get_true_energy();
  input_particles.push_back(add_particle); // Copy, to make sure that we have a record of all the start particles

  if(std::dynamic_pointer_cast<Tau>(add_particle))
  {
    shared_ptr<Tau> p_tau = std::dynamic_pointer_cast<Tau>(add_particle);
    for(shared_ptr<Particle> p_product : p_tau->get_decay_products())
    {
      event_particles.push_back(p_product); // Copy, still belongs to the Tau
    }
  }
  else
  {
    event_particles.push_back(std::move(add_particle)); // Move
  }
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