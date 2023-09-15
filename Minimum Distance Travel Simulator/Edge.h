// File: Edge class
// Author: Matthew Martinez
// Description: File contains class/function declarations for Edge class.

#ifndef EDGE_H
#define EDGE_H

class Edge {
 public:
  Edge();
  Edge(unsigned int, unsigned int,unsigned int);
  unsigned int GetDist();
  unsigned int GetStartNode();
  unsigned int GetEndNode();

 private:
  unsigned int startNode;
  unsigned int endNode;
  unsigned int dist;
};

#endif