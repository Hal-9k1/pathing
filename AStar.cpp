#include "AStar.hpp"

#include <cstdio>

AStar::AStar(const Graph &graph, int startHandle, int endHandle)
  : graph(graph),
    startHandle(startHandle),
    endHandle(endHandle),
    endNodePos(graph.getNode(endHandle).getPos()),
    openQueue(NodeCompare(*this))
{
  saveCostToStart(startHandle, 0);
  saveCostToEnd(startHandle);
  openQueue.push(startHandle);
}

bool AStar::run()
{
  while (!openQueue.empty())
  {
    int curHandle = openQueue.top();
    printf("Considering node %d\n", curHandle);
    openQueue.pop();
    openSet.erase(curHandle);
    if (curHandle == endHandle)
    {
      printf("Found the end\n");
      assembleResult();
      return true;
    }
    for (int neighborHandle : graph.getNeighborHandles(curHandle))
    {
      printf("Considering %d's neighbor %d\n", curHandle, neighborHandle);
      bool isBetterPath = saveCostToStart(neighborHandle, curHandle);
      saveCostToEnd(neighborHandle);
      if (isBetterPath && openSet.find(neighborHandle) == openSet.end())
      {
        printf("New best route from %d to %d, adding to open\n", neighborHandle, curHandle);
        backNode.insert_or_assign(neighborHandle, curHandle);
        openQueue.push(neighborHandle);
        openSet.insert(neighborHandle);
      }
    }
    printf("Done with node %d for now\n", curHandle);
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

bool AStar::saveCostToStart(int handle, int forcedParentHandle)
{
  double cost = getGraphPos(handle).getDistTo(getGraphPos(forcedParentHandle));
  int curHandle = forcedParentHandle;
  while (curHandle != startHandle)
  {
    int nextHandle = backNode.at(curHandle);
    cost += getGraphPos(curHandle).getDistTo(getGraphPos(nextHandle));
    curHandle = nextHandle;
  }
  printf("Found start cost of %d to be %.2f", handle, cost);
  auto iter = costToStart.find(handle);
  if (iter == costToStart.end() || iter->second > cost)
  {
    printf(", closer than existing cost of %.2f\n", iter == costToStart.end() ? -1.0 : iter->second);
    costToStart.insert_or_assign(handle, cost);
    return true;
  }
  printf("\n");
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
  std::printf("  Total cost of %d is %.2f\n", handle, costToStart.at(handle) + costToEnd.at(handle));
  return costToStart.at(handle) + costToEnd.at(handle);
}

void AStar::assembleResult()
{
  int pathLength = 0;
  int handle = endHandle;
  int debug_backNodeSize = backNode.size(); (void)debug_backNodeSize;
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
  return astar.getTotalCost(a) > astar.getTotalCost(b);
}
