//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-04-06 15:59:51
//

#include "AccelerationStructure.hpp"
#include "RHI.hpp"

#undef max

AccelerationStructure::AccelerationStructure()
    : Resource()
{
    mInputs = {};
}

void AccelerationStructure::Allocate(const std::string& name)
{
    D3D12_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO prebuildInfo = {};
    RHI::GetDevice()->GetDevice()->GetRaytracingAccelerationStructurePrebuildInfo(&mInputs, &prebuildInfo);
    mUpdateSize = prebuildInfo.UpdateScratchDataSizeInBytes;

    mScratch = std::make_shared<Buffer>(prebuildInfo.ScratchDataSizeInBytes, 0, BufferType::Storage, "Scratch Acceleration Structure " + name);

    D3D12_HEAP_PROPERTIES props = {};
    props.Type = D3D12_HEAP_TYPE_DEFAULT;

    D3D12_RESOURCE_DESC desc = {};
    desc.Flags = D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS | D3D12_RESOURCE_FLAG_RAYTRACING_ACCELERATION_STRUCTURE;
    desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    desc.Width = prebuildInfo.ResultDataMaxSizeInBytes;
    desc.Height = 1;
    desc.DepthOrArraySize = 1;
    desc.MipLevels = 1;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

    CreateResource(&props, &desc, D3D12_RESOURCE_STATE_RAYTRACING_ACCELERATION_STRUCTURE);
    SetName(name);
}

void AccelerationStructure::FreeScratch()
{
    mScratch.reset();
}
