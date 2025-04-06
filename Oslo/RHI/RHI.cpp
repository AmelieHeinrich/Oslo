//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-04-06 12:20:53
//

#include "RHI.hpp"

RHI::Data RHI::sData;

void RHI::Init()
{
    sData.Device = std::make_shared<Device>();

    sData.Heaps[DescriptorHeapType::RenderTarget] = std::make_shared<DescriptorHeap>(DescriptorHeapType::RenderTarget, 2048);
    sData.Heaps[DescriptorHeapType::DepthTarget] = std::make_shared<DescriptorHeap>(DescriptorHeapType::DepthTarget, 2048);
    sData.Heaps[DescriptorHeapType::ShaderResource] = std::make_shared<DescriptorHeap>(DescriptorHeapType::ShaderResource, 1'000'000);
    sData.Heaps[DescriptorHeapType::Sampler] = std::make_shared<DescriptorHeap>(DescriptorHeapType::Sampler, 2048);
}

void RHI::Exit()
{

}
