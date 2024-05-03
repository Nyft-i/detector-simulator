#ifndef CALORIMETER_H_INCLUDED
#define CALORIMETER_H_INCLUDED

#include<vector>
#include<memory>

#include"sub_detector.h"

using std::vector;
using std::unique_ptr;

class Calorimeter : public SubDetector
{
private:
  unique_ptr<vector<double>> cal_detection;
public:
  // Constructors
  // Default
  Calorimeter();
  // Parameterised
  Calorimeter(double con_efficiency);
  // Copy
  Calorimeter(const Calorimeter& other);
  // Move
  Calorimeter(Calorimeter&& other);
  
  // Destructor, not needed.
  
  // Assignment
  // Copy
  Calorimeter& operator=(const Calorimeter& other);
  // Move
  Calorimeter& operator=(Calorimeter&& other);

  // Getters
  vector<double> get_cal_detection() const;
  double get_EM_1() const;
  double get_EM_2() const;  
  double get_HAD_1() const;
  double get_HAD_2() const;
  
  // Setters
  void set_cal_detection(vector<double> set_cal_detection);
  void set_EM_1(double set_EM_1);
  void set_EM_2(double set_EM_2);
  void set_HAD_1(double set_HAD_1);
  void set_HAD_2(double set_HAD_2);

  // Functionality
  void interact(Particle& interacting_particle) override;
  void reset() override;
  void print() override;
};

#endif