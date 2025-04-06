//
// > Notice: Amélie Heinrich @ 2024
// > Create Time: 2024-12-03 23:10:09
//

#pragma once

#include "Device.hpp"
#include "DescriptorHeap.hpp"
#include "Resource.hpp"

enum class BufferType
{
    Vertex,
    Index,
    Constant,
    Storage,
    Copy,
    Readback,
    AccelerationStructure
};

class Buffer : public Resource
{
public:
    Buffer(uint64_t size, uint64_t stride, BufferType type, const std::string& name = "Buffer");
    ~Buffer();

    void BuildCBV();
    void BuildUAV();
    void BuildSRV();

    void Map(int start, int end, void **data);
    void Unmap(int start, int end);
    void CopyMapped(void *data, uint64_t size);

    int CBV() { return mCBV.Index; }
    int UAV() { return mUAV.Index; }
    int SRV() { return mSRV.Index; }
private:
    friend class CommandBuffer;

    BufferType mType;

    DescriptorHeap::Descriptor mCBV = {};
    DescriptorHeap::Descriptor mSRV = {};
    DescriptorHeap::Descriptor mUAV = {};

    D3D12_VERTEX_BUFFER_VIEW mVBV;
    D3D12_INDEX_BUFFER_VIEW mIBV;
};
