#include <vector>
#include <algorithm>
#include <set>

#include "cs225_graph/graph.h"
#include "cs225_graph/edge.h"

#include "NetworkFlow.h"

int min(int a, int b) {
  if (a<b)
    return a;
  else return b;
}

NetworkFlow::NetworkFlow(Graph & startingGraph, Vertex source, Vertex sink) :
  g_(startingGraph), residual_(Graph(true,true)), flow_(Graph(true,true)), source_(source), sink_(sink) {

  // YOUR CODE HERE
  vector<Vertex> myVertices = startingGraph.getVertices();

  for (const Vertex& v : myVertices) {
    residual_.insertVertex(v);
    flow_.insertVertex(v);
  }

  vector<Edge> myEdges = startingGraph.getEdges();

  for (const Edge& e : myEdges) {
    Vertex i2 = e.source;
    Vertex i3 = e.dest;
    int weight = e.getWeight();
    
    residual_.insertEdge(i2, i3);
    residual_.setEdgeWeight(i2, i3, weight);
    
    residual_.insertEdge(i3, i2);
    residual_.setEdgeWeight(i3, i2, 0);
    
    flow_.insertEdge(i2, i3);
    flow_.setEdgeWeight(i2, i3, 0);
    
    flow_.insertEdge(i3, i2);
    flow_.setEdgeWeight(i3, i2, 0);
  }

}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the helper function.
   *
   * @param source  The starting (current) vertex
   * @param sink    The destination vertex
   * @param path    The vertices in the path
   * @param visited A set of vertices we have visited
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, 
  std::vector<Vertex> &path, std::set<Vertex> &visited) {

  if (visited.count(source) != 0)
    return false;
  visited.insert(source);

  if (source == sink) {
    return true;
  }

  vector<Vertex> adjs = residual_.getAdjacent(source);
  for(auto it = adjs.begin(); it != adjs.end(); it++) {
    if (visited.count(*it) == 0 && residual_.getEdgeWeight(source,*it) > 0) {
      path.push_back(*it);
      if (findAugmentingPath(*it,sink,path,visited))
        return true;
      else {
        path.pop_back();
      }
    }
  }

  return false;
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the main function.  It initializes a set to keep track of visited vertices.
   *
   * @param source The starting (current) vertex
   * @param sink   The destination vertex
   * @param path   The vertices in the path
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, std::vector<Vertex> &path) {
   std::set<Vertex> visited;
   path.clear();
   path.push_back(source);
   return findAugmentingPath(source,sink,path,visited);
}

  /**
   * pathCapacity - Determine the capacity of a path in the residual graph.
   *
   * @param path   The vertices in the path
   */

int NetworkFlow::pathCapacity(const std::vector<Vertex> & path) const {
  // YOUR CODE HERE
  if (path.size() < 2) {
    return 0;
  }

  int minSmall = 1000000000;

  for (size_t i = 0; i < path.size() - 1; i++) {
    Vertex i2 = path[i];
    Vertex i3 = path[i + 1];

    int edgeOne = residual_.getEdgeWeight(i2, i3);
    minSmall = min(minSmall, edgeOne);
  }
  
  return minSmall;
}

  /**
   * calculateFlow - Determine the maximum flow of the entire graph.
   * Sets the member variable `maxFlow_` to the computed maximum flow, and updates the
   * residual graph and flow graph according to the algorithm.
   *
   * @return The network flow graph.
   */

const Graph & NetworkFlow::calculateFlow() {
  // YOUR CODE HERE
  maxFlow_ = 0;
  std::vector<Vertex> path;

  while (findAugmentingPath(source_, sink_, path)) {
    
    int mySize = pathCapacity(path);
    
    maxFlow_ += mySize;
    
    for (size_t i = 0; i < path.size() - 1; i++) {
      Vertex i2 = path[i];
      Vertex i3 = path[i + 1];
      
      int myRes = residual_.getEdgeWeight(i2, i3);
      residual_.setEdgeWeight(i2, i3, myRes - mySize);

      int my2ndRes = residual_.getEdgeWeight(i3, i2);
      residual_.setEdgeWeight(i3, i2, my2ndRes + mySize);

      int theFlow = 0;

      if (g_.edgeExists(i2, i3)) {
        theFlow = flow_.getEdgeWeight(i2, i3);
        flow_.setEdgeWeight(i2, i3, theFlow + mySize);
      } else {
        theFlow = flow_.getEdgeWeight(i3, i2);
        flow_.setEdgeWeight(i3, i2, theFlow - mySize);
      }
    }
  }
  
  return flow_;

}

int NetworkFlow::getMaxFlow() const {
  return maxFlow_;
}

const Graph & NetworkFlow::getGraph() const {
  return g_;
}

const Graph & NetworkFlow::getFlowGraph() const {
  return flow_;
}

const Graph & NetworkFlow::getResidualGraph() const {
  return residual_;
}

