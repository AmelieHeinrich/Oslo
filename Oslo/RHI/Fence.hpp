//
// > Notice: Amélie Heinrich @ 2024
// > Create Time: 2024-12-03 10:01:44
//

#pragma once

#include <Core/Common.hpp>
#include <memory>

#include "Device.hpp"

class Queue;

class Fence
{
public:
    Fence();
    ~Fence();

    void Wait(uint64_t value);
    uint64_t Signal(std::shared_ptr<Queue> queue);
    uint64_t GetCompletedValue() { return mFence->GetCompletedValue(); }

    ID3D12Fence* GetFence() { return mFence; }
    uint64_t GetValue() { return mValue; }
private:
    uint64_t mValue = 0;
    ID3D12Fence* mFence = nullptr;
};
