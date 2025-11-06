#include "Vec2.hpp"

#include <cmath>

double Vec2::getDistTo(const Vec2 &other)
{
  double dx = x - other.x;
  double dy = y - other.y;
  return std::sqrt(dx * dx + dy * dy);
}
