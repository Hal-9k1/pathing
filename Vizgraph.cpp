#include "Vizgraph.hpp"

#include <cstddef>
#include <vector>

#include "Vec2.hpp"
#include "Segment.hpp"
#include "ObstacleState.hpp"

int Vizgraph::addObstacle(const ObstacleState &obs)
{
  const std::vector<Vec2> &corners = obs.getCorners();
  cornerNodeHandles.push_back({static_cast<int>(corners.size())});
  std::vector<int> &handles = cornerNodeHandles.back();
  for (const Vec2 &corner : corners)
  {
    handles.push_back(createNode(corner));
  }
  for (std::size_t i = 0; i < corners.size(); ++i)
  {
    for (std::size_t j = 0; j < obsData.size(); ++j)
    {
      const std::vector<Vec2> &otherCorners = obsData[j].getCorners();
      for (std::size_t k = 0; i < otherCorners.size(); ++k)
      {
        if (!segmentIntersectsAny({corners[i], otherCorners[k]}))
        {
          connectNodes(handles[i], 1, &cornerNodeHandles[j][k]);
        }
      }
    }
  }
  obsData.push_back(obs);
  return obsData.size() - 1;
}

bool Vizgraph::segmentIntersectsAny(const Segment &segment)
{
  for (const ObstacleState &obs : obsData)
  {
    if (obs.intersectsSegment(segment))
    {
      return true;
    }
  }
  return false;
}
