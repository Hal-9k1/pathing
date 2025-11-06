#pragma once

class Vec2
{
public:
  Vec2(double x, double y);
  double getDistTo(const Vec2 &other) const;

private:
  double x;
  double y;
};
