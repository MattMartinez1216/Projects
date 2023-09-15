// File: Plane.h
// Author: Matthew Martinez
// Description: File contains class declaration and member functions for Plane class.

#ifndef Plane_H
#define Plane_H

#include<iostream>
#include <vector>
#include <string>

using std::string;

class Plane{
 public:
  Plane();
  
  Plane(int, int, string, int);
 
  ~Plane();

  int GetTime();
  
  int GetID();

  string GetAction();
  
  int GetPriority();

 private:
  int time;
  int ID;
  string action;
  int priority;
};
#endif