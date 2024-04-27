#ifndef COLLISION_EVENT_H_INCLUDED
#define COLLISION_EVENT_H_INCLUDED

#include<vector>

class CollisionEvent
{
private:
  
public:
  // Constructor
  // Default
  CollisionEvent() = default;
  // Parameterised
  
  // Copy
  CollisionEvent(const CollisionEvent& copy_from);
  // Move
  CollisionEvent(CollisionEvent&& move_from);

  // Destructor, not needed.

  // Assignment
  // Copy
  CollisionEvent& operator=(const CollisionEvent& copy_from);
  // Move
  CollisionEvent& operator=(CollisionEvent&& move_from);
  
  // Getters

  // Setters

  // Functionality

};

#endif
