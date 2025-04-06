//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-03-27 13:30:12
//

#pragma once

#include <cstdint>
#include <string>

#define BIT(x) (1 << x) 

constexpr uint64_t KILOBYTE = 1024;
constexpr uint64_t MEGABYTE = 1024 * 1024;
constexpr uint64_t GIGABYTE = 1024 * 1024 * 1024;

#if defined(_WIN32)
    #define OSLO_WINDOWS
#endif

#if defined(OSLO_DEBUG)
constexpr bool IsDebugEnabled() {
    return true;
}
#else
constexpr bool IsDebugEnabled() {
    return false;
}
#endif
