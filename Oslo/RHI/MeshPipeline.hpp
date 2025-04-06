//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-04-06 16:18:19
//

#pragma once

#include "GraphicsPipeline.hpp"

class MeshPipeline
{
public:
    MeshPipeline(GraphicsPipelineSpecs& specs);
    ~MeshPipeline();

    ID3D12PipelineState* GetPipeline() { return mPipeline; }
    std::shared_ptr<RootSignature> GetSignature() { return mSignature; }
private:
    ID3D12PipelineState* mPipeline = nullptr;
    std::shared_ptr<RootSignature> mSignature = nullptr;
};
