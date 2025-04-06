//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-04-06 12:24:13
//

#pragma once

#include "Device.hpp"

#include <vector>
#include <unordered_map>
#include <memory>

enum class DescriptorHeapType
{
    ShaderResource = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
    Sampler = D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER,
    RenderTarget = D3D12_DESCRIPTOR_HEAP_TYPE_RTV,
    DepthTarget = D3D12_DESCRIPTOR_HEAP_TYPE_DSV
};

class DescriptorHeap
{
public:
    struct Descriptor
    {
        bool Valid = false;
        int Index = -1;
        DescriptorHeap* Parent = nullptr;

        D3D12_CPU_DESCRIPTOR_HANDLE CPU;
        D3D12_GPU_DESCRIPTOR_HANDLE GPU;
        
        Descriptor() = default;
        Descriptor(DescriptorHeap* heap, int index)
            : Parent(heap), Index(index), Valid(true)
        {
            CPU = Parent->mHeap->GetCPUDescriptorHandleForHeapStart();
            CPU.ptr += index * Parent->mIncrementSize;

            if (Parent->mShaderVisible) {
                GPU = Parent->mHeap->GetGPUDescriptorHandleForHeapStart();
                GPU.ptr += index * Parent->mIncrementSize;
            }
        }
    };

    DescriptorHeap(DescriptorHeapType type, uint32_t size);
    ~DescriptorHeap();

    Descriptor Allocate();
    void Free(Descriptor& descriptor);

    ID3D12DescriptorHeap* GetHeap() { return mHeap; }
private:
    DescriptorHeapType mType;
    ID3D12DescriptorHeap* mHeap = nullptr;

    int mIncrementSize = 0;
    uint32_t mHeapSize = 0;
    bool mShaderVisible = false;
    std::vector<bool> mLookupTable;
};

using DescriptorHeaps = std::unordered_map<DescriptorHeapType, std::shared_ptr<DescriptorHeap>>;
