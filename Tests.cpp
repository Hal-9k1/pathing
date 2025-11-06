#include "Tests.hpp"

#include <cstdio>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "Node.hpp"
#include "Vec2.hpp"
#include "Graph.hpp"

int Tests::run()
{
  failures = 0;
  ignoredScopeDepth = 0;

  // Tests for Graph
  enterScope("Graph");
  {
    std::unique_ptr<Graph> pGraph;

    pGraph = std::make_unique<Graph>();
    int handles[] = {
      pGraph->createNode({0, 0}),
      pGraph->createNode({1, 0}),
      pGraph->createNode({0, 0}),
      pGraph->createNode({0, 0}),
      pGraph->createNode({0, 0})
    };
    assertEq(
      "new node has no neighbors",
      pGraph->getNeighborHandles(handles[0]).size(),
      0
    );
    pGraph->connectNodes(handles[0], 1, &handles[1]);
    enterScope("first connected node");
    if (shouldTest())
    {
      assertEqChain(
        "has neighbor",
        pGraph->getNeighborHandles(handles[0]).size(),
        1
      );
    }
    if (shouldTest())
    {
      assertEqChain(
        "has other node as neighbor",
        pGraph->getNeighborHandles(handles[0])[0],
        handles[1]
      );
    }
    popScope();
    enterScope("second connected node");
    if (shouldTest())
    {
      assertEqChain(
        "has neighbor",
        pGraph->getNeighborHandles(handles[1]).size(),
        1
      );
    }
    if (shouldTest())
    {
      assertEqChain(
        "has other node as neighbor",
        pGraph->getNeighborHandles(handles[1])[0],
        handles[0]
      );
    }
    popScope();
  }
  popScope();

  return failures;
}

void Tests::assertEqChain(const char *testName, int a, int b)
{
  if (!assertEq(testName, a, b))
  {
    skipScope();
  }
}

bool Tests::assertEq(const char *testName, int a, int b)
{
  std::string fullTestName;
  qualifyTestName(testName, fullTestName);
  printf("%s %d == %d\n", fullTestName.data(), a, b);
  if (a != b)
  {
    printf("FAILED: %s\n", fullTestName.data());
    ++failures;
    return false;
  }
  return true;
}

void Tests::enterScope(const char *scopeName)
{
  ignoredScopeDepth += static_cast<bool>(ignoredScopeDepth);
  scopes.push_back(scopeName);
}

void Tests::popScope()
{
  ignoredScopeDepth -= static_cast<bool>(ignoredScopeDepth);
  scopes.pop_back();
  printf("\n");
}

void Tests::skipScope()
{
  ignoredScopeDepth = ignoredScopeDepth ? ignoredScopeDepth : 1;
}

bool Tests::shouldTest()
{
  return ignoredScopeDepth == 0;
}

void Tests::qualifyTestName(const char *testName, std::string &outFullTestName)
{
  outFullTestName = "";
  for (const char *scope : scopes)
  {
    outFullTestName += scope;
    outFullTestName += " / ";
  }
  outFullTestName += testName;
}
