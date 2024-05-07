#ifndef MUON_DETECTOR_H_INCLUDED
#define MUON_DETECTOR_H_INCLUDED

#include<vector>
#include<memory>

#include"sub_detector.h"

using std::vector;

class MuonDetector : public SubDetector
{
private:
  enum tracker_layers{INNER_MUON_LAYER=0, OUTER_MUON_LAYER=1};
  std::unique_ptr<vector<bool>> hit_layers; // Unique pointer to a vector of booleans.
  double percent_chance;
public:
  // Constructor
  // Default
  MuonDetector();
  // Parameterised
  MuonDetector(double con_efficiency, double con_chance);
  
  // Copy
  MuonDetector(const MuonDetector& copy_from);
  // Move
  MuonDetector(MuonDetector&& move_from);

  // Destructor, not needed.

  // Assignment
  // Copy
  MuonDetector& operator=(const MuonDetector& copy_from);
  // Move
  MuonDetector& operator=(MuonDetector&& move_from);
  
  // Getters
  vector<bool> get_hit_layers() const;
  bool get_hit_layer(int hit_layer) const;
  int get_percent_chance() const;

  // Setters
  void set_hit_layers(vector<bool> set_layers);
  void set_inner_muon_layer(bool set_inner);
  void set_outer_muon_layer(bool set_outer);
  void set_percent_chance(int set_percent_chance);

  // Functionality
  void interact(Particle& interacting_particle) override;
  void print() override;
  int get_num_hits();
  bool detection_status();
  void see_detection();
  void reset() override;
  void total_reset() override;
  
};



#endif