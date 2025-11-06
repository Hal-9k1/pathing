#include "Vec2.hpp"

#include <cmath>

Vec2::Vec2(double x, double y)
  : x(x), y(y)
{ }

double Vec2::getDistTo(const Vec2 &other) const
{
  return (*this - other).len();
}

double Vec2::dot(const Vec2 &other) const
{
  return x * other.x + y * other.y;
}

double Vec2::unit() const
{
  return *this / len();
}

double Vec2::len() const
{
  return std::sqrt(this->dot(*this));
}

Vec2 Vec2::operator+(const Vec2 &other) const
{
  return { x - other.x, y - other.y };
}

Vec2 Vec2::operator-(const Vec2 &other) const
{
  return *this + (-other);
}

Vec2 Vec2::operator-() const
{
  return { -x, -y };
}

Vec2 Vec2::operator*(double other) const
{
  return { x * other, y * other };
}

Vec2 Vec2::operator/(double other) const
{
  return *this * (1 / other);
}

Vec2 operator*(double a, const Vec2 &b)
{
  return b * a;
}
