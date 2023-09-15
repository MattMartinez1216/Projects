// File: Edge.cpp
// Author: Matthew Martinez
// Description: File contains all member functions for Edge class.

#include "Edge.h"

Edge::Edge() {
}

Edge::Edge(unsigned int start, unsigned int end, unsigned int distance) {
  startNode = start;
  endNode = end;
  dist = distance;
}

unsigned int Edge::GetDist() {
  return dist;
}

unsigned int Edge::GetStartNode() {
  return startNode;
}

unsigned int Edge::GetEndNode() {
  return endNode;
}


