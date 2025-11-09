#include "BaseGraph.hpp"

#include <vector>

const std::vector<int> &BaseGraph::getNeighborHandles(int handle) const
{
  return neighbors[handle];
}

Node &BaseGraph::getNode(int handle)
{
  return nodes.at(handle);
}

const Node &BaseGraph::getNode(int handle) const
{
  return nodes.at(handle);
}

int BaseGraph::createNode(const Vec2 &pos)
{
  nodes.push_back(Node(pos));
  neighbors.push_back({});
  return nodes.size() - 1;
}

void BaseGraph::connectNodes(int handle, int numNeighbors, int *pNeighbors)
{
  neighbors[handle].insert(neighbors[handle].end(), pNeighbors, pNeighbors + numNeighbors);
  for (int i = 0; i < numNeighbors; ++i)
  {
    neighbors[pNeighbors[i]].push_back(handle);
  }
}
