#include <cstdio>
#include <cstddef>

#include "Tests.hpp"

int main()
{
  Tests tests;
  int failedTests = tests.run();
  if (!failedTests)
  {
    std::printf("All unit tests passed.\n");
    return EXIT_SUCCESS;
  }
  else
  {
    std::printf("%d unit tests failed.\n", failedTests);
    return EXIT_FAILURE;
  }
}
