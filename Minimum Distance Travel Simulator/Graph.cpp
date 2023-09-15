// File: Graph.cpp
// Author: Matthew Martinez
// Description: File contains all member functions for Graph class.

#include <iostream>
#include "Graph.h"
#include <queue>
#include <limits.h>

using std::cout;
using std::endl;
using std::vector;

/*Description: Default constructor for Graph class
  Parameters: N/A
  Returns: N/A
*/
Graph::Graph(){
  nodes = {};
  nodePath = {};
  extraInitialChargeUpDist = 0;
}

Graph Graph::RemakeGraph (unsigned int startNodeID, unsigned int endNodeID, unsigned int maxRange) {
  unsigned int sourceNode;

  vector<std::shared_ptr<Edge>> EdgesForGraph2,  EdgesForGraph2b;
  vector<std::shared_ptr<Node>> NodesForGraph2;

  // Add all nodes that are start, end, or charging station to vector
    NodesForGraph2.push_back(nodes[startNodeID]);

  for (unsigned int i = 0; i < nodes.size(); i++) {
    if (nodes[i]->chargingStation == 1 && (nodes[i]->id != startNodeID && nodes[i]->id != endNodeID)) {
      NodesForGraph2.push_back(nodes[i]);
    }
  }

  NodesForGraph2.push_back(nodes[endNodeID]);
  
     // reset member variables for all nodes
  for (unsigned int i = 0; i < nodes.size(); i++) {
    nodes[i]->dist = INT_MAX;
    nodes[i]->visited = false;
    nodes[i]->predecessor = nullptr;
  }


  for (unsigned int s = 0; s < NodesForGraph2.size(); s++) {
    if (NodesForGraph2[s]->id != endNodeID) { 
      NodesForGraph2[s]->dist = 0;
      sourceNode =  NodesForGraph2[s]->id;

      std::vector<std::shared_ptr<Node>> visited;
      visited.insert(visited.begin(),NodesForGraph2[s]);
      std::shared_ptr<Edge> currentEdge;

      while (visited.size() > 0) {
        int ns = visited.back()->id;
        visited.pop_back();
      
        if (nodes[ns]->id != endNodeID) {
        // visit all unvisited neighbors for each node and set member variables
          for (unsigned int i = 0; i < nodes[ns]->neighbors.size(); i++) {
            if (nodes[ns]->neighbors[i]->visited == false) {
              for (unsigned int j = 0; j < nodes[ns]->nodeEdges.size(); j++) {
                if (nodes[ns]->nodeEdges[j]->GetStartNode() == nodes[ns]->id  
                && nodes[ns]->nodeEdges[j]->GetEndNode() == nodes[ns]->neighbors[i]->id) {
                  currentEdge = nodes[ns]->nodeEdges[j];
                }
              }

              nodes[ns]->neighbors[i]->dist = nodes[ns]->dist + currentEdge->GetDist();
              nodes[ns]->neighbors[i]->predecessor = nodes[ns];
              // if node is charging station create edge from source node to charging station for new graph
              if ((nodes[ns]->neighbors[i]->chargingStation == 1 || nodes[ns]->neighbors[i]->id == endNodeID) 
              && (nodes[ns]->neighbors[i]->dist <= maxRange)) {
                std::shared_ptr<Edge> edgeToAdd(new Edge(sourceNode,nodes[ns]->neighbors[i]->id,nodes[ns]->neighbors[i]->dist));
                std::shared_ptr<Edge> edgeToAdd2(new Edge(nodes[ns]->neighbors[i]->id,sourceNode, nodes[ns]->neighbors[i]->dist));
                EdgesForGraph2.push_back(edgeToAdd);
                EdgesForGraph2b.push_back(edgeToAdd2);
              } 
            }
            // Determine which nodes need to be added to visited vector.
            if (nodes[ns]->neighbors[i]->id != endNodeID && nodes[ns]->neighbors[i]->chargingStation == 0 && nodes[ns]->neighbors[i]->visited == false) {
              bool chargingStations = false;
              for (unsigned int z = 0; z < nodes.size(); z++) {
                if (nodes[z]->chargingStation == 1) {
                  chargingStations = true;
                }
              }
              
              if (chargingStations == true) {
                visited.insert(visited.begin(), nodes[ns]->neighbors[i]);
              }             
            }
          }
        }
        
        bool allChargingNeighborsvisited = true;

        for (unsigned int i = 0; i < nodes[ns]->neighbors.size(); i++) {
          if (nodes[ns]->neighbors[i]->id == endNodeID) {
            allChargingNeighborsvisited = false;
          }
        }
        
        if (nodes[ns]->chargingStation == 0 && allChargingNeighborsvisited == true) {
          nodes[ns]->visited = true;
        }
      }
    }
    nodes[sourceNode]->visited = true;
  }

  // Add all nodes to new graph.
  Graph Graph2 = Graph();
  for (unsigned int i = 0; i < NodesForGraph2.size(); i++) {
    NodesForGraph2[i]->nodeEdges.clear();
    Graph2.nodes.push_back(NodesForGraph2[i]);
  }

  // Add all edges to new graph.
  for (unsigned int i = 0; i < EdgesForGraph2.size(); i++) {
    unsigned int edgeStart = EdgesForGraph2[i]->GetStartNode();
    unsigned int edgeEnd =  EdgesForGraph2[i]->GetEndNode();

    for (unsigned int j = 0; j < Graph2.nodes.size(); j++) {
      if (Graph2.nodes[j]->id == edgeStart) {
        Graph2.nodes[j]->nodeEdges.push_back(EdgesForGraph2[i]);
      }
      
      if (Graph2.nodes[j]->id == edgeEnd) {
        Graph2.nodes[j]->nodeEdges.push_back(EdgesForGraph2b[i]);
      }
    }
  }

  return Graph2;
}

/*Description: Function BFS performs breadth first search
  on graph. Function takes parameter int s as source node.
  Parameters: int s
  Returns: void
*/
void Graph::AlteredBFS(int s){
  // reset member variables for all nodes
  for (unsigned int i = 0; i < nodes.size(); i++) {
    nodes[i]->visited = false;
  }

  nodes[s]->visited = true;

  std::vector<std::shared_ptr<Node>> visited;
  visited.insert(visited.begin(),nodes[s]);

  while (visited.size() > 0) {
    s = visited.back()->id;
    visited.pop_back();

    unsigned int currentVectorLocation;
    for (unsigned int i = 0; i < nodes.size(); i++) {
      if (s == nodes[i]->id) {
        s = i;
      }
    }

    // visit all unvisited neighbors for each node and set member variables
    for (unsigned int i = 0; i < nodes[s]->neighbors.size(); i++) {
      if (nodes[s]->neighbors[i]->visited == false) {
        nodes[s]->neighbors[i]->visited = true;
        visited.insert(visited.begin(),nodes[s]->neighbors[i]);
      }
    }
  }
}


/*Description: Function determines if nodes u and v have a 
  path through the graph linking the two.
  Parameters: int u, int v
  Returns: bool
*/
bool Graph::isReachable(int u, int v){
  if (nodes.size() > 0){
    AlteredBFS(u);
  }

  if (nodes[v]->visited == true) {
    return true;
  }

  return false;
}
