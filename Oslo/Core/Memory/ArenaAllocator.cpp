//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-03-27 13:48:38
//

#include "ArenaAllocator.hpp"
#include <Core/Context.hpp>

ArenaAllocator::ArenaAllocator(uint64_t arenaSize)
    : mCap(arenaSize), mTracker(0)
{
    mMemoryBlock = reinterpret_cast<uint8_t*>(std::malloc(arenaSize));
    if (!mMemoryBlock) {
        LOG_CRITICAL("Failed to allocate arena allocator memory!");
    }
}

ArenaAllocator::~ArenaAllocator()
{
    std::free(reinterpret_cast<void*>(mMemoryBlock));
}

void* ArenaAllocator::Allocate(uint64_t size, int line, const char* file)
{
    if (mTracker + size > mCap) {
        LOG_ERROR("Arena Allocator is out of memory!");
        return nullptr;
    }

    void* memory = reinterpret_cast<void*>(mMemoryBlock + mTracker);
    mTracker += size;
    return memory;
}

void ArenaAllocator::Free(void* block)
{
    LOG_WARN("Arena Allocator doesn't support free functions!");
}

void ArenaAllocator::Clear()
{
    mTracker = 0;
}

void ArenaAllocator::Report()
{
    LOG_INFO("Arena Allocator Report: Size: %.3fmb, Used: %.3fmb", float(mCap) / float(MEGABYTE), float(mTracker) / float(MEGABYTE));
}
