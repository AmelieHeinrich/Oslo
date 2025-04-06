//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-03-27 13:55:16
//

#pragma once

#include <unordered_map>

#include "MemoryAllocator.hpp"

class TrackingAllocator : public IMemoryAllocator
{
public:
    TrackingAllocator() = default;
    ~TrackingAllocator() = default;

    void* Allocate(uint64_t size, int line = 0, const char* file = "") override;
    void Free(void* block) override;
    void Clear() override;
    void Report() override;
private:
    struct MemoryInfo {
        uint64_t Size;
        std::string File;
        int32_t Line;
    };

    std::unordered_map<void*, MemoryInfo> mTrackedAllocations;
};
