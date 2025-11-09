#pragma once

#include <vector>

#include "Vec2.hpp"
#include "Segment.hpp"

class Obstacle
{
public:
  Obstacle(const Vec2 &pos, double rot, const Vec2 &size);
  bool intersectsSegment(const Segment &segment) const;
  const std::vector<Vec2> &getCorners() const;

private:
  Vec2 pos;
  double rot;
  Vec2 size;
  std::vector<Vec2> corners;
  Vec2 u;
  Vec2 v;
};
