#include<iostream>
#include<vector>
#include<ctime>
#include<chrono>

#include"muon.h"

using std::vector;

// Constructors
// Default
Muon::Muon()
{
  set_true_energy(10);
  rest_mass = 0.10566;
  pap_status = 1;
  charge = -1;
  name = "muon";
  interacted_with_muon_detector = false;
}

// Parameterised
Muon::Muon(double con_energy, int con_pap)
{
  set_true_energy(con_energy);
  rest_mass = 0.10566;
  pap_status = con_pap;
  if(pap_status==-1)
  {
    charge = 1;
    name = "antimuon";
  }
  else  // Defaults to muon if pap_status is invalid
  {
    charge = -1;
    name = "muon";
  }
  interacted_with_muon_detector = false;
}

// Deep Copy Constructor
Muon::Muon(const Muon& copy_from)
{
  true_energy = copy_from.true_energy;
  rest_mass = copy_from.rest_mass;
  charge = copy_from.charge;
  name = copy_from.name;
  pap_status = copy_from.pap_status;
  from_tau = copy_from.from_tau;
  tracker_energy = copy_from.tracker_energy;
  chamber_energy = copy_from.chamber_energy;
  interacted_with_muon_detector = copy_from.interacted_with_muon_detector;
  detected_energies = std::make_unique<vector<double>>(*copy_from.detected_energies);
}

// Move Constructor
Muon::Muon(Muon&& move_from)
{
  true_energy = move_from.true_energy;
  rest_mass = move_from.rest_mass;
  charge = move_from.charge;
  name = std::move(move_from.name);
  pap_status = move_from.pap_status;
  from_tau = move_from.from_tau;
  tracker_energy = move_from.tracker_energy;
  chamber_energy = move_from.chamber_energy;
  interacted_with_muon_detector = move_from.interacted_with_muon_detector;
  detected_energies = std::move(move_from.detected_energies);

  // Set attributes of move_from to nothing.
  move_from.true_energy = 0;
  move_from.rest_mass = 0;
  move_from.charge = 0;
  move_from.pap_status = 0;
  move_from.from_tau = false;
  move_from.name = "";
  move_from.tracker_energy = 0;
  move_from.chamber_energy = 0;
  move_from.interacted_with_muon_detector = false;
  move_from.detected_energies = nullptr;
}


// Destructor


// Assignment
// Deep copy assignment
Muon& Muon::operator=(const Muon& copy_from)
{
  // Make sure we're not copying ourself.
  if(&copy_from==this) return *this;
  
  // Copy the data
  true_energy = copy_from.true_energy;
  rest_mass = copy_from.rest_mass;
  charge = copy_from.charge;
  name = copy_from.name;
  pap_status = copy_from.pap_status;
  from_tau = copy_from.from_tau;
  tracker_energy = copy_from.tracker_energy;
  chamber_energy = copy_from.chamber_energy;
  interacted_with_muon_detector = copy_from.interacted_with_muon_detector;
  detected_energies = std::make_unique<vector<double>>(*copy_from.detected_energies);

  return *this;
}
// Move assignment
Muon& Muon::operator=(Muon&& move_from)
{
  // Make sure we're not moving from ourself.
  if(&move_from == this) return *this;
  
  // Move the data
  true_energy = move_from.true_energy;
  rest_mass = move_from.rest_mass;
  charge = move_from.charge;
  name = std::move(move_from.name);
  pap_status = move_from.pap_status;
  from_tau = move_from.from_tau;  
  tracker_energy = move_from.tracker_energy; 
  chamber_energy = move_from.chamber_energy;
  interacted_with_muon_detector = move_from.interacted_with_muon_detector;
  detected_energies = std::move(move_from.detected_energies);
  
  // Set attributes of move_from to nothing.
  move_from.true_energy = 0;
  move_from.rest_mass = 0;
  move_from.charge = 0;
  pap_status = 0;
  move_from.from_tau = false;
  tracker_energy = 0;
  chamber_energy = 0;
  move_from.name = "moved particle";
  move_from.interacted_with_muon_detector = false;
  move_from.detected_energies = nullptr;
  
  return *this;
}

// Getters
double Muon::get_tracker_energy() const {return tracker_energy;}
double Muon::get_chamber_energy() const {return chamber_energy;}
bool Muon::get_interacted_with_detector() const {return interacted_with_muon_detector;}

// Setters
void Muon::set_tracker_energy(double set_tracker_energy) {tracker_energy = set_tracker_energy;}
void Muon::set_chamber_energy(double set_chamber_energy) {chamber_energy = set_chamber_energy;}
void Muon::set_true_energy(double set_energy) 
{
  // Based on the calorimeter code, very similar but no need for loops for only 2 elements.
  // Sets the true energy using the base class method. We benefit from the existing verification in Particle.
  Particle::set_true_energy(set_energy);

  // When the user tries to set the true energy, it is split randomly between the tracker and chamber deposits.
  vector<double> random_ratio;

  random_ratio.push_back(std::rand()); // Can be an int between 0 and RAND_MAX which is >32767
  random_ratio.push_back(std::rand()); // Can be an int between 0 and RAND_MAX which is >32767

  double total = random_ratio[0]+random_ratio[1];
  // Divides each number by the total sum of all random numbers, then it will be out of 1 instead of a random number.
  random_ratio[0] = random_ratio[0]/total;
  random_ratio[1] = random_ratio[1]/total;
  
  tracker_energy = true_energy*random_ratio[0];
  chamber_energy = true_energy*random_ratio[1];
}
void Muon::set_interacted_with_detector(bool set_interacted) {interacted_with_muon_detector = set_interacted;}

// Functionality
void Muon::print()
{
  std::cout<<"\nparticle is : "<<name<<std::endl;
  Particle::print();
  std::cout<<"tracker energy (GeV) : "<<tracker_energy<<std::endl;
  std::cout<<"chamber energy (GeV) : "<<chamber_energy<<std::endl;
}