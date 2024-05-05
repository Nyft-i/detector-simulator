#include<iostream>
#include<memory>
#include<vector>
#include<string>
#include<list>
#include<algorithm>

#include"detector.h"
#include"tracker.h"
#include"calorimeter.h"
#include"muon_detector.h"
#include"collision_event.h"
#include"col_result_container.h"

using std::vector;
using std::string;
using std::list;

// Constructors
// Default

// Parameterised
Detector::Detector(double tracker_efficiency, double calorimeter_efficiency, double muon_efficiency, double con_tracker_percent_chance, double con_muon_percent_chance)
{
  tracker = std::make_unique<Tracker>(tracker_efficiency, con_tracker_percent_chance);
  calorimeter = std::make_unique<Calorimeter>(calorimeter_efficiency);
  muon_detector = std::make_unique<MuonDetector>(muon_efficiency, con_muon_percent_chance);

  current_col = nullptr;
  col_elem = 0;
}

// Copy
Detector::Detector(const Detector& copy_from)
{
  tracker = std::make_unique<Tracker>(*copy_from.tracker);
  calorimeter = std::make_unique<Calorimeter>(*copy_from.calorimeter);  
  muon_detector = std::make_unique<MuonDetector>(*copy_from.muon_detector);

  current_col = std::make_unique<CollisionEvent>(*copy_from.current_col);
  col_elem = copy_from.col_elem;

  current_col = nullptr;
  col_elem = 0;
}

// Move
Detector::Detector(Detector&& move_from)
{
  tracker = std::move(move_from.tracker);
  calorimeter = std::move(move_from.calorimeter);
  muon_detector = std::move(move_from.muon_detector);

  current_col = std::move(move_from.current_col);
  col_elem = move_from.col_elem;

  // Set move_from to 0.
  tracker = nullptr;
  calorimeter = nullptr;
  muon_detector = nullptr;
  current_col = nullptr;
  col_elem = 0;
}

// Destructor

// Assignment
// Copy
Detector& Detector::operator=(const Detector& copy_from)
{
  // Self assignment
  if(this == &copy_from) return *this;

  tracker = std::make_unique<Tracker>(*copy_from.tracker);
  calorimeter = std::make_unique<Calorimeter>(*copy_from.calorimeter);
  muon_detector = std::make_unique<MuonDetector>(*copy_from.muon_detector);
  
  current_col = std::make_unique<CollisionEvent>(*copy_from.current_col);
  col_elem = copy_from.col_elem;

  return *this;
}

// Move
Detector& Detector::operator=(Detector&& move_from)
{
  // Self assignment
  if(this == &move_from) return *this;

  tracker = std::move(move_from.tracker);
  calorimeter = std::move(move_from.calorimeter);
  muon_detector = std::move(move_from.muon_detector);

  current_col = std::move(move_from.current_col);
  col_elem = move_from.col_elem;

  // Set move_from to 0.
  tracker = nullptr;
  calorimeter = nullptr;
  muon_detector = nullptr;
  current_col = nullptr;
  col_elem = 0;

  return *this;
}

// Getters
Tracker& Detector::get_tracker() const {return *tracker;}
Calorimeter& Detector::get_calorimeter() const {return *calorimeter;}
MuonDetector& Detector::get_muon_detector() const {return *muon_detector;}
vector<bool> Detector::get_detections() const 
{
  vector<bool> detections;
  // Vector of booleans for all the possible types of detections. Will only be accurate in the scenario that the detector is perfect.
  detections.push_back(tracker->detection_status());
  detections.push_back(calorimeter->EM_detection_status());
  detections.push_back(calorimeter->HAD_detection_status());
  detections.push_back(muon_detector->detection_status());
  return detections;
}

// Functionality
void Detector::interact(Particle& interacting_particle)
{
  reset();
  tracker->interact(interacting_particle);
  calorimeter->interact(interacting_particle);
  muon_detector->interact(interacting_particle);
}

void Detector::start_collision(unique_ptr<CollisionEvent> p_col_event)
{
  setup_collision(std::move(p_col_event));
  step_collision();
}

void Detector::setup_collision(unique_ptr<CollisionEvent> p_col_event)
{
  current_col = std::move(p_col_event);
  col_elem = 0;
}

void Detector::step_collision()
{
  reset();
  interact((*current_col)[col_elem]);
  col_elem++;
}

void Detector::see_detections()
{
  // Uses the information available to guess the particle.
  // Tracker
  std::cout<<"\n\n__ DETECTOR STATUS __"<<std::endl;

  if(tracker->detection_status()) std::cout<<"tracker detection!"<<std::endl;
  else std::cout<<"no tracker detection"<<std::endl;

  // Calorimeter
  calorimeter->print();

  // Muon Detector
  if(muon_detector->detection_status()) std::cout<<"muon detector detection!"<<std::endl;
  else std::cout<<"no muon detector detection"<<std::endl;
  muon_detector->print();
}

void Detector::reset()
{
  tracker->reset();
  calorimeter->reset();
  muon_detector->reset();
}

void Detector::sneak_look()
{
  // Function that tells us everything about the sub-detectors in a way that shouldn't normally be visible for testing purposes.
  std::cout<<"\n\n__ SUB-DETECTOR STATUSES __"<<std::endl;
  tracker->print();
  calorimeter->print();
  muon_detector->print();
  int total_energy = tracker->get_total_energy_detected() + calorimeter->get_total_energy_detected(); // Muon detector energy is going to be the same as tracker energy for muons, so will accidentally double up the energy.
  std::cout<<"\ntotal energy detected, all sub-detectors (GeV) : "<<total_energy<<std::endl;
}

list<string> Detector::guess_particle()
{
  // Uses the information from get_detections to guess the particle.
  vector<bool> detections = get_detections();
  enum detection_type {TRACKER=0, CAL_EM=1, CAL_HAD=2, MUON=3};
  list<string> possible_particles = {"muon/antimuon", "electron/positron", "proton", "neutron", "photon", "neutrino/antineutrino"}; // No Tau present as they decay too fast
  

  // Muon detection, unlike the calorimeter, if a detection isn't found then we cannot rule out muons, as their detection is % chance
  if(detections[MUON]) // Must be a muon
  {possible_particles.remove_if([](string const & x) {return x != "muon/antimuon";});}
  if(!detections[MUON]) // Must NOT be a muon
  {possible_particles.remove_if([](string const & x) {return x == "muon/antimuon";});}

  // Tracker detection
  if(detections[TRACKER]) // must be charged
  {possible_particles.remove_if([](string const & x) {return x != "muon/antimuon" && x != "electron/positron" && x != "tau/antitau" && x != "proton";});}
  if(!detections[TRACKER]) // must NOT be charged
  {possible_particles.remove_if([](string const & x) {return x == "muon/antimuon" || x == "electron/positron" || x == "tau/antitau" || x == "proton";});}

  // Calorimeter detection (EM)
  if(detections[CAL_EM]) // must be anything but a neutrino or muon. Muon's don't leave energy in the EM calorimeter.
  {possible_particles.remove_if([](string const & x) {return x == "neutrino/antineutrino" || x =="muon/antimuon";});}
  if(!detections[CAL_EM]) // must be a neutrino or muon
  {possible_particles.remove_if([](string const & x) {return x != "neutrino/antineutrino" && x !="muon/antimuon";});}

  // Calorimeter detection (HAD)
  if(detections[CAL_HAD]) // Must be a proton or a neutron
  {possible_particles.remove_if([](string const & x) {return x != "proton" && x != "neutron";});}
  if(!detections[CAL_HAD]) // Must be a NOT proton or a neutron
  {possible_particles.remove_if([](string const & x) {return x == "proton" || x == "neutron";});}


  return possible_particles;
}

shared_ptr<ColResultContainer> Detector::collide(unique_ptr<CollisionEvent> p_col_event)
{
  // Transfers ownership to the caller of a unique pointer to a container for all the known information about a potential collision event.
  // Initial setup
  setup_collision(std::move(p_col_event));
  enum detection_type {TRACKER=0, CAL_EM=1, CAL_HAD=2, MUON=3};
  vector<list<string>> potential_particles;
  double input_energy = current_col->get_collision_energy();
  string collision_name = current_col->get_event_name();
  double detected_energy = 0;

  // For every particle (note that tau's will automatically decay into their decay products when they are added to the collision event.)
  for(int i = 0; i<current_col->get_num_particles(); i++)
  {
    step_collision();
    potential_particles.push_back(guess_particle());
    
    vector<bool> detections = get_detections();

    // Code stops doubling up energies for particles which have imparted their true energy onto tracker/muon detector as well as the calorimeter.
    // This is definitely not the physics way to do this but 
    if(!detections[CAL_EM] && !detections[CAL_HAD]) detected_energy += tracker->get_total_energy_detected() + muon_detector->get_total_energy_detected();
    else detected_energy += calorimeter -> get_total_energy_detected();

    // sneak_look();
  }

  ColResultContainer results(collision_name, input_energy, detected_energy, potential_particles);
  return std::make_shared<ColResultContainer>(results); // Transferral of ownership/joinery of ownership
}