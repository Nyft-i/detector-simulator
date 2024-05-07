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

  // Instantiating a main detector
  Detector main_detector(0.8, 0.8, 0.8, 0.7, 0.7); // No arguments means that it will create a perfect detector, this has an energy efficiency of 0.8 for all detectors and a chance of tracker and muon detections of 0.7
  // The detector is built off of random number generations
  // A 100% efficient detector can be instantiated by using `Detector main_detector(1, 1, 1, 1, 1);` or `Detector main_detector;`
  // Note: a 100% efficient detector will still not be able to detect neutrinos, and will therefore not detect 100% of the input energy, just all the available energy.
  
  // Rather than creating vectors of particles, I have defined a CollisionEvent which contains a list of particles and also the total energy of the event.
  // add_particle is used to add to the event and then adjust() is used to double check that the energies add up, if they do not then they are adjusted to match the ratio of true energies.
  // __ Event 1 __
  CollisionEvent photon_event("two photons, 125GeV", 125);
  photon_event.add_particle(std::move(std::make_unique<Photon>(65)));
  photon_event.add_particle(std::move(std::make_unique<Photon>(60)));
  photon_event.adjust();

  // __ Event 2 __
  CollisionEvent background_event("neutron_photon_proton 1500GeV event", 1500);
  background_event.add_particle(std::move(std::make_unique<Nucleon>(700, "neutron")));
  background_event.add_particle(std::move(std::make_unique<Photon>(100)));
  background_event.add_particle(std::move(std::make_unique<Nucleon>(600, "proton")));
  background_event.adjust();

  // __ Event 3 __
  CollisionEvent tau_event("tau, antitau, 1500GeV", 1500);
  tau_event.add_particle(std::move(std::make_unique<Tau>(20, 1, "hadronic"))); // Different value that doesnt add up to 1500 to prove that it will adjust
  tau_event.add_particle(std::move(std::make_unique<Tau>(20, -1, "muon"))); // Using a muonic decay to show that the muon_detector works.
  tau_event.adjust();

  // __ Event 4 __
  CollisionEvent z_decay("proton, neutrino, antineutrino, 1500GeV", 1500);
  z_decay.add_particle(std::move(std::make_unique<Nucleon>(1000, "proton"))); // Proton nucleon
  z_decay.add_particle(std::move(std::make_unique<Neutrino>(250, 1, 1, false)));
  z_decay.add_particle(std::move(std::make_unique<Neutrino>(250, 1, -1, false))); // Rubric doesn't specify what flavour of neutrinos- going with electron

  // __ Event 1 __
  // Firstly print all the input particles, taus will already have decayed.
  photon_event.print();
  // Collide ! & store the results in a Collision result container, ColResultContainer
  std::cout<<"here at least"<<std::endl;
  shared_ptr<ColResultContainer> p_results1 = main_detector.collide(std::make_unique<CollisionEvent>(photon_event));
  // Print the collision result
  p_results1->print();
  // Completely reset the detector.
  main_detector.total_reset();

  // Now do the same for every other event
  // __ Event 2 __
  background_event.print();
  shared_ptr<ColResultContainer> p_results2 = main_detector.collide(std::make_unique<CollisionEvent>(background_event));
  p_results2->print();
  main_detector.total_reset();
  
  // __ Event 3 __
  tau_event.print();
  shared_ptr<ColResultContainer> p_results3 = main_detector.collide(std::make_unique<CollisionEvent>(tau_event));
  p_results3->print();
  main_detector.total_reset();

  // __ Event 4 __
  z_decay.print();
  shared_ptr<ColResultContainer> p_results4 = main_detector.collide(std::make_unique<CollisionEvent>(z_decay));
  p_results4->print();
  main_detector.total_reset();

  // Information about all the events.
  int total_tracker_particles = p_results1->get_tracker_particles() + p_results2->get_tracker_particles() + p_results3->get_tracker_particles() + p_results4->get_tracker_particles();
  double total_tracker_energy = p_results1->get_tracker_energy() + p_results2->get_tracker_energy() + p_results3->get_tracker_energy() + p_results4->get_tracker_energy();

  int total_calorimeter_particles = p_results1->get_calorimeter_particles() + p_results2->get_calorimeter_particles() + p_results3->get_calorimeter_particles() + p_results4->get_calorimeter_particles();
  double total_calorimeter_energy = p_results1->get_calorimeter_energy() + p_results2->get_calorimeter_energy() + p_results3->get_calorimeter_energy() + p_results4->get_calorimeter_energy();

  int total_muon_particles = p_results1->get_muon_particles() + p_results2->get_muon_particles() + p_results3->get_muon_particles() + p_results4->get_muon_particles();
  double total_muon_energy = p_results1->get_muon_energy() + p_results2->get_muon_energy() + p_results3->get_muon_energy() + p_results4->get_muon_energy();

  int total_correct_guesses = p_results1->get_correct_guesses() + p_results2->get_correct_guesses() + p_results3->get_correct_guesses() + p_results4->get_correct_guesses();
  int total_particles = p_results1->get_input_event().get_num_particles() + p_results2->get_input_event().get_num_particles() + p_results3->get_input_event().get_num_particles() + p_results4->get_input_event().get_num_particles();
  double total_detected_energy = p_results1->get_total_energy_detected() + p_results2->get_total_energy_detected() + p_results3->get_total_energy_detected() + p_results4->get_total_energy_detected();
  double total_input_energy = p_results1->get_input_energy() + p_results2->get_input_energy() + p_results3->get_input_energy() + p_results4->get_input_energy();

  std::cout<<"__ ALL EVENTS __"<<std::endl;
  std::cout<<"summary after all events:"<<std::endl;
  std::cout<<"  total number of particles detected by tracker accross all events : "<<total_tracker_particles<<", total energy detected by tracker accross all events (GeV) : "<<total_tracker_energy<<std::endl;
  std::cout<<"  total number of particles detected by calorimeter accross all events : "<<total_calorimeter_particles<<", total energy detected by calorimeter accross all events (GeV) : "<<total_calorimeter_energy<<std::endl;
  std::cout<<"  total number of muons detected accross all events : "<<total_muon_particles<<", total energy detected by muon detector accross all events (GeV) : "<<total_muon_energy<<std::endl;
  std::cout<<"  detector identification efficiency : "<<total_correct_guesses*100/total_particles<<"% ("<<total_correct_guesses<<"/"<<total_particles<<")"<<std::endl;
  std::cout<<"  energy detected by detectors : "<<total_detected_energy*100/total_input_energy<<"% ("<<total_detected_energy<<"/"<<total_input_energy<<")"<<std::endl;
  
  std::cout<<"__ END __"<<std::endl;
  
  return 0;
}