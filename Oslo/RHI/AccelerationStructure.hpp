//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-04-06 15:59:11
//

#pragma once

#include "Device.hpp"
#include "DescriptorHeap.hpp"
#include "Resource.hpp"
#include "Buffer.hpp"

class AccelerationStructure : public Resource
{
public:
    AccelerationStructure();
    ~AccelerationStructure() = default;

    void FreeScratch();
    std::shared_ptr<Buffer> GetScratch() { return mScratch; }
protected:
    friend class Uploader;
    friend class CommandBuffer;

    void Allocate(const std::string& name = "Acceleration Structure");

    DescriptorHeaps mHeaps;
    D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS mInputs;
    uint64_t mUpdateSize = 0;
    std::shared_ptr<Buffer> mScratch = nullptr;
};
