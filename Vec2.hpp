#pragma once

class Vec2
{
public:
  Vec2() = default;
  Vec2(double x, double y);
  double getDistTo(const Vec2 &other) const;
  double dot(const Vec2 &other) const;
  Vec2 unit() const;
  double len() const;
  Vec2 proj(const Vec2 &other) const;
  Vec2 operator+(const Vec2 &other) const;
  Vec2 operator-(const Vec2 &other) const;
  Vec2 operator-() const;
  Vec2 operator*(double other) const;
  Vec2 operator/(double other) const;
  double getX() const;
  double getY() const;

private:
  double x;
  double y;
};

Vec2 operator*(double a, const Vec2 &b);
