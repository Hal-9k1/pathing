#include "Node.hpp"

Node::Node(const Vec2 &pos)
  : pos(pos)
{ }

const Vec2 &Node::getPos() const
{
  return pos;
}
