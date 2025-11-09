#pragma once

#include "BaseGraph.hpp"
#include "Obstacle.hpp"

class Vizgraph : public BaseGraph
{
public:
  void add(const Obstacle &obs);
};
