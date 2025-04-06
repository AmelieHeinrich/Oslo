//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-04-06 16:07:05
//


#pragma once

#include <Asset/Shader.hpp>

#include "RootSignature.hpp"
#include "Buffer.hpp"

struct RaytracingPipelineSpecs
{
    uint32_t PayloadSize;
    uint32_t AttribSize = 8;
    uint32_t MaxRecursion = 3;

    ShaderModule Library;
    std::shared_ptr<RootSignature> Signature = nullptr;
};

class RaytracingPipeline
{
public:
    RaytracingPipeline(RaytracingPipelineSpecs specs);
    ~RaytracingPipeline();

    ID3D12StateObject* GetPipeline() { return mPipeline; }
    std::shared_ptr<RootSignature> GetSignature() { return mSignature; }
    std::shared_ptr<Buffer> GetTables() { return mIDBuffer; }
private:
    ID3D12StateObject* mPipeline = nullptr;
    std::shared_ptr<RootSignature> mSignature = nullptr;
    std::shared_ptr<Buffer> mIDBuffer = nullptr;
};
