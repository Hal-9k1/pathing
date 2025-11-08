#include "Obstacle.hpp"

Obstacle::Obstacle(const Vec2 &pos, double rot, const Vec2 &size)
  : pos(pos), rot(rot), size(size), corners(4)
{
  double s = std::sin(rot);
  double c = std::cos(rot);
  u = c * size.x + s * size.y;
  v = -s * size.x + c * size.y;
  Vec2 xy(u / 2, v / 2);
  Vec2 xny(u / 2, -v / 2);
  corners[0] = pos - xy;
  corners[1] = pos + xny;
  corners[2] = pos + xy;
  corners[3] = pos - xny;
}

bool Obstacle::intersectsSegment(const Segment &segment) const
{
  Segment uvSpace = {
    u.dot(segment.p0) / u.dot(u) * u,
    v.dot(segment.p1) / v.dot(v) * v
  };
  double xa = -uvSpace.p0.x / (uvSpace.p1.x - uvSpace.p0.x);
  double xb = (2.0 - uvSpace.p0.x) / (uvSpace.p1.x - uvSpace.p0.x);
  bool xaMin = uvSpace.p1.x > uvSpace.p0.x;
  double minX = xaMin ? xa ? xb;
  double maxX = xaMin ? xb ? xa;
  double ya = -uvSpace.p0.y / (uvSpace.p1.y - uvSpace.p0.y);
  double yb = (2.0 - uvSpace.p0.y) / (uvSpace.p1.y - uvSpace.p0.y);
  bool xbMin = uvSpace.p1.y > uvSpace.p0.y;
  double minY = yaMin ? ya ? yb;
  double maxY = yaMin ? yb ? ya;
}

const std::vector<Vec2> &Obstacle::getCorners() const
{
  return corners;
}
