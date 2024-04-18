#include"photon.h"

// Constructors
// Default

// Parameterised
Photon::Photon(double con_energy)
{
  true_energy = con_energy;
  rest_mass = 0;
  charge = 0;
  name = "photon";
}

// Deep Copy Constructor
Photon::Photon(const Photon& copy_from)
{
  true_energy = copy_from.true_energy;
  rest_mass = copy_from.rest_mass;
  charge = copy_from.charge;
  name = copy_from.name;
  cal_deposits = copy_from.cal_deposits;
}

// Move Constructor
Photon::Photon(Photon&& move_from)
{
  true_energy = move_from.true_energy;
  rest_mass = move_from.rest_mass;
  charge = move_from.charge;
  name = std::move(move_from.name);
  cal_deposits = std::move(move_from.cal_deposits);
  
  // Reset the moved-from object
  move_from.true_energy = 0;
  move_from.rest_mass = 0;
  move_from.charge = 0;
  move_from.name = "";
}


// Destructor


// Assignment
// Deep copy assignment
Photon& Photon::operator=(const Photon& copy_from)
{
  // Make sure we're not copying ourself.
  if(&copy_from==this) return *this;
  
  // Copy the data
  true_energy = copy_from.true_energy;
  rest_mass = copy_from.rest_mass;
  charge = copy_from.charge;
  name = copy_from.name;
  cal_deposits = copy_from.cal_deposits;
  
  return *this;
}
// Move assignment
Photon& Photon::operator=(Photon&& move_from)
{
  // Make sure we're not moving from ourself.
  if(&move_from == this) return *this;
  
  // Move the data
  true_energy = move_from.true_energy;
  rest_mass = move_from.rest_mass;
  charge = move_from.charge;
  name = std::move(move_from.name);
  cal_deposits = std::move(move_from.cal_deposits);
  
  // Reset the moved-from object
  move_from.true_energy = 0;
  move_from.rest_mass = 0;
  move_from.charge = 0;
  move_from.name = "moved particle";
  
  return *this;
}