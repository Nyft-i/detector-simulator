#ifndef DETECTOR_H_INCLUDED
#define DETECTOR_H_INCLUDED

#include<memory>
#include<vector>
#include<string>
#include<list>

#include"tracker.h"
#include"calorimeter.h"
#include"collision_event.h"
#include"muon_detector.h"

using std::vector;
using std::string;
using std::list;
using std::shared_ptr;
using std::unique_ptr;

class Detector
{
private:
  unique_ptr<Tracker> tracker;
  unique_ptr<Calorimeter> calorimeter;
  unique_ptr<MuonDetector> muon_detector;
  unique_ptr<CollisionEvent> current_col;
  double col_elem;
public:
  // Constructor
  // Default
  // Parameterised
  Detector(double tracker_efficiency=1, double calorimeter_efficiency=1, double muon_efficiency=1, double con_tracker_percent_chance=1, double con_muon_percent_chance=1);
  // Copy
  Detector(const Detector& copy_from);
  // Move
  Detector(Detector&& move_from);

  // Destructor

  // Assignment
  // Copy
  Detector& operator=(const Detector& copy_from);
  // Move
  Detector& operator=(Detector&& move_from);

  // Getters
  Tracker& get_tracker() const;
  Calorimeter& get_calorimeter() const;
  MuonDetector& get_muon_detector() const;
  vector<bool> get_detections() const;
  
  // Setters
  void set_tracker(shared_ptr<Tracker> set_tracker);

  // Functionality
  void interact(Particle& interacting_particle);
  void start_collision(unique_ptr<CollisionEvent> p_col_event);
  void step_collision();
  void see_detections();
  void reset();
  void sneak_look();
  list<string> guess_particle();
};

#endif