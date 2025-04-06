//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-04-06 12:08:20
//

#pragma once

#include <memory>

#include "Device.hpp"
#include "DescriptorHeap.hpp"

class RHI
{
public:
    static void Init();
    static void Exit();

    static std::shared_ptr<Device> GetDevice() { return sData.Device; }
private:
    static struct Data {
        std::shared_ptr<Device> Device;
        DescriptorHeaps Heaps;
    } sData;
};
