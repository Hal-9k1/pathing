#include "TestUtils.hpp"

#include <cmath>
#include <string>
#include <cstdio>
#include <memory>

#include "Vec2.hpp"
#include "smartsprintf.hpp"

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

bool TestUtils::assert(const char *testName, const char *testDetail, bool pass)
{
  std::string fullTestName; // FIXME: string realloc segfault, even right after creation
  qualifyTestName(testName, fullTestName);
  std::printf("%s %s\n", fullTestName.data(), testDetail);
  if (!pass)
  {
    std::printf("FAILED: %s\n", fullTestName.data());
    ++failures;
    return false;
  }
  return true;
}

bool TestUtils::assertEq(const char *testName, const Vec2 &a, const Vec2 &b, int precision)
{
  std::unique_ptr<char []> numFmt = smartsprintf("%%.%df", precision);
  std::unique_ptr<char []> fmt = smartsprintf(
    "<%s, %s> == <%s, %s>",
    numFmt.get(), numFmt.get(), numFmt.get(), numFmt.get()
  );
  Vec2 scaleDiff = (a - b) * std::pow(10, precision);
  Vec2 roundedDiff = {std::round(scaleDiff.getX()), std::round(scaleDiff.getY())};
  std::unique_ptr<char []> detail = smartsprintf(fmt.get(), a.getX(), a.getY(), b.getX(), b.getY());
  return assert(testName, detail.get(), roundedDiff.dot(roundedDiff) == 0.0);
}

bool TestUtils::assertEq(const char *testName, double a, double b, int precision)
{
  std::unique_ptr<char []> numFmt = smartsprintf("%%.%df", precision);
  int scale = std::pow(10, precision);
  std::unique_ptr<char []> fmt = smartsprintf("%s == %s", numFmt.get(), numFmt.get());
  std::unique_ptr<char []> detail = smartsprintf(fmt.get(), a, b);
  return assert(testName, detail.get(), std::round(a * scale) == std::round(b * scale));
}

bool TestUtils::assertEq(const char *testName, int a, int b)
{
  std::unique_ptr<char []> detail = smartsprintf("%d == %d", a, b);
  return assert(testName, detail.get(), a == b);
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
