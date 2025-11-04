#pragma once

#include "Node.hpp"

class IGraph
{
public:
  virtual int getNeighbors(const Node &node, Node *pNeighbors) = 0;
  virtual int getMaxNeighbors() = 0;
};
