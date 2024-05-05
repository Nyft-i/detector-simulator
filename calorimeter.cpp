#include<iostream>

#include"calorimeter.h"
#include"depositor_particle.h"
#include"particle.h"

// Constructors
// Default
Calorimeter::Calorimeter()
{
  total_energy_detected = 0;
  cal_detection = std::make_unique<vector<double>>(4, 0);
}

// Parameterised
Calorimeter::Calorimeter(double con_efficiency):
SubDetector(con_efficiency)
{
  total_energy_detected = 0;
  cal_detection = std::make_unique<vector<double>>(4, 0);
}


// Copy
Calorimeter::Calorimeter(const Calorimeter& copy_from)
{
  total_energy_detected = copy_from.total_energy_detected;
  cal_detection = std::make_unique<vector<double>>(*copy_from.cal_detection);
}

// Move
Calorimeter::Calorimeter(Calorimeter&& move_from)
{
  total_energy_detected = move_from.total_energy_detected;
  cal_detection = std::move(move_from.cal_detection);

  // Set move_from to 0.
  move_from.total_energy_detected = 0;
  move_from.cal_detection = std::make_unique<vector<double>>(4, 0);
}

// Destructor, don't need

// Assignment
// Copy
Calorimeter& Calorimeter::operator=(const Calorimeter& copy_from)
{
  // Make sure we're not copying ourself.
  if(&copy_from==this) return *this;
  
  // Copy the data
  total_energy_detected = copy_from.total_energy_detected;
  cal_detection = std::make_unique<vector<double>>(*copy_from.cal_detection);
  
  return *this;
}

// Move
Calorimeter& Calorimeter::operator=(Calorimeter&& move_from)
{
  // Make sure we're not moving from ourself.
  if(&move_from == this) return *this;
  
  // Move the data
  total_energy_detected = move_from.total_energy_detected;
  cal_detection = std::move(move_from.cal_detection);
  
  // Set move_from to 0.
  move_from.total_energy_detected = 0;
  move_from.cal_detection = std::make_unique<vector<double>>(4, 0);
  
  return *this;
}

// Getters
vector<double> Calorimeter::get_cal_detection() const {return *cal_detection;}
double Calorimeter::get_EM_1() const {return cal_detection->at(0);}
double Calorimeter::get_EM_2() const {return cal_detection->at(1);}
double Calorimeter::get_HAD_1() const {return cal_detection->at(2);}
double Calorimeter::get_HAD_2() const {return cal_detection->at(3);}


// Setters
void Calorimeter::set_cal_detection(vector<double> set_cal_detection) {cal_detection = std::make_unique<vector<double>>(set_cal_detection);}
void Calorimeter::set_EM_1(double set_EM_1) {cal_detection->at(0) = set_EM_1;}
void Calorimeter::set_EM_2(double set_EM_2) {cal_detection->at(1) = set_EM_2;}
void Calorimeter::set_HAD_1(double set_HAD_1) {cal_detection->at(2) = set_HAD_1;}
void Calorimeter::set_HAD_2(double set_HAD_2) {cal_detection->at(3) = set_HAD_2;}

// Functionality
void Calorimeter::print()
{
  std::cout<<"\nprinting calorimeter..."<<std::endl;
  SubDetector::print();
  std::cout<<"EM_1 (GeV) : "<<cal_detection->at(0)<<std::endl;
  std::cout<<"EM_2 (Gev) : "<<cal_detection->at(1)<<std::endl;
  std::cout<<"HAD_1 (Gev) : "<<cal_detection->at(2)<<std::endl;
  std::cout<<"HAD_2 (Gev) : "<<cal_detection->at(3)<<std::endl;
}

void Calorimeter::interact(Particle& interacting_particle)
{
  // Calorimeter can only interact with DepositorParticles i.e. particles which have velues for each of the 4 layers.
  // Downcast the particle to a DepositorParticle if possible.
  if(dynamic_cast<DepositorParticle*>(&interacting_particle))
  {
    DepositorParticle& interacting_depositor_particle = dynamic_cast<DepositorParticle&>(interacting_particle);
    cal_detection->at(0) += interacting_depositor_particle.get_EM_1();
    cal_detection->at(1) += interacting_depositor_particle.get_EM_2();
    cal_detection->at(2) += interacting_depositor_particle.get_HAD_1();
    cal_detection->at(3) += interacting_depositor_particle.get_HAD_2();

    // Adds to the total energy detected.
    total_energy_detected += interacting_depositor_particle.get_true_energy();
  }
}

void Calorimeter::reset()
{
  total_energy_detected = 0;
  cal_detection = std::make_unique<vector<double>>(4, 0);
}

bool Calorimeter::EM_detection_status() const 
{
  // Boolean for if there is 
  if(cal_detection->at(0) > 0 || cal_detection->at(1) > 0) return true;
  else return false;
}

bool Calorimeter::HAD_detection_status() const 
{
  if(cal_detection->at(2) > 0 || cal_detection->at(3) > 0) return true;
  else return false;
}