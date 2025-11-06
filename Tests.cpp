#include "Tests.hpp"

#include <cstdio>

#include "AStar.hpp"
#include "Node.hpp"
#include "Vec2.hpp"
#include "Graph.hpp"

void Tests::runTests()
{
  enterScope("Graph");
  {
    Graph graph;
    int handles[] = {
      graph.createNode({0, 0}),
      graph.createNode({0, 0}),
      graph.createNode({0, 0}),
      graph.createNode({0, 0}),
      graph.createNode({0, 0})
    };
    assertEq(
      "new node has no neighbors",
      graph.getNeighborHandles(handles[0]).size(),
      0
    );
    graph.connectNodes(handles[0], 1, &handles[1]);
    enterScope("first connected node");
    if (shouldTest())
    {
      assertEqChain(
        "has neighbor",
        graph.getNeighborHandles(handles[0]).size(),
        1
      );
    }
    if (shouldTest())
    {
      assertEqChain(
        "has other node as neighbor",
        graph.getNeighborHandles(handles[0])[0],
        handles[1]
      );
    }
    popScope();
    enterScope("second connected node");
    if (shouldTest())
    {
      assertEqChain(
        "has neighbor",
        graph.getNeighborHandles(handles[1]).size(),
        1
      );
    }
    if (shouldTest())
    {
      assertEqChain(
        "has other node as neighbor",
        graph.getNeighborHandles(handles[1])[0],
        handles[0]
      );
    }
    popScope();
    graph.connectNodes(handles[2], 1, &handles[1]);
    graph.connectNodes(handles[2], 2, &handles[3]);
    graph.connectNodes(handles[3], 1, &handles[4]);
    enterScope("graph with loops");
    if (shouldTest())
    {
      assertEqChain(
        "is connected properly",
        graph.getNeighborHandles(handles[2]).size(),
        3
      );
    }
    if (shouldTest())
    {
      assertEqChain(
        "is connected properly",
        graph.getNeighborHandles(handles[4]).size(),
        2
      );
    }
    popScope();
  }
  popScope();
  enterScope("AStar");
  {
    Graph graph;
    int handles[] = {
      graph.createNode({0, 0}),
      graph.createNode({2.86, 1.08}),
      graph.createNode({5.59, -0.83}),
      graph.createNode({3.62, -2.85}),
      graph.createNode({5.62, -4.54}),
      graph.createNode({0.14, -3.61}),
      graph.createNode({-1.27, -1.79}),
    };
    {
      AStar astar(graph, handles[0], handles[4]);
      assertEq(
        "unconnected graph fails",
        astar.run(),
        0
      );
    }
    graph.connectNodes(handles[0], 1, &handles[1]);
    graph.connectNodes(handles[1], 1, &handles[2]);
    graph.connectNodes(handles[2], 1, &handles[3]);
    graph.connectNodes(handles[3], 1, &handles[4]);
    graph.connectNodes(handles[4], 1, &handles[5]);
    graph.connectNodes(handles[5], 1, &handles[6]);
    graph.connectNodes(handles[6], 1, &handles[0]);
    enterScope("on simple loop graph");
    {
      AStar astar(graph, handles[0], handles[4]);
      if (shouldTest())
      {
        assertEqChain(
          "succeeds",
          astar.run(),
          1
        );
      }
      if (shouldTest())
      {
        assertEqChain(
          "picks path with correct length",
          astar.getResult().size(),
          3
        );
      }
      if (shouldTest())
      {
        assertEqChain(
          "picks correct path",
          astar.getResult()[1],
          handles[5]
        );
      }
    }
    popScope();
    graph.connectNodes(handles[0], 1, &handles[3]);
    enterScope("on graph with shortcut");
    {
      AStar astar(graph, handles[0], handles[4]);
      if (shouldTest())
      {
        assertEqChain(
          "succeeds",
          astar.run(),
          1
        );
      }
      if (shouldTest())
      {
        assertEqChain(
          "picks path with correct length",
          astar.getResult().size(),
          2
        );
      }
      if (shouldTest())
      {
        assertEqChain(
          "picks correct path",
          astar.getResult()[0],
          handles[3]
        );
      }
    }
    popScope();
  }
  popScope();
}
