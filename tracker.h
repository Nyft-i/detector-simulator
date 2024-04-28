#ifndef TRACKER_H_INCLUDED
#define TRACKER_H_INCLUDED

#include"sub_detector.h"
#include"particle.h"

#include<vector>
#include<memory>

using std::vector;

class Tracker : public SubDetector
{
private:
  enum tracker_layers{INNER_PIXEL_LAYER=0, OUTER_PIXEL_LAYER=1, STRIP_LAYER=2};
  std::shared_ptr<vector<bool>> hit_layers; // Unique pointer to a vector of booleans.
  int percent_chance;
public:
  // Constructor
  // Default
  Tracker();
  // Parameterised
  Tracker(int con_percent_chance);
  
  // Copy
  Tracker(const Tracker& copy_from);
  // Move
  Tracker(Tracker&& move_from);

  // Destructor, not needed.

  // Assignment
  // Copy
  Tracker& operator=(const Tracker& copy_from);
  // Move
  Tracker& operator=(Tracker&& move_from);
  
  // Getters
  std::shared_ptr<vector<bool>>& get_hit_layers();
  bool get_hit_layer(int hit_layer);
  int get_percent_chance();

  // Setters
  void set_hit_layers(vector<bool> set_layers);
  void set_inner_pixel_layer(bool set_inner);
  void set_outer_pixel_layer(bool set_outer);
  void set_strip_layer(bool set_strip);
  void set_percent_chance(int set_percent_chance);

  // Functionality
  void interact(Particle& interacting_particle) override;
  void interact(CollisionEvent& col_event) override;
  void print() override;
  int get_num_hits();
  bool detection_status();
  void see_detection();
  void reset() override;
};

#endif