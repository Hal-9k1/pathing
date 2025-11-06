#include "AStar.hpp"

AStar::AStar(const Graph &graph, int startHandle, int endHandle)
  : graph(graph), startHandle(startHandle), open(NodeCompare(*this))
{
  endNodePos = graph.getNode(endHandle).getPos();
  saveCostToStart(startHandle);
  saveCostToEnd(startHandle);
  open.push(startHandle);
}

bool AStar::run()
{
  while (!open.empty())
  {
    int curHandle = open.top();
    open.pop();
    openSet.erase(curHandle);
    if (curHandle == endHandle)
    {
      assembleResult();
      return true;
    }
    for (int neighborHandle : graph.getNeighborHandles(curHandle))
    {
      bool isBetterPath = saveCostToStart(neighborHandle);
      saveCostToEnd(neighborHandle);
      if (isBetterPath && openSet.find(neighborHandle) == openSet.end())
      {
        open.push(neighborHandle);
        openSet.insert(neighborHandle);
      }
    }
  }
  return false;
}

const std::vector<int> &getResult()
{
  return result;
}

const Vec2 &AStar::getGraphPos(int handle)
{
  return graph.getNode(handle).getPos();
}

bool AStar::saveCostToStart(int handle)
{
  double cost = 0;
  int curHandle = handle;
  while (curHandle != startHandle)
  {
    int nextHandle = backNode.at(curHandle);
    cost += getGraphPos(curHandle).getDistTo(getGraphPos(nextHandle));
    curHandle = nextHandle;
  }
  auto iter = costToStart.find(handle);
  if (iter == costToStart.end() || iter->second > cost)
  {
    costToStart.insert_or_assign(handle, cost);
    return true;
  }
  return false;
}

void AStar::saveCostToEnd(int handle)
{
  if (costToEnd.find(handle) == costToEnd.end())
  {
    costToEnd.insert({ handle, getGraphPos(handle).getDistTo(endNodePos) });
  }
}

double AStar::getTotalCost(int handle)
{
  return astar.costToStart.at(handle) + astar.costToEnd.at(handle);
}

AStar::NodeCompare::NodeCompare(const AStar &astar)
  : astar(astar)
{ }

bool AStar::NodeCompare::operator()(int a, int b)
{
  return astar.getTotalStart(a) < astar.getTotalCost(b);
}
