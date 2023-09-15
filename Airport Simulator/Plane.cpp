// File: Airplane.cpp
// Author: Matthew Martinez
// Description: Program contains all member functions for Plane class.

#include "Plane.h"

/*Description: Default constructor for Plane class.
  Parameters: N/A
  Returns: N/A
*/
Plane::Plane() {
  time = -1;
  ID = -1;
  action = "";
  priority = -1;
}

/*Description: Constructor for plane class with inputs for all members.
  Parameters: int arrivalTime, int planeID, string planeAction, int planePriority
  Returns: N/A
*/
Plane::Plane(int arrivalTime, int planeID, string planeAction, int planePriority) {
  time = arrivalTime;
  ID = planeID;
  action = planeAction;
  priority = planePriority;
}

/*Description: Destructor for Plane class.
  Parameters: N/A
  Returns: N/A
*/
Plane::~Plane() {}

/*Description: Function returns object Plane member variable time.
  Parameters: N/A
  Returns: int
*/
int Plane::GetTime() {
  return time;
}

/*Description: Function returns object Plane member variable ID.
  Parameters: N/A
  Returns: int
*/
int Plane::GetID() {
  return ID;
}

/*Description: Function returns object Plane member variable Action.
  Parameters: N/A
  Returns: string
*/
string Plane::GetAction() {
  return action;
}

/*Description: Function returns object Plane member variable Priority.
  Parameters: N/A
  Returns: int
*/
int Plane::GetPriority() {
  return priority;
}