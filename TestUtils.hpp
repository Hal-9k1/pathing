#pragma once

#include <string>
#include <vector>

class TestUtils
{
public:
  int run();

protected:
  void assertEqChain(const char *testName, int a, int b);
  bool assertEq(const char *testName, int a, int b);
  void enterScope(const char *scopeName);
  void popScope();
  void skipScope();
  bool shouldTest();
  void qualifyTestName(const char *testName, std::string &outFullTestName);

private:
  int failures;
  std::vector<const char *> scopes;
  int ignoredScopeDepth;

  virtual void runTests() = 0;
};
