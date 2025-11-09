#pragma once

#include <vector>

#include "BaseGraph.hpp"
#include "Vec2.hpp"

class Graph : public BaseGraph
{
public:
  int createNode(const Vec2 &pos);
  void connectNodes(int handle, int numNeighbors, int *pNeighbors);
};
