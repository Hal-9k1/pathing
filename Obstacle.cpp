#include "Obstacle.hpp"

Obstacle::Obstacle(const Vec2 &pos, double rot, const Vec2 &size)
  : pos(pos), rot(rot), size(size), corners(4)
{
  double s = std::sin(rot);
  double c = std::cos(rot);
  v0 = c * size.x + s * size.y;
  v1 = -s * size.x + c * size.y;
  u0 = { c, s };
  u1 = { -s, c };
  k0 = v0.dot(v0);
  k1 = v1.dot(v1);
  Vec2 u(v0 / 2, v1 / 2);
  Vec2 v(v0 / 2, -v1 / 2);
  corners[0] = pos - u;
  corners[1] = pos + v;
  corners[2] = pos + u;
  corners[3] = pos - v;
}
bool Obstacle::intersectsSegment(const Segment &segment) const;
const std::vector<Vec2> &Obstacle::getCorners() const;
