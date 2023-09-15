// File: Graph.h
// Author: Matthew Martinez
// Description: File contains class/function declarations for Graph class.

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "Node.h"

class Graph{
  public:
   std::vector<std::shared_ptr<Node>> nodes;
   std::vector<std::shared_ptr<Node>> nodePath;
   unsigned int extraInitialChargeUpDist;
   Graph();
   void AlteredBFS(int);
   Graph RemakeGraph(unsigned int, unsigned int, unsigned int);
   bool isReachable(int, int);
};

#endif
