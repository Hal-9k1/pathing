#pragma once

#include <string>
#include <vector>

#include "Vec2.hpp"

class TestUtils
{
public:
  int run();

protected:
  void assertEqChain(const char *testName, int a, int b);
  bool assert(const char *testName, const char *testDetail, bool pass);
  bool assertEq(const char *testName, const Vec2 &a, const Vec2 &b, int precision);
  bool assertEq(const char *testName, double a, double b, int precision);
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
