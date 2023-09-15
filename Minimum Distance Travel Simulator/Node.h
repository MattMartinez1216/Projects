// File: Node Class
// Author: Matthew Martinez
// Description: File contains class/function declarations for Node class.

#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include <memory>
#include "Edge.h"

class Node{
  public:
    unsigned int id;
    unsigned int chargingStation;
    unsigned int dist;
    bool visited;
    std::shared_ptr<Node> predecessor;
    std::vector<std::shared_ptr<Edge>> nodeEdges;
    std::vector<std::shared_ptr<Node>> neighbors;
    
    Node();
    Node(unsigned int, unsigned int);
};

#endif
