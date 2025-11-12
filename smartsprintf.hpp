#pragma once

#include <memory>
#include <utility>

template <typename ...T>
std::unique_ptr<char []> smartsprintf(const char *fmt, T... args)
{
  int len = std::snprintf(nullptr, 0, fmt, args...);
  std::unique_ptr<char []> pBuf = std::make_unique<char []>(len);
  std::sprintf(pBuf.get(), fmt, args...);
  return pBuf;
}
