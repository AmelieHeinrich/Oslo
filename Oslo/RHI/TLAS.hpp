//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-04-06 16:03:44
//

#pragma once

#include "AccelerationStructure.hpp"
#include <glm/glm.hpp>

struct RaytracingInstance
{
    glm::mat3x4 Transform;
    uint32_t InstanceID	: 24;
    uint32_t InstanceMask : 8;
    uint32_t InstanceContributionToHitGroupIndex : 24;
    uint32_t Flags : 8;
    uint64_t AccelerationStructure;
};

class TLAS : public AccelerationStructure
{
public:
    TLAS(std::shared_ptr<Buffer> instanceBuffer, uint32_t numInstance, const std::string& name = "TLAS");
    ~TLAS();

    int Bindless() const { return mSRV.Index; }
    DescriptorHeap::Descriptor GetDescriptor() const { return mSRV; }
private:
    DescriptorHeap::Descriptor mSRV;
};
