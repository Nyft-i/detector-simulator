#include<iostream>

#include"col_result_container.h"
#include"collision_event.h"
#include"particle.h"
#include"depositor_particle.h"
#include"muon.h"
#include"tau.h"
#include"nucleon.h"
#include"neutrino.h"

// Constructors
// Parameterised
ColResultContainer::ColResultContainer(string con_col_name, double con_input_energy, double con_detected_energy, vector<list<string>> con_potential_particles, unique_ptr<CollisionEvent> con_input_event):
  collision_name(con_col_name),
  input_energy(con_input_energy),
  total_energy_detected(con_detected_energy), 
  potential_particles(con_potential_particles)
{
  input_event = std::move(con_input_event);
}

// Copy
ColResultContainer::ColResultContainer(const ColResultContainer& copy_from)
{
  collision_name = copy_from.collision_name;
  input_energy = copy_from.input_energy;
  total_energy_detected = copy_from.total_energy_detected;
  potential_particles = copy_from.potential_particles;
  input_event = std::make_unique<CollisionEvent>(*copy_from.input_event);
}

// Move
ColResultContainer::ColResultContainer(ColResultContainer&& move_from)
{
  collision_name = std::move(move_from.collision_name);
  input_energy = move_from.input_energy;
  total_energy_detected = move_from.total_energy_detected;
  potential_particles = std::move(move_from.potential_particles);
  input_event = std::move(move_from.input_event);

  // Set move_from to 0.
  move_from.collision_name = "";
  move_from.input_energy = 0;
  move_from.total_energy_detected = 0;
  move_from.potential_particles = {};
  move_from.input_event = nullptr;
}

// Assignment
// Copy
ColResultContainer& ColResultContainer::operator=(const ColResultContainer& copy_from)
{
  // Make sure we're not copying ourself.
  if(&copy_from==this) return *this;
  
  // Copy the data
  collision_name = copy_from.collision_name;
  input_energy = copy_from.input_energy;
  total_energy_detected = copy_from.total_energy_detected;
  potential_particles = copy_from.potential_particles;
  input_event = std::make_unique<CollisionEvent>(*copy_from.input_event);
  
  return *this;
}

// Move
ColResultContainer& ColResultContainer::operator=(ColResultContainer&& move_from)
{
  // Make sure we're not copying ourself.
  if(&move_from==this) return *this;
  
  // Move the data
  collision_name = std::move(move_from.collision_name);
  input_energy = move_from.input_energy;
  total_energy_detected = move_from.total_energy_detected;
  potential_particles = std::move(move_from.potential_particles);
  input_event = std::move(move_from.input_event);
  
  // Set move_from to 0.
  move_from.collision_name = "";
  move_from.input_energy = 0;
  move_from.total_energy_detected = 0;
  move_from.potential_particles = {};
  move_from.input_event = nullptr;
  
  return *this;
}

// Getters
string ColResultContainer::get_collision_name() const {return collision_name;}
double ColResultContainer::get_input_energy() const {return input_energy;}
double ColResultContainer::get_total_energy_detected() const {return total_energy_detected;}
int ColResultContainer::get_num_particles_detected() const {return input_event->get_num_particles();}

// Setters
void ColResultContainer::set_input_energy(double set_input_energy) {input_energy = set_input_energy;}

void ColResultContainer::print_individual(int index, int &offset) // Offset determines disparity in number of particles between start and end of event
{
  Particle& curr_particle = (*input_event)[index+offset];
  
  // Checks if it is a nucleon so it can print the type rather than printing the word nucleon at the beginning
  if(dynamic_cast<Nucleon*>(&curr_particle))
  {
    Nucleon& curr_nucleon = dynamic_cast<Nucleon&>(curr_particle);
    std::cout<<curr_nucleon.get_nuc_type();
  }
  else
  {
    std::cout<<curr_particle.get_name();
  }

  // Basic information
  std::cout<<" : id = "<<curr_particle.identify()<<", charge = "<<curr_particle.get_charge()<<", true energy (GeV) = "<<curr_particle.get_true_energy()<<std::endl;

  // Energy detected vs energy deposited in each section.
  // Tracker
  std::cout<<"  tracker:"<<std::endl;
  // Muons act differently in the tracker
  if(dynamic_cast<Muon*>(&curr_particle))
  {
    Muon& curr_muon = dynamic_cast<Muon&>(curr_particle);
    std::cout<<"    energy (GeV) = "<<curr_muon.get_detected_energy(0)<<" / "<<curr_muon.get_tracker_energy()<<std::endl;
  }
  // Neutrinos leave leave nothing in the detector
  if(dynamic_cast<Neutrino*>(&curr_particle))
  {
    std::cout<<"    energy (GeV) = "<<curr_particle.get_detected_energy(0)<<" / 0"<<std::endl;
  }
  else
  {
    std::cout<<"    energy (GeV) = "<<curr_particle.get_detected_energy(0)<<" / "<<curr_particle.get_true_energy()<<std::endl;
  }
  
  // Calorimeter
  std::cout<<"  calorimeter:"<<std::endl;
  // dynamic cast to a depositor particle to retrieve cal energy deposits true energies
  if(dynamic_cast<DepositorParticle*>(&curr_particle))
  {
    DepositorParticle& curr_depositor = dynamic_cast<DepositorParticle&>(curr_particle);
    std::cout<<"    energy (GeV) = "<<"("<<curr_depositor.get_detected_energy(1)<<", "<<curr_depositor.get_detected_energy(2)<<", "<<curr_depositor.get_detected_energy(3)<<", "<<curr_depositor.get_detected_energy(4)<<")"<<" / "<<curr_depositor.cal_dep_string()<<std::endl;
  }
  else
  {
    std::cout<<"    energy (GeV) = (0, 0, 0, 0) / (0, 0, 0, 0)"<<std::endl;
  }

  // Muon Detector
  std::cout<<"  muon_detector: "<<std::endl;
  // Cast to muon, their get_true_energy does not suffice as it is not the same as the energy deposited in the muon detector
  if(dynamic_cast<Muon*>(&curr_particle))
  {
    Muon& curr_muon = dynamic_cast<Muon&>(curr_particle);
    std::cout<<"    energy (GeV) = <<"<<curr_muon.get_detected_energy(5)<<" / "<<curr_muon.get_chamber_energy()<<std::endl;
  }
  else
  {
    std::cout<<"    energy (GeV) = 0 / 0";
  }
  std::cout<<std::endl;
  std::cout<<"  particle detected as : ";
  string guessed_particle = potential_particles[index+offset].front();
  std::cout<<guessed_particle;
  // If the guess is correct
  if(guessed_particle.find(curr_particle.get_name())!=string::npos) std::cout<<" (correct)";
  // cast to nucleons as they also have a nucleon type in addition to being called just nucleons
  else if(dynamic_cast<Nucleon*>(&curr_particle))
  {
    Nucleon& curr_nucleon = dynamic_cast<Nucleon&>(curr_particle);
    if(guessed_particle.find(curr_nucleon.get_nuc_type())!=string::npos) std::cout<<" (correct)";
  }
  else std::cout<<" (incorrect)";
  std::cout<<std::endl;
  
  

  std::cout<<std::endl;
  if(dynamic_cast<Nucleon*>(&curr_particle))
  {
    // Checks the number of decay products as there will be an offset 
    Nucleon& curr_nucleon = dynamic_cast<Nucleon&>(curr_particle);
    Tau& curr_tau = dynamic_cast<Tau&>(input_event->init_particle(index));

    offset += curr_tau.get_decay_products().size()-1; // Skips forward by the number of decay products, as there are a different number of start products compated to end products if a tau decays.
  }
}


// Fucntionality
void ColResultContainer::print()
{
  // Ugly as all hell print function to ensure that it is readable.
  std::cout<<"collision results for event : \""<<collision_name<<"\""<<std::endl;
  // For each particle
  input_event->print();

  int offset = 0;
  
  for(int i = 0; i+offset<input_event->get_num_particles(); i++)
  { 
    print_individual(i, offset);
  }
}
