//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-03-27 13:37:12
//

#pragma once

#include <Core/Common.hpp>

class IMemoryAllocator
{
public:
    virtual ~IMemoryAllocator() = default;

    virtual void* Allocate(uint64_t size, int line = 0, const char* file = "") = 0;
    virtual void Free(void* block) = 0;
    virtual void Clear() = 0;
    virtual void Report() {}
};
