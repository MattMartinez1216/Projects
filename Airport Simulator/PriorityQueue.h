// CSCI 311 - Spring 2023
// Priorityqueue.cpp
// Author: Matthew Martinez

#ifndef MinHeap_H
#define MinHeap_H

#include<iostream>
#include <vector>
#include "Plane.h"

using std::vector;

class MinHeap{
 public:
  MinHeap();

  bool empty();
  
  int size();

  void push(Plane);

  Plane pop();

  Plane peek();

  vector<Plane> planeVector;
};

#endif
