#include "Graph.hpp"

#include <vector>

#include "Node.hpp"

int Graph::createNode(const Vec2 &pos)
{
  nodes.push_back(Node(pos));
  neighbors.push_back({});
  return nodes.size() - 1;
}

void Graph::connectNodes(int handle, int numNeighbors, int *pNeighbors)
{
  neighbors[handle].insert(neighbors[handle].end(), pNeighbors, pNeighbors + numNeighbors);
  for (int i = 0; i < numNeighbors; ++i)
  {
    neighbors[pNeighbors[i]].push_back(handle);
  }
}
