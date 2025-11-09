#include "Graph.hpp"

#include <vector>

#include "BaseGraph.hpp"
#include "Node.hpp"

int Graph::createNode(const Vec2 &pos)
{
  return BaseGraph::createNode(pos);
}

void Graph::connectNodes(int handle, int numNeighbors, int *pNeighbors)
{
  BaseGraph::connectNodes(handle, numNeighbors, pNeighbors);
}
