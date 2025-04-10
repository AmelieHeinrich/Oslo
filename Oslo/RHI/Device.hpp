//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-04-06 11:29:32
//

#pragma once

#include <Core/Context.hpp>
#include "Utils.hpp"

class Device
{
public:
    USE_TRACKING_ALLOCATOR

    Device();
    ~Device();

    ID3D12Device14* GetDevice() { return mDevice; }
    IDXGIFactory6* GetFactory() { return mFactory; }
    std::string GetDeviceName() { return mDeviceName; }
private:
    IDXGIFactory6* mFactory = nullptr;
    IDXGIAdapter1* mAdapter = nullptr;
    ID3D12Device14* mDevice = nullptr;
    ID3D12Debug1* mDebug = nullptr;

    std::string mDeviceName;
};