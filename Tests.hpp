#pragma once

#include <string>
#include <vector>

class Tests
{
public:
  int run();

private:
  void assertEqChain(const char *testName, int a, int b);
  bool assertEq(const char *testName, int a, int b);
  void enterScope(const char *scopeName);
  void popScope();
  void skipScope();
  bool shouldTest();
  void qualifyTestName(const char *testName, std::string &outFullTestName);

  int failures;
  std::vector<const char *> scopes;
  int ignoredScopeDepth;
};
