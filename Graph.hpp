#pragma once

#include <vector>

#include "Node.hpp"
#include "Vec2.hpp"

class Graph
{
public:
  const std::vector<int> &getNeighborHandles(int handle) override;
  int createNode(const Vec2 &pos);
  int getMaxHandleValue();
  Node &getNode(int handle);
  void connectNodes(int handle, int *pNeighbors);

private:
  std::vector<Node> nodes;
  std::vector<std::vector<int>> neighbors;
}
