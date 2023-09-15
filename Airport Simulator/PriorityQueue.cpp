// CSCI 311 - Spring 2023
// PriorityQueue.cpp
// Author: Matthew Martinez

#include "PriorityQueue.h"
#include "Plane.h"

/*Description: Default constructor for MinHeap class.
  Parameters: N/A
  Returns: N/A
*/
MinHeap::MinHeap(){
  planeVector.resize(0);
}

/*Description: Function determines if MinHeap is empty. Returns true
  if true, else returns false.
  Parameters: N/A
  Returns: bool
*/
bool MinHeap::empty() {
  if (planeVector.size() == 0) {
    return true;
  }

  return false;
}

/*Description: Function returns object MinHeap member variable size.
  Parameters: N/A
  Returns: int
*/
int MinHeap::size() {
  return planeVector.size();
}

/*Description: Function adds parameter Plane to end of MinHeap.
  Parameters: Plane p
  Returns: N/A
*/
void MinHeap::push(Plane p) {
  planeVector.push_back(p);
}

/*Description: Function removes and returns first Plane object in MinHeap.
  Parameters: N/A
  Returns: Plane
*/
Plane MinHeap::pop() {
  Plane nextPlane = planeVector[0];
  if (planeVector.size() >= 1) {
    planeVector[0] = planeVector[planeVector.size() - 1];
    planeVector.pop_back();
  }
  
  return nextPlane;
}

/*Description: Function returns first Plane object in MinHeap.
  Parameters: N/A
  Returns: Plane
*/
Plane MinHeap::peek() {
  return planeVector[0];
}



