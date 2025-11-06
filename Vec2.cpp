#include "Vec2.hpp"

#include <cmath>

Vec2::Vec2(double x, double y)
  : x(x), y(y)
{ }

double Vec2::getDistTo(const Vec2 &other) const
{
  double dx = x - other.x;
  double dy = y - other.y;
  return std::sqrt(dx * dx + dy * dy);
}
