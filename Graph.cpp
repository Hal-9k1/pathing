#include "Graph.hpp"

#include <vector>

const std::vector<int> &Graph::getNeighborHandles(int handle)
{
  return neighbors[handle];
}

int Graph::createNode(const Vec2 &pos)
{
  nodes.push_back(Node(pos));
  neighbors.push_back({});
}

Node &Graph::getNode(int handle)
{
  return nodes.at(handle);
}

void Graph::connectNodes(int handle, int numNeighbors, int *pNeighbors)
{
  neighbors.insert(neighbors.end(), pNeighbors, pNeighbors + numNeighbors);
}
