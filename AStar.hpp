#pragma once

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <priority_queue>

class AStar
{
public:
  AStar(const Graph &graph, int startHandle, int endHandle);
  bool run();
  const std::vector<int> &getResult();

private:
  struct NodeCompare
  {
    NodeCompare(const AStar &astar);
    bool operator()(int a, int b);
    const AStar &astar;
  };

  const Graph &graph;
  Vec2 endNodePos;
  std::vector<int> result;
  std::unordered_map<int, double> costToStart;
  std::unordered_map<int, double> costToEnd;
  std::unordered_map<int, int> backNode;
  std::priority_quene<int, std::vector<int>, NodeCompare> open;
  std::unordered_set<int> openSet;

  const Vec2 &getGraphPos(int handle);
  bool saveCostToStart(int handle);
  void saveCostToEnd(int handle);
};
