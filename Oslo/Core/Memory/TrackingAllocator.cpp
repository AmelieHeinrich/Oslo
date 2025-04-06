//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-03-27 13:58:18
//

#include "TrackingAllocator.hpp"

#include <Core/Context.hpp>

void* TrackingAllocator::Allocate(uint64_t size, int line, const char* file)
{
    MemoryInfo info = {};
    info.Line = line;
    info.Size = size;
    info.File = file;

    void* memory = std::malloc(size);
    if (!memory) {
        LOG_ERROR("Allocation failed for %llu bytes at %s:%d", size, file, line);
        return nullptr;
    }
    mTrackedAllocations.emplace(memory, std::move(info));
    return memory;
}

void TrackingAllocator::Free(void* block)
{
    auto it = mTrackedAllocations.find(block);
    if (it != mTrackedAllocations.end()) {
        std::free(block);
        mTrackedAllocations.erase(it);
    } else {
        LOG_ERROR("Double free or invalid pointer detected: %p", block);
    }
}

void TrackingAllocator::Clear()
{
    for (auto& [ptr, _] : mTrackedAllocations) {
        std::free(ptr);
    }

    mTrackedAllocations.clear();
}

void TrackingAllocator::Report()
{
    if (mTrackedAllocations.size() == 0) {
        LOG_INFO("No leaks found. Good job!");
        return;
    }

    for (auto& [ptr, data] : mTrackedAllocations) {
        LOG_INFO("Leak of %zu bytes at %s:%d", data.Size, data.File.c_str(), data.Line);
    }
}
