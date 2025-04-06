//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-04-06 15:42:45
//

#pragma once

#include "RootSignature.hpp"
#include "Texture.hpp"

#include <Asset/Shader.hpp>
#include <memory>

enum class FillMode
{
    Solid = D3D12_FILL_MODE_SOLID,
    Line = D3D12_FILL_MODE_WIREFRAME
};

enum class CullMode
{
    Back = D3D12_CULL_MODE_BACK,
    Front = D3D12_CULL_MODE_FRONT,
    None = D3D12_CULL_MODE_NONE
};

enum class DepthOperation
{
    Greater = D3D12_COMPARISON_FUNC_GREATER,
    Less = D3D12_COMPARISON_FUNC_LESS,
    Equal = D3D12_COMPARISON_FUNC_EQUAL,
    LEqual = D3D12_COMPARISON_FUNC_LESS_EQUAL,
    None = D3D12_COMPARISON_FUNC_NONE
};

struct GraphicsPipelineSpecs
{
    FillMode Fill = FillMode::Solid;
    CullMode Cull = CullMode::None;
    bool CCW = true;
    bool Line = false;

    std::vector<TextureFormat> Formats;
    DepthOperation Depth = DepthOperation::None;
    TextureFormat DepthFormat = TextureFormat::Unknown;
    bool DepthEnabled = false;
    bool DepthClampEnable = false;
    bool DepthWrite = true;
    bool Reflect = true;

    std::unordered_map<ShaderType, ShaderModule> Bytecodes;
    std::shared_ptr<RootSignature> Signature = nullptr;
};

class GraphicsPipeline
{
public:
    GraphicsPipeline(GraphicsPipelineSpecs& specs);
    ~GraphicsPipeline();

    ID3D12PipelineState* GetPipeline() { return mPipeline; }
    std::shared_ptr<RootSignature> GetRootSignature() { return mSignature; }
private:
    ID3D12PipelineState* mPipeline = nullptr;
    std::shared_ptr<RootSignature> mSignature = nullptr;
};
