#pragma once

#include <vector>

#include "Node.hpp"
#include "Vec2.hpp"

class BaseGraph
{
public:
  const std::vector<int> &getNeighborHandles(int handle) const;
  Node &getNode(int handle);
  const Node &getNode(int handle) const;

protected:
  int createNode(const Vec2 &pos);
  void connectNodes(int handle, int numNeighbors, int *pNeighbors);

  std::vector<Node> nodes;
  std::vector<std::vector<int>> neighbors;
};
