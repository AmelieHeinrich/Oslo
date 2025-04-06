//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-04-06 15:52:22
//

#include "ComputePipeline.hpp"
#include "RHI.hpp"

#include <Core/Context.hpp>

ComputePipeline::ComputePipeline(ShaderModule shader, std::shared_ptr<RootSignature> signature)
    : mSignature(signature)
{
    D3D12_COMPUTE_PIPELINE_STATE_DESC desc = {};
    desc.CS.pShaderBytecode = shader.Bytecode.data();
    desc.CS.BytecodeLength = shader.Bytecode.size();
    desc.pRootSignature = signature->GetSignature();

    HRESULT Result = RHI::GetDevice()->GetDevice()->CreateComputePipelineState(&desc, IID_PPV_ARGS(&mPipeline));
    if (FAILED(Result)) {
        LOG_CRITICAL("Failed creating D3D12 compute pipeline!");
        return;
    }
}

ComputePipeline::~ComputePipeline()
{
    mPipeline->Release();
}
