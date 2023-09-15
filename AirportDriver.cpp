// File: AirportDriver.cpp
// Author: Matthew Martinez
// Description: Program uses a priority queue to simulate an airport. Program manages scheduled incoming
// and outgoing planes based on their priority.


#include <iostream>
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::vector;
using std::endl;
using std::string;
// Define class Plane
#ifndef Plane_H
#define Plane_H

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



#ifndef MinHeap_H
#define MinHeap_H
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
#endif

/*Description: Function outputs all member functions of parameter Plane.
  Parameters: Plane Plane
  Returns: N/A
*/
void outputPlaneData(Plane Plane) {
  cout << "\t\t" << Plane.GetTime();
  cout << " " << Plane.GetID();
  cout << " " << Plane.GetAction();
  cout << " " << Plane.GetPriority() << endl;
}

/*Description: Function turns vector of Plane objects into a 
  MinHeap based on Plane member variable time if only potential 
  out of place value is at position i in vector.
  Parameters: vector<Plane> &v, int i, int planeVectorSize
  Returns: N/A
*/
void minHeapifyTime(vector<Plane> &v, int i, int planeVectorSize) {
  int left = 2*i+1;
  int right = 2*i+2;
  int minPriority = i;

  // Determine if left child of node [i] has greater priority than node [i]
  if (left < planeVectorSize && v[left].GetTime() <= v[i].GetTime()) {
    if (v[left].GetTime() == v[i].GetTime()) {
      if (v[left].GetPriority() < v[i].GetPriority()) {
        minPriority = left; 
      } else if (v[left].GetPriority() == v[i].GetPriority()) {
          if (v[left].GetID() < v[i].GetID()) {
            minPriority = left;
          }
        }
    } else { 
        minPriority = left; 
      }
  }
  
  // Determine if right child of node [i] has greater priority than node [minPriority]
  if (right < planeVectorSize && v[right].GetTime() <= v[minPriority].GetTime()){ 
    if (v[right].GetTime() == v[minPriority].GetTime()) {
      if (v[right].GetPriority() < v[minPriority].GetPriority()) {
        minPriority = right; 
      } else if (v[right].GetPriority() == v[minPriority].GetPriority()) {
          if (v[right].GetID() < v[i].GetID()) {
            minPriority = right;
          }
        }
    } else { 
        minPriority = right; 
      }
  }
  
  // swap node i with child node [minPriority] if node [i] does not have greater 
  // priority than one of its children
  if (minPriority != i){
    Plane temp = v[i];
    v[i] = v[minPriority];
    v[minPriority] = temp;
    minHeapifyTime(v, minPriority, v.size());
  }
}

/*Description: Function turns vector of Plane objects into a 
  MinHeap based on Plane member variable priority if only potential 
  out of place value is at position i in vector.
  Parameters: vector<Plane> &v, int i, int planeVectorSize
  Returns: N/A
*/
void minHeapifyPriority(vector<Plane> &v, int i, int planeVectorSize) {
  int left = 2*i+1;
  int right = 2*i+2;
  int minPriority = i;

  // Determine if left child of node [i] has greater priority than node [i]
  if (left < planeVectorSize && v[left].GetPriority() <= v[i].GetPriority()) {
    if (v[left].GetPriority() == v[i].GetPriority()) {
      if (v[left].GetID() < v[i].GetID()) {
        minPriority = left; 
      } else if (v[left].GetID() == v[i].GetID()) {
          if (v[left].GetTime() > v[i].GetTime()) {
            minPriority = left;
          }
        }
    } else { 
        minPriority = left; 
      }
  }
  
  // Determine if right child of node [i] has greater priority than node [minPriority]
  if (right < planeVectorSize && v[right].GetPriority() <= v[minPriority].GetPriority()){ 
    if (v[right].GetPriority() == v[minPriority].GetPriority()) {
      if (v[right].GetID() < v[minPriority].GetID()) {
        minPriority = right; 
      } else if (v[right].GetID() == v[minPriority].GetID()) {
          if (v[right].GetTime() > v[i].GetTime()) {
            minPriority = right;
          }
        }
    } else { 
        minPriority = right; 
      }
  }
  
  // swap node i with child node [minPriority] if node [i] does not have greater 
  // priority than one of its children
  if (minPriority != i){
    Plane temp = v[i];
    v[i] = v[minPriority];
    v[minPriority] = temp;
    minHeapifyPriority(v, minPriority, v.size());
  }
}

/*Description: Function turns vector of Plane objects into a 
  MinHeap based on Plane member variable time.
  Parameters: vector<Plane> &v
  Returns: N/A
*/
void constructMinHeapTime(vector<Plane> &v){
  if (v.size() > 1) {
    int lastNode = (v.size()/2) - 1;
    for (int i = lastNode; i >= 0; i--) {
      minHeapifyTime(v,i,v.size());
    }
  }
}

/*Description: Function turns vector of Plane objects into a 
  MinHeap based on Plane member variable priority.
  Parameters: vector<Plane> &v
  Returns: N/A
*/
void constructMinHeapPriority(vector<Plane> &v){
  if (v.size() > 1) {
    int lastNode = (v.size()/2) - 1;
    for (int i = lastNode; i >= 0; i--) {
      minHeapifyPriority(v,i,v.size());
    } 
  }
}



int main(){
  int numOfPlanes, makePlanes, timeStep = 0, currentBaseTime;
  string time, ID, action, priority;
  Plane runwayAPlane, runwayBPlane;

  cin >> numOfPlanes;
  makePlanes = numOfPlanes;
  vector<Plane> InputOrderPlanes, OutputOrderPlanes;
  MinHeap arrivingPlanes = MinHeap(), departingPlanes = MinHeap();

  // Take user input for all plane member variables
  while(makePlanes > 0) {
    cin >> time >> ID >> action >> priority;
    InputOrderPlanes.insert(InputOrderPlanes.begin(),(Plane(stoi(time),stoi(ID),action,stoi(priority))));
    makePlanes--;
  }

  timeStep = InputOrderPlanes[InputOrderPlanes.size() - 1].GetTime();
  currentBaseTime = timeStep;

  // While loop to iterate through all planes and place them in proper runways at correct time.
  while (InputOrderPlanes.size() != 0 || arrivingPlanes.size() != 0 || departingPlanes.size() != 0) {
    // Check to see if timeStep needs to be reset.
    if (OutputOrderPlanes.size() == 0 && InputOrderPlanes.size() > 0) {
      timeStep = InputOrderPlanes[InputOrderPlanes.size() - 1].GetTime();
      currentBaseTime = timeStep;
    }

    
    Plane planeToAddToHeap;
    if (InputOrderPlanes.size() > 0) {
      planeToAddToHeap = InputOrderPlanes[InputOrderPlanes.size()-1];
    }
    
    // Add all planes for a given timeStep to their respective runways.
    while (planeToAddToHeap.GetTime() == timeStep) {
      if (planeToAddToHeap.GetAction() == "arriving") {
        arrivingPlanes.push(planeToAddToHeap);
      } else if (planeToAddToHeap.GetAction() == "departing") {
          departingPlanes.push(planeToAddToHeap);
        } 
    
    // Move all planes from input vector to output vector.
      OutputOrderPlanes.insert(OutputOrderPlanes.begin(),planeToAddToHeap);
      InputOrderPlanes.pop_back();
      if (InputOrderPlanes.size() == 0) {
        break;
      }
      if (InputOrderPlanes[InputOrderPlanes.size()-1].GetTime() == timeStep) {
        planeToAddToHeap = InputOrderPlanes[InputOrderPlanes.size()-1];
      } else {
          break;
        }
    }

  // Convert arriving and departing plane Heaps into MinHeaps based
  // on time or priority in regards to timeStep.
    if (timeStep == currentBaseTime) {
      constructMinHeapTime(arrivingPlanes.planeVector);
    } else {
        constructMinHeapPriority(arrivingPlanes.planeVector);
      }
    
    if (timeStep == currentBaseTime) {
      constructMinHeapTime(departingPlanes.planeVector);
    } else {
        constructMinHeapPriority(departingPlanes.planeVector);
      }
  
      cout << "Time step " << timeStep << endl;
      cout << "\tEntering simulation" << endl;

    // Output Planes entering simulation to terminal.
    for (int i =  OutputOrderPlanes.size()-1; i >= 0; i--) {
      if (OutputOrderPlanes[i].GetTime() == timeStep) {
        cout << "\t\t" <<OutputOrderPlanes[i].GetTime();
        cout << " " << OutputOrderPlanes[i].GetID();
        cout << " " << OutputOrderPlanes[i].GetAction();
        cout << " " << OutputOrderPlanes[i].GetPriority() << endl;
      }
    }

    // Remove Planes from output vector that are going
    // on runways.
    switch (OutputOrderPlanes.size()) {
      case 0:{};
      break;
      case 1:OutputOrderPlanes.pop_back();
      break;
      default:OutputOrderPlanes.pop_back();
      OutputOrderPlanes.pop_back();
    }

    // Output planes are their proper runways for a given timeStep.  
    cout << "\tRunway A" << endl; 
    if(departingPlanes.size()>0) {
      runwayAPlane = departingPlanes.pop(); 
      outputPlaneData(runwayAPlane);
      cout << "\tRunway B" << endl; 
      if (arrivingPlanes.size()>0) {
        runwayBPlane = arrivingPlanes.pop();
        outputPlaneData(runwayBPlane);
      } else if (departingPlanes.size()>0) {
          if (departingPlanes.size() > 1) {
            if (timeStep == currentBaseTime) {
              minHeapifyTime(departingPlanes.planeVector, 0, departingPlanes.size());
            } else {
                minHeapifyPriority(departingPlanes.planeVector, 0, departingPlanes.size());
              }
          }
          runwayBPlane = departingPlanes.pop();
          outputPlaneData(runwayBPlane);
        }
    } else if (arrivingPlanes.size()>0) {
        if (arrivingPlanes.size()>1) {
          runwayBPlane = arrivingPlanes.pop();
          if (arrivingPlanes.planeVector.size() > 1) {
            if (timeStep == currentBaseTime) {
              minHeapifyTime(arrivingPlanes.planeVector, 0, arrivingPlanes.size());
            } else {
            minHeapifyPriority(arrivingPlanes.planeVector, 0, arrivingPlanes.size());
      }
          }
          runwayAPlane = arrivingPlanes.pop();
          outputPlaneData(runwayAPlane);
          cout << "\tRunway B" << endl; 
          outputPlaneData(runwayBPlane);
        } else {
            cout << "\tRunway B" << endl; 
            runwayBPlane = arrivingPlanes.pop();
            outputPlaneData(runwayBPlane);
          }
      } 

      //MinHeapify departing and arriving Plane vectors.
      if (departingPlanes.size() > 1) {
        if (timeStep == currentBaseTime) {
          minHeapifyTime(departingPlanes.planeVector, 0, departingPlanes.size());
        } else {
            minHeapifyPriority(departingPlanes.planeVector, 0, departingPlanes.size());
          }
      }
      
      if (arrivingPlanes.size() > 1) {
        if (timeStep == currentBaseTime) {
          minHeapifyTime(arrivingPlanes.planeVector, 0, arrivingPlanes.size());
        } else {
            minHeapifyPriority(arrivingPlanes.planeVector, 0, arrivingPlanes.size());
          }
      }
      timeStep++;
  }
}


// Test Descriptions
/*
Test 1: Testing if time steps increment if there are still planes with 
time that would be less than what the incremented time step would be.
Notice the time does increment past the time of the planes entering the
simulation even though the planes haven't been given a runway to access.

Test 2: Testing if time steps increase in ascending order. Note timeStep
does not increase in ascending order, but rather follows the times of the
input planes in the order they were input.

Test 3: Testing to see what member variable for departing planes gets 
prioritized and how if multiple planes have the same priority but
different entrance times. Note that planes 5,6, and 7 are prioritized
by ascending entrance time when their priorities are the same.

Test 4: Testing to see what runways prioritize. Note that runway A prioritizes 
departing planes even though their priorities are lower than that of the 
arriving planes and runway B prioritizes arriving planes over departing
planes with lower priority.

Test 5: Testing how ID is prioritized when time and priority are the same
for multiple planes. Note how ID is then the determining priority factor
and is prioritized in ascending order.

Test 6: Further tests the premise of test 5 to ensure that output was indeed
based on ascending ID number and not input order. Note the order of the 
planes still follows ascending ID order.

Test 7: Testing to see what member variable becomes the primary priority
determiner when Planes in Heap have different timeSteps. Note now planes are 
prioritized by priority rather than by entrance time.  

Test 8: Testing if time steps increase in ascending order. Note timeStep
does not increase in ascending order, but rather follows the times of
the input planes in the order they were input.

Test 9: Pressure test to test numerous scenarios and determine if output
matches expected output of original executable file. Note output matches
original executable output.

Test 10: Pressure test to test numerous scenarios and determine if output
matches expected output of original executable file. Note output matches
original executable output.
*/


