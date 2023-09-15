// File: Priorityqueue.cpp
// Author: Matthew Martinez
// Description: File contains class/function declarations for Min\Heap class.

#include<iostream>
#include <vector>
#include "Node.h"
using std::vector;


#ifndef MinHeap_H
#define MinHeap_H

class MinHeap{
 public:
  MinHeap();

  bool empty();
  
  int size();

  void push(std::shared_ptr<Node>);

  std::shared_ptr<Node> pop();

  std::shared_ptr<Node> peek();

  vector<std::shared_ptr<Node>> nodeVector;
};

#endif
