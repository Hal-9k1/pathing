#include "ObstacleState.hpp"

#include <cmath>

ObstacleState::ObstacleState(const Vec2 &pos, double rot, const Vec2 &size)
  : pos(pos), rot(rot), size(size), corners(4), normal(1.0)
{
  double s = std::sin(rot);
  double c = std::cos(rot);
  u = Vec2(c, s) * size.getX();
  v = Vec2(-s, c) * size.getY();
  Vec2 xy = size / 2;
  Vec2 xny(xy.getX(), -xy.getY());
  corners[0] = pos - xy;
  corners[1] = pos + xny;
  corners[2] = pos + xy;
  corners[3] = pos - xny;
}

bool ObstacleState::intersectsSegment(const Segment &segment) const
{
  Vec2 u0 = u.dot(segment.p0) / u.dot(u) * u;
  Vec2 v0 = v.dot(segment.p1) / v.dot(v) * v;
  double a = u0.getX();
  double b = u0.getY();
  double c = v0.getX();
  double d = v0.getY();
  double tx0 = -a / (c - a);
  double tx1 = (1 - a) / (c - a);
  double ty0 = -b / (d - b);
  double ty1 = (1 - b) / (d - b);
  double k1 = (a + (c - a) * ty0) * normal;
  double k2 = (a + (c - a) * ty1) * normal;
  double k3 = (b + (d - b) * tx0) * normal;
  double k4 = (b + (d - b) * tx1) * normal;
  bool b1 = 0 <= k1 && k1 <= normal;
  bool b2 = 0 <= k2 && k2 <= normal;
  bool b3 = 0 <= k3 && k3 <= normal;
  bool b4 = 0 <= k4 && k4 <= normal;
  return b1 || b2 || b3 || b4;
}

const std::vector<Vec2> &ObstacleState::getCorners() const
{
  return corners;
}

void ObstacleState::setInvertedNormals(bool invert)
{
  normal = invert ? -1.0 : 1.0;
}
