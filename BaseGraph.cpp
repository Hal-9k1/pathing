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
