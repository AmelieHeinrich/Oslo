//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-04-06 12:24:55
//

#include "DescriptorHeap.hpp"
#include "Utils.hpp"
#include "RHI.hpp"

#include <Core/Assert.hpp>

DescriptorHeap::DescriptorHeap(DescriptorHeapType type, uint32_t size)
    : mType(type), mHeapSize(size), mShaderVisible(false)
{
    D3D12_DESCRIPTOR_HEAP_DESC desc = {};
    desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE(type);
    desc.NumDescriptors = size;
    if (type == DescriptorHeapType::ShaderResource || type == DescriptorHeapType::Sampler) {
        desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
        mShaderVisible = true;
    }

    HRESULT result = RHI::GetDevice()->GetDevice()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&mHeap));
    ASSERT(SUCCEEDED(result), "Failed to create descriptor heap!");

    mLookupTable.resize(size, false);
    mIncrementSize = RHI::GetDevice()->GetDevice()->GetDescriptorHandleIncrementSize(desc.Type);
}

DescriptorHeap::~DescriptorHeap()
{
    D3DUtils::Release(mHeap);
}

DescriptorHeap::Descriptor DescriptorHeap::Allocate()
{
    int index = -1;
    for (uint64_t i = 0; i < mLookupTable.size(); i++) {
        if (mLookupTable[i] == false) {
            mLookupTable[i] = true;
            index = i;
            break;
        }
    }
    ASSERT(index != -1, "Descriptor heap is full!");

    return DescriptorHeap::Descriptor(this, index);
}

void DescriptorHeap::Free(DescriptorHeap::Descriptor& descriptor)
{
    if (!descriptor.Valid)
        return;
    mLookupTable[descriptor.Index] = false;
}
