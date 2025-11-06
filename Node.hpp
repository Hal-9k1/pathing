#pragma once

#include "Vec2.hpp"

class Node
{
public:
  Node(const Vec2 &pos);
  const Vec2 &getPos();

private:
  Vec2 pos;
};
