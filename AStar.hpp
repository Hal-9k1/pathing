#pragma once

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>

#include "Graph.hpp"
#include "Vec2.hpp"

class AStar
{
public:
  AStar(const Graph &graph, int startHandle, int endHandle);
  bool run();
  const std::vector<int> &getResult() const;

private:
  struct NodeCompare
  {
    NodeCompare(const AStar &astar);
    bool operator()(int a, int b) const;
    const AStar &astar;
  };

  const Graph &graph;
  int startHandle;
  int endHandle;
  Vec2 endNodePos;
  std::vector<int> result;
  std::unordered_map<int, double> costToStart;
  std::unordered_map<int, double> costToEnd;
  std::unordered_map<int, int> backNode;
  std::priority_queue<int, std::vector<int>, NodeCompare> openQueue;
  std::unordered_set<int> openSet;

  const Vec2 &getGraphPos(int handle) const;
  double getTotalCost(int handle) const;
  bool saveCostToStart(int handle);
  void saveCostToEnd(int handle);
  void assembleResult();
};
