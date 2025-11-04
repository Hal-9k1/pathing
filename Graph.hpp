#pragma once

#include "IGraph.hpp"
#include "Node.hpp"

class Graph
{
public:
  int getNeighbors(const Node *pNode, Node **ppNeighbors) override;
  int getMaxNeighbors() override;
  Node *createNode(const Vec2 &pos);
  void connectNodes(const Node &node, Node **ppNeighbors);
}
