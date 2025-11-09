#pragma once

#include "BaseGraph.hpp"
#include "ObstacleState.hpp"
#include "Segment.hpp"

#include <vector>

class Vizgraph : public BaseGraph
{
public:
  int addObstacle(const ObstacleState &obs);

private:
  bool segmentIntersectsAny(const Segment &segment);

  std::vector<ObstacleState> obsData;
  std::vector<std::vector<int>> cornerNodeHandles;
};
