//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-03-27 13:40:30
//

#pragma once

#include "MemoryAllocator.hpp"

class BasicAllocator : public IMemoryAllocator
{
public:
    BasicAllocator() = default;
    ~BasicAllocator() = default;

    void* Allocate(uint64_t size, int line = 0, const char* file = "") override;
    void Free(void* block) override;
    void Clear() override;
};
