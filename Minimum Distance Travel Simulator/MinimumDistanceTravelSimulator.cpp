// File: MinimumDistanceTravelSimulator.cpp
// Author: Matthew Martinez
// Description: Program takes in values for graph size, number of graph edges, the vehicles max range, 
// the vehicle's initial range, The startNodeID(node number), the endNodeID(node number), and the nodes'
// distances and other pertinent information. Program then determines the minimum viable distance between 
// the start and end nodes that allow for charing of the vehicle at available charging/fuel stations along the way.

#include "Node.h"
#include "Graph.h"
#include "Edge.h"
#include "PriorityQueue.h"
#include <iostream>
#include <limits.h>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

void minHeapifyDist(vector<std::shared_ptr<Node>> &v, int i, int nodesVectorSize) {
  int left = 2*i+1;
  int right = 2*i+2;
  int minI = i;

  // Determine if left child of node [i] has smaller distance than node [i]
  if (left < nodesVectorSize && v[left]->dist < v[i]->dist)
    { minI = left; }
  if (right < nodesVectorSize && v[right]->dist < v[minI]->dist)
    { minI = right; }
  if (minI != i){
    std::shared_ptr<Node> temp = v[i];
    v[i] = v[minI];
    v[minI] = temp;
    minHeapifyDist(v, minI, nodesVectorSize);
}
}

void constructMinHeapDist(vector<std::shared_ptr<Node>> &v){
  if (v.size() > 1) {
    int lastNode = (v.size()/2) - 1;
    for (int i = lastNode; i >= 0; i--) {
      // ADD BACK LATER 
      minHeapifyDist(v,i,v.size());
    } 
  }
}

void Dijkstras(Graph &g, unsigned int s, unsigned int vehicleInitialRange) {
  MinHeap minDist = MinHeap();
  g.nodePath.push_back(g.nodes[0]);
  
  
  for (unsigned int i = 0; i < g.nodes.size(); i++) {
    minDist.push(g.nodes[i]);
    minDist.nodeVector[i]->dist = INT_MAX;
    minDist.nodeVector[i]->predecessor = nullptr;
  }

  g.nodes[s]->dist = 0;

  // ADD CONSTRUCT MINHEAP HERE
  //constructMinHeapDist(minDist.nodeVector);

  std::shared_ptr<Node> currentMinDist;
  std::shared_ptr<Edge> currentEdge;
  //cout<< "made it to while loop" << endl;
  while (minDist.size() > 0) {
    currentMinDist = minDist.peek();
   // unsigned int shortestPath = INT_MAX;

  for (unsigned int i = 0; i < minDist.nodeVector[0]->neighbors.size(); i++) {
    currentEdge = nullptr;
    for (unsigned int j = 0; j < minDist.nodeVector[0]->nodeEdges.size(); j++) {
      if (minDist.nodeVector[0]->nodeEdges[j]->GetStartNode() == minDist.nodeVector[0]->id
      && minDist.nodeVector[0]->nodeEdges[j]->GetEndNode() == minDist.nodeVector[0]->neighbors[i]->id) {
        if (currentEdge == nullptr) {
        currentEdge = minDist.nodeVector[0]->nodeEdges[j]; 
        }
   
          if (minDist.nodeVector[0]->nodeEdges[j]->GetStartNode() == currentEdge->GetStartNode()
          && minDist.nodeVector[0]->nodeEdges[j]->GetEndNode() == currentEdge->GetEndNode()) {
            if (currentEdge->GetDist() > minDist.nodeVector[0]->nodeEdges[j]->GetDist()) {
              currentEdge = minDist.nodeVector[0]->nodeEdges[j];
            }
          }

        
        // MAY NEED TO ACCOUNT FOR EQUAL LENGTH PATH SPLIT
       // if (currentEdge->GetDist() < shortestPath) {
       // shortestPath = currentEdge->GetDist();
        //}
      }
    }
    if (minDist.nodeVector[0]->neighbors[i]->dist > (minDist.nodeVector[0]->dist + currentEdge->GetDist())) {
      minDist.nodeVector[0]->neighbors[i]->dist = minDist.nodeVector[0]->dist + currentEdge->GetDist();
      minDist.nodeVector[0]->neighbors[i]->predecessor = minDist.nodeVector[0];
    }

    // push shortest path node here
    //for (unsigned int m = 0; m < minDist.nodeVector.size(); m++  ) {
     // if (minDist.nodeVector[m]->dist == shortestPath) {
       // g.nodePath.push_back(minDist.nodeVector[m]);
      //}
    //}
    
  }

  minDist.pop();
  minHeapifyDist(minDist.nodeVector, 0, minDist.nodeVector.size());
  //cout << "finished while loop" << endl;
  }
  std::shared_ptr<Node> currentPredecessor = g.nodes[g.nodes.size()-1]->predecessor;
  while (currentPredecessor->predecessor != nullptr) {
    g.nodePath.insert(g.nodePath.begin()+1,currentPredecessor);
    currentPredecessor = currentPredecessor->predecessor;
  }

    g.nodePath.push_back(g.nodes[g.nodes.size()-1]);

    // check to see if initial range of vehicle can get it to 
    //first charging station
      if (g.nodePath[1]->dist > vehicleInitialRange) {
        unsigned int chargingStationNodeDist = INT_MAX; 
        std::shared_ptr<Node> chargingStationNode = nullptr;
        for (unsigned int i = 0; i < g.nodes[0]->neighbors.size(); i++) {
          if (g.nodes[0]->neighbors[i]->chargingStation == 1 
          && g.nodes[0]->neighbors[i]->dist <= vehicleInitialRange) {
            if ( g.nodes[0]->neighbors[i]->dist < chargingStationNodeDist) {
              chargingStationNode = g.nodes[0]->neighbors[i];
              chargingStationNodeDist = g.nodes[0]->neighbors[i]->dist;
            }
          }
        }
           if (chargingStationNodeDist != INT_MAX) {
            g.nodePath.insert(g.nodePath.begin() + 1,chargingStationNode);
            g.extraInitialChargeUpDist = chargingStationNode->dist;           
           }
      }

  }

  bool verifyPath(Graph g, vector<int> v, int i, int c) {
    return g.isReachable(0,g.nodes.size() - 1);
  }

int main() {
  unsigned int graphSize, graphEdges, vehicleMaxRange, vehicleInitialRange; 
  unsigned int startNodeID, endNodeID;
  unsigned int  nodeID, nodeChargingStation;

  cin >> graphSize >> graphEdges >> vehicleMaxRange >> vehicleInitialRange;

  cin >> startNodeID >> endNodeID;
  
  Graph Map1 = Graph();

  for (unsigned int i = 0; i < graphSize; i++){
    cin >> nodeID >> nodeChargingStation;
    std::shared_ptr<Node> nodeToAdd(new Node(nodeID,nodeChargingStation));
   // cout << "node = " << nodeToAdd->id << "station = " << nodeToAdd->chargingStation << endl;
    Map1.nodes.push_back(nodeToAdd);
    //Map1.nodes[i]->nodeEdges.resize(graphSize);
  } 

  for (unsigned int i = 0; i < graphEdges; i++){
    unsigned int u, v, d;
    cin >> u >> v >> d;
    std::shared_ptr<Edge> edgeToAdd(new Edge(u,v,d));
    std::shared_ptr<Edge> edgeToAdd2(new Edge(v,u,d));
    //Map1.nodes[u]->nodeEdges[v] = edgeToAdd;
    Map1.nodes[u]->nodeEdges.push_back(edgeToAdd);
    Map1.nodes[u]->neighbors.push_back(Map1.nodes[v]);
    Map1.nodes[v]->nodeEdges.push_back(edgeToAdd2);
    Map1.nodes[v]->neighbors.push_back(Map1.nodes[u]);
  }

  Graph Map2 = Map1.RemakeGraph(startNodeID,endNodeID, vehicleMaxRange);

  // reset neighbors for new graph
  for (unsigned int i = 0; i < Map2.nodes.size(); i++) {
    Map2.nodes[i]->neighbors.clear();
    for (unsigned int j = 0; j < Map2.nodes[i]->nodeEdges.size(); j++) {
      for (unsigned int k = 0; k < Map2.nodes.size(); k++) {
        if (Map2.nodes[i]->nodeEdges[j]->GetEndNode() == Map2.nodes[k]->id) {
          Map2.nodes[i]->neighbors.push_back(Map2.nodes[k]);
        }
      }
    }
    }

  Graph Map3 = Map2;
  vector<int> pathOfNodes;
  for (unsigned int i = 0; i < Map3.nodePath.size(); i++) {
    pathOfNodes.push_back(Map3.nodePath[i]->id);
  }

  if (Map2.isReachable(0,Map2.nodes.size() - 1) == true) {
    Dijkstras(Map2, startNodeID, vehicleInitialRange);
  } else {
    cout << "No suitable path from" << startNodeID << " to ";
    cout << endNodeID << "exists." << endl;
  }



  cout << "Verify Path: " << verifyPath(Map3, pathOfNodes, vehicleInitialRange, vehicleMaxRange) << endl;
  cout << Map2.nodes[Map2.nodes.size()-1]->dist + Map2.extraInitialChargeUpDist*2 << ": ";

  // PRINT OUT ALL NODES TRAVERSED
  for (int i = 0; i < Map2.nodePath.size(); i++) {
    cout << Map2.nodePath[i]->id << " ";
  }

  cout << endl;
  return 0;
}
