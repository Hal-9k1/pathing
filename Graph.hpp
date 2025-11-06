#pragma once

#include <vector>

#include "Node.hpp"
#include "Vec2.hpp"

class Graph
{
public:
  const std::vector<int> &getNeighborHandles(int handle) const;
  int createNode(const Vec2 &pos);
  Node &getNode(int handle);
  const Node &getNode(int handle) const;
  void connectNodes(int handle, int numNeighbors, int *pNeighbors);

private:
  std::vector<Node> nodes;
  std::vector<std::vector<int>> neighbors;
};
