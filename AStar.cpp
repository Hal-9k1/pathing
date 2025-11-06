#include "AStar.hpp"

AStar::AStar(const Graph &graph, int startHandle, int endHandle)
  : graph(graph),
    startHandle(startHandle),
    endNodePos(graph.getNode(endHandle).getPos()),
    openQueue(NodeCompare(*this))
{
  saveCostToStart(startHandle);
  saveCostToEnd(startHandle);
  openQueue.push(startHandle);
}

bool AStar::run()
{
  while (!openQueue.empty())
  {
    int curHandle = openQueue.top();
    openQueue.pop();
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
        backNode.insert_or_assign(neighborHandle, curHandle);
        openQueue.push(neighborHandle);
        openSet.insert(neighborHandle);
      }
    }
  }
  return false;
}

const std::vector<int> &AStar::getResult() const
{
  return result;
}

const Vec2 &AStar::getGraphPos(int handle) const
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

double AStar::getTotalCost(int handle) const
{
  return costToStart.at(handle) + costToEnd.at(handle);
}

void AStar::assembleResult()
{
  int pathLength = 0;
  int handle = endHandle;
  while (handle != startHandle)
  {
    ++pathLength;
    handle = backNode.at(handle);
  }
  result.resize(pathLength);
  handle = endHandle;
  auto iter = result.rbegin();
  while (handle != startHandle)
  {
    *iter++ = handle;
    handle = backNode.at(handle);
  }
}

AStar::NodeCompare::NodeCompare(const AStar &astar)
  : astar(astar)
{ }

bool AStar::NodeCompare::operator()(int a, int b) const
{
  return astar.getTotalCost(a) < astar.getTotalCost(b);
}
