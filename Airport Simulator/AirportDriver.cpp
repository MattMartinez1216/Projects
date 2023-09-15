// AirportDriver.cpp
// Author: Matthew Martinez
// Description: Program uses a priority queue to simulate an airport. Program manages scheduled incoming
// and outgoing planes and uses priority to schedule planes for landing and departure.

#include <iostream>
#include <vector>
#include <string>
#include "Plane.h"
#include "PriorityQueue.h"

using std::cin;
using std::cout;
using std::vector;
using std::endl;
using std::string;

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

