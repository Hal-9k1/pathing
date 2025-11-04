#pragma once

#include "Vec2.hpp"

class Node
{
public:
  const Vec2 &getPos();

private:
  Vec2 pos;
};
