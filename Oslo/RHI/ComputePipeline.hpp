//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-04-06 15:51:51
//

#pragma once

#include "Device.hpp"
#include "RootSignature.hpp"

#include <Asset/Shader.hpp>
#include <memory>

class ComputePipeline
{
public:
    ComputePipeline(ShaderModule shader, std::shared_ptr<RootSignature> signature);
    ~ComputePipeline();

    ID3D12PipelineState* GetPipeline() { return mPipeline; }
    std::shared_ptr<RootSignature> GetSignature() { return mSignature; }
private:
    ID3D12PipelineState* mPipeline = nullptr;
    std::shared_ptr<RootSignature> mSignature = nullptr;
};
