//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-04-06 11:38:45
//

#pragma once

#include <Core/Common.hpp>

#include <Agility/d3d12.h>
#include <dxgi1_6.h>

class D3DUtils
{
public:
    static void Release(IUnknown* object);
    static uint64_t CalculateAdapterScore(IDXGIAdapter1* adapter);
};
