// File Node.cpp
// Author: Matthew Martinez
// Description: File contains all member functions for Node class.

#include "Node.h"
#include "Edge.h"
#include <limits.h>

using std::vector;

Node::Node(){
  id = 0;
  dist = INT_MAX;
  visited = false;
  predecessor = nullptr;
  vector<std::shared_ptr<Edge>> nodeEdges;
  neighbors = {};
}

Node::Node(unsigned int i, unsigned int chargingS){
  id = i;
  chargingStation = chargingS;
  dist = INT_MAX;
  visited = false;
  predecessor = nullptr;
  vector<std::shared_ptr<Edge>> nodeEdges;
  neighbors = {};
}
