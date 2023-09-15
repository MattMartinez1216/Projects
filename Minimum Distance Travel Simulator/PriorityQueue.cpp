// File: PriorityQueue.cpp
// Author: Matthew Martinez
// Description: File contains all member functions for MinHeap class.

#include <iostream>
#include <vector>
#include "PriorityQueue.h"
#include "Node.h"

using std::vector;

MinHeap::MinHeap(){
  nodeVector.resize(0);
}

bool MinHeap::empty() {
  if (nodeVector.size() == 0) {
    return true;
  }

  return false;
}

int MinHeap::size() {
  return nodeVector.size();
}

void MinHeap::push(std::shared_ptr<Node> n) {
 nodeVector.push_back(n);
}

std::shared_ptr<Node> MinHeap::pop() {
 std::shared_ptr<Node> nextNode = nodeVector[0];
  if (nodeVector.size() >= 1) {
  nodeVector[0] = nodeVector[nodeVector.size() - 1];
  nodeVector.pop_back();
  }
  return nextNode;
}

std::shared_ptr<Node> MinHeap::peek() {
  return nodeVector[0];
}



