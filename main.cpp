#include <cstdio>
#include <cstddef>
#include <cstdlib>

#include "Tests.hpp"

int main()
{
  Tests tests;
  int failedTests = tests.run();
  std::printf("\n");
  if (!failedTests)
  {
    std::printf("All unit tests passed.\n");
    return EXIT_SUCCESS;
  }
  else
  {
    std::printf("%d unit test(s) failed.\n", failedTests);
    return EXIT_FAILURE;
  }
}
