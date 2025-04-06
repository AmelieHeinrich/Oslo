//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-04-06 15:41:13
//

#pragma once

#include <vector>

#include "Device.hpp"

enum class RootType
{
    PushConstant = 0xFFFF,
    ConstantBuffer = D3D12_DESCRIPTOR_RANGE_TYPE_CBV,
    ShaderResource = D3D12_DESCRIPTOR_RANGE_TYPE_SRV,
    Storage = D3D12_DESCRIPTOR_RANGE_TYPE_UAV,
    Sampler = D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER
};

class RootSignature
{
public:
    RootSignature();
    RootSignature(const std::vector<RootType>& roots, uint64_t pushConstantSize = 0);
    ~RootSignature();

    ID3D12RootSignature* GetSignature() { return mRootSignature; }
private:
    ID3D12RootSignature* mRootSignature = nullptr;
};
