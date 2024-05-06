// PHYS30762 Programming in C++
// Project - Detector Simulation: Jade Salisbury

#include<iostream>
#include<memory>
#include<vector>
#include<string>
#include<ctime>
#include<chrono>
#include<list>

#include"detector.h"
#include"particle.h"
#include"depositor_particle.h"
#include"collision_event.h"
#include"photon.h"
#include"electron.h"
#include"muon.h"
#include"tau.h"
#include"neutrino.h"
#include"sub_detector.h"
#include"tracker.h"
#include"calorimeter.h"
#include"muon_detector.h"
#include"col_result_container.h"
#include"nucleon.h"

using std::shared_ptr;
using std::vector;
using std::string;
using std::list;
using std::unique_ptr;

unsigned long long get_ticks()
{
  // Current time in milliseconds for the seed. (https://stackoverflow.com/a/24959236)
  using namespace std::chrono;
  return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}

int Particle::numberer=0; // Starts the particle numbering from 0.
int main()
{
  // Seed random number generator
  std::srand(get_ticks()); // use current time as seed for random generator, ensures different answer each time.

  /*
  CollisionEvent photon_event("two photons, 1500GeV");
  photon_event.add_particle(std::move(std::make_unique<Photon>(75)));
  photon_event.add_particle(std::move(std::make_unique<Photon>(75)));
  */

  CollisionEvent background_event("neutron_photon_proton 1500GeV event");
  background_event.add_particle(std::move(std::make_unique<Nucleon>(500, "neutron")));
  background_event.add_particle(std::move(std::make_unique<Photon>(500)));
  background_event.add_particle(std::move(std::make_unique<Nucleon>(500, "proton")));
  

  
  CollisionEvent tau_event("tau, antitau, 1500GeV");
  tau_event.add_particle(std::move(std::make_unique<Tau>(750, 1, "hadronic")));
  tau_event.add_particle(std::move(std::make_unique<Tau>(750, -1, "electron")));
  

  /*
  shared_ptr<ColResultContainer> p_results1 = main_detector.collide(std::make_unique<CollisionEvent>(photon_event));
  p_results1->print();

  main_detector.reset();
  shared_ptr<ColResultContainer> p_results2 = main_detector.collide(std::make_unique<CollisionEvent>(background_event));
  p_results2->print();
  */

  Detector main_detector; // No arguments means that it will create a perfect detector
  main_detector.reset();
  shared_ptr<ColResultContainer> p_results3 = main_detector.collide(std::make_unique<CollisionEvent>(tau_event));
  std::cout<<"main : "<<main_detector.get_tracker().get_num_particles_detected()<<std::endl;
  p_results3->print();

  
  return 0;
}