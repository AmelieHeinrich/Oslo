//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-03-27 13:46:09
//

#pragma once

#include "MemoryAllocator.hpp"

class ArenaAllocator : public IMemoryAllocator
{
public:
    ArenaAllocator(uint64_t arenaSize);
    ~ArenaAllocator();

    void* Allocate(uint64_t size, int line = 0, const char* file = "") override;
    void Free(void* block) override;
    void Clear() override;
    void Report() override;
private:
    uint8_t* mMemoryBlock;
    uint64_t mTracker;
    uint64_t mCap;
};
