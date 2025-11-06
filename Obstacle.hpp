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
  Vec2 v0;
  Vec2 v1;
  Vec2 u0;
  Vec2 u1;
  double k0;
  double k1;
};
