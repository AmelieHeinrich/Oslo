//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-04-06 16:04:24
//

#include "TLAS.hpp"
#include "RHI.hpp"

TLAS::TLAS(std::shared_ptr<Buffer> instanceBuffer, uint32_t numInstance, const std::string& name)
    : AccelerationStructure()
{
    mInputs = {};
    mInputs.Type = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL;
    mInputs.Flags = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_ALLOW_UPDATE | D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_PREFER_FAST_TRACE;
    mInputs.NumDescs = numInstance;
    mInputs.DescsLayout = D3D12_ELEMENTS_LAYOUT_ARRAY;
    mInputs.InstanceDescs = instanceBuffer->GetAddress();
    Allocate(name);

    mSRV = RHI::GetHeaps()[DescriptorHeapType::ShaderResource]->Allocate();

    D3D12_SHADER_RESOURCE_VIEW_DESC desc = {};
    desc.ViewDimension = D3D12_SRV_DIMENSION_RAYTRACING_ACCELERATION_STRUCTURE;
    desc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    desc.Format = DXGI_FORMAT_UNKNOWN;
    desc.RaytracingAccelerationStructure.Location = mResource->GetGPUVirtualAddress();
    
    RHI::GetDevice()->GetDevice()->CreateShaderResourceView(nullptr, &desc, mSRV.CPU);
}

TLAS::~TLAS()
{
    mSRV.Parent->Free(mSRV);
}
