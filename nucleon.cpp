#include<iostream>

#include"nucleon.h"

// Constructors
// Default
Nucleon::Nucleon()
{
  // Assume neutron if not told otherwise
  nuc_type = "neutron";
  true_energy = 939.565;
  rest_mass = 939.565;
  charge = 0;
  name = "nucleon";
  ;
}

// Parameterised
Nucleon::Nucleon(string con_nuc_type, double con_energy)
{
  // Case insensitivity, converting user input to lowercase.
  for(int i=0; i<con_nuc_type.length(); i++) {con_nuc_type[i] = tolower(con_nuc_type[i]);}
  // Checking for user input.
  if(con_nuc_type!="neutron" && con_nuc_type!="proton")
  {
    // Error message and default to neutron user doesn't enter a valid nucleon type.
    std::cout<<"Invalid nucleon type. Defaulting to neutron."<<std::endl;
    nuc_type="neutron";
    true_energy = 939.565;
    rest_mass = 939.565;
    charge = 0;
    name = "nucleon";
    cal_deposits;
  }
  else if(con_nuc_type=="proton")
  {
    nuc_type = con_nuc_type;
    true_energy = con_energy;
    rest_mass = 938.272;
    charge = 1;
    name = "nucleon";
    cal_deposits;
  }
  else
  {
    nuc_type = con_nuc_type;
    true_energy = con_energy;
    rest_mass = 939.565;
    charge = 0;
    name = "nucleon";
    cal_deposits;
  }
}
