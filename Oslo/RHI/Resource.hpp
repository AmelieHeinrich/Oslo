//
// > Notice: Amélie Heinrich @ 2024
// > Create Time: 2024-12-03 10:38:04
//

#pragma once

#include "Device.hpp"

enum class ResourceLayout
{
    Common = D3D12_RESOURCE_STATE_COMMON,
    Shader = D3D12_RESOURCE_STATE_ALL_SHADER_RESOURCE,
    Storage = D3D12_RESOURCE_STATE_UNORDERED_ACCESS,
    DepthWrite = D3D12_RESOURCE_STATE_DEPTH_WRITE,
    DepthRead = D3D12_RESOURCE_STATE_DEPTH_READ,
    ColorWrite = D3D12_RESOURCE_STATE_RENDER_TARGET,
    CopySource = D3D12_RESOURCE_STATE_COPY_SOURCE,
    CopyDest = D3D12_RESOURCE_STATE_COPY_DEST,
    Present = D3D12_RESOURCE_STATE_PRESENT,
    GenericRead = D3D12_RESOURCE_STATE_GENERIC_READ,
    Vertex = D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER,
    AccelerationStructure = D3D12_RESOURCE_STATE_RAYTRACING_ACCELERATION_STRUCTURE,
    NonPixelShader = D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE
};


class Resource
{
public:
    Resource();
    ~Resource();

    void SetName(const std::string& string);

    uint64_t GetSize() const { return mSize; }
    uint64_t GetStride() const { return mStride; }
    ID3D12Resource* GetResource() const { return mResource; }
    uint64_t GetAddress() { return mResource->GetGPUVirtualAddress(); }
    std::string GetName() { return mName; }

    ResourceLayout GetLayout() { return mLayout; };
    void SetLayout(ResourceLayout layout) { mLayout = layout; }
protected:
    ID3D12Resource* mResource = nullptr;
    
    bool mShouldFree = false;
    uint64_t mSize;
    uint64_t mStride;
    ResourceLayout mLayout;
    std::string mName;

    void CreateResource(D3D12_HEAP_PROPERTIES* heapProps, D3D12_RESOURCE_DESC* resourceDesc, D3D12_RESOURCE_STATES state);
private:
    uint64_t mAllocSize;
};
