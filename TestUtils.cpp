#include "TestUtils.hpp"

#include <string>
#include <cstdio>

int TestUtils::run()
{
  failures = 0;
  scopes.clear();
  ignoredScopeDepth = 0;
  runTests();
  return failures;
}

void TestUtils::assertEqChain(const char *testName, int a, int b)
{
  if (!assertEq(testName, a, b))
  {
    skipScope();
  }
}

bool TestUtils::assertEq(const char *testName, int a, int b)
{
  std::string fullTestName;
  qualifyTestName(testName, fullTestName);
  std::printf("%s %d == %d\n", fullTestName.data(), a, b);
  if (a != b)
  {
    std::printf("FAILED: %s\n", fullTestName.data());
    ++failures;
    return false;
  }
  return true;
}

void TestUtils::enterScope(const char *scopeName)
{
  std::printf("\n");
  ignoredScopeDepth += static_cast<bool>(ignoredScopeDepth);
  scopes.push_back(scopeName);
}

void TestUtils::popScope()
{
  ignoredScopeDepth -= static_cast<bool>(ignoredScopeDepth);
  scopes.pop_back();
}

void TestUtils::skipScope()
{
  ignoredScopeDepth = ignoredScopeDepth ? ignoredScopeDepth : 1;
}

bool TestUtils::shouldTest()
{
  return ignoredScopeDepth == 0;
}

void TestUtils::qualifyTestName(const char *testName, std::string &outFullTestName)
{
  outFullTestName = "";
  for (const char *scope : scopes)
  {
    outFullTestName += scope;
    outFullTestName += " / ";
  }
  outFullTestName += testName;
}
