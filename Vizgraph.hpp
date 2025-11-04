#pragma once

#include "IGraph.hpp"
#include "Obstacle.hpp"

class Vizgraph : IGraph
{
public:
  void add(Obstacle &obs);
};
