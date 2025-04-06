//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-04-06 15:06:42
//

#include "CommandBuffer.hpp"
#include "RHI.hpp"
#include "Utils.hpp"

#include <imgui.h>
#include <backends/imgui_impl_dx12.h>
#include <backends/imgui_impl_sdl3.h>

#include <PIX/pix3.h>
#include <Core/Assert.hpp>

CommandBuffer::CommandBuffer(std::shared_ptr<Queue> queue, bool singleTime)
    : mSingleTime(singleTime), mParentQueue(queue)
{
    HRESULT result = RHI::GetDevice()->GetDevice()->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE(queue->GetType()), IID_PPV_ARGS(&mAllocator));
    ASSERT(SUCCEEDED(result), "Failed to create command allocator!");

    result = RHI::GetDevice()->GetDevice()->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE(queue->GetType()), mAllocator, nullptr, IID_PPV_ARGS(&mList));
    ASSERT(SUCCEEDED(result), "Failed to create command list!");

    if (!singleTime) {
        mList->Close();
    }
}

CommandBuffer::~CommandBuffer()
{
    D3DUtils::Release(mAllocator);
    D3DUtils::Release(mList);
}

void CommandBuffer::Begin()
{
    if (!mSingleTime) {
        mAllocator->Reset();
        mList->Reset(mAllocator, nullptr);
    }

    ID3D12DescriptorHeap* heaps[] = {
        RHI::GetHeaps()[DescriptorHeapType::ShaderResource]->GetHeap(),
        RHI::GetHeaps()[DescriptorHeapType::Sampler]->GetHeap()
    };
    mList->SetDescriptorHeaps(2, heaps);
}

void CommandBuffer::UAVBarrier(std::shared_ptr<Resource> resource)
{
    D3D12_RESOURCE_BARRIER Barrier = {};
    Barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_UAV;
    Barrier.UAV.pResource = resource->GetResource();

    mList->ResourceBarrier(1, &Barrier);
}

void CommandBuffer::Barrier(std::shared_ptr<Resource> resource, ResourceLayout layout, uint32_t mip)
{
    D3D12_RESOURCE_BARRIER Barrier = {};
    Barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    Barrier.Transition.pResource = resource->GetResource();
    Barrier.Transition.StateBefore = D3D12_RESOURCE_STATES(resource->GetLayout());
    Barrier.Transition.StateAfter = D3D12_RESOURCE_STATES(layout);
    Barrier.Transition.Subresource = mip == VIEW_ALL_MIPS ? D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES : mip;
    
    if (Barrier.Transition.StateBefore == D3D12_RESOURCE_STATE_UNORDERED_ACCESS && Barrier.Transition.StateAfter == D3D12_RESOURCE_STATE_UNORDERED_ACCESS) {
        Barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_UAV;
        Barrier.UAV.pResource = resource->GetResource();
    } else {
        if (resource->GetLayout() == layout)
            return;
    }
    
    mList->ResourceBarrier(1, &Barrier);
    resource->SetLayout(layout);
}

void CommandBuffer::SetViewport(float x, float y, float width, float height)
{
    D3D12_VIEWPORT Viewport = {};
    Viewport.Width = width;
    Viewport.Height = height;
    Viewport.MinDepth = 0.0f;
    Viewport.MaxDepth = 1.0f;
    Viewport.TopLeftX = x;
    Viewport.TopLeftY = y;

    D3D12_RECT Rect = {};
    Rect.right = width;
    Rect.bottom = height;
    Rect.top = 0.0f;
    Rect.left = 0.0f;

    if (Rect.right < 0 || Rect.bottom < 0)
        return;

    mList->RSSetViewports(1, &Viewport);
    mList->RSSetScissorRects(1, &Rect);
}

void CommandBuffer::SetTopology(Topology topology)
{
    mList->IASetPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY(topology));
}

void CommandBuffer::SetGraphicsPipeline(std::shared_ptr<GraphicsPipeline> pipeline)
{
    mList->SetPipelineState(pipeline->GetPipeline());
    mList->SetGraphicsRootSignature(pipeline->GetRootSignature()->GetSignature());
}

void CommandBuffer::SetComputePipeline(std::shared_ptr<ComputePipeline> pipeline)
{
    mList->SetPipelineState(pipeline->GetPipeline());
    mList->SetComputeRootSignature(pipeline->GetSignature()->GetSignature());
}

void CommandBuffer::SetRenderTargets(const std::vector<std::shared_ptr<View>> targets, std::shared_ptr<View> depth)
{
    std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> cpus;
    for (auto& target : targets) {
        cpus.push_back(target->GetDescriptor().CPU);
    }
    D3D12_CPU_DESCRIPTOR_HANDLE depth_cpu = {};
    if (depth) depth_cpu = depth->GetDescriptor().CPU;

    mList->OMSetRenderTargets(cpus.size(), cpus.data(), false, depth ? &depth_cpu : nullptr);
}

void CommandBuffer::SetVertexBuffer(std::shared_ptr<Buffer> buffer)
{
    mList->IASetVertexBuffers(0, 1, &buffer->mVBV);
}

void CommandBuffer::SetIndexBuffer(std::shared_ptr<Buffer> buffer)
{
    mList->IASetIndexBuffer(&buffer->mIBV);
}

void CommandBuffer::GraphicsPushConstants(const void *data, uint32_t size, int index)
{
    mList->SetGraphicsRoot32BitConstants(index, size / 4, data, 0);
}

void CommandBuffer::ComputePushConstants(const void *data, uint32_t size, int index)
{
    mList->SetComputeRoot32BitConstants(index, size / 4, data, 0);
}

void CommandBuffer::ClearDepth(std::shared_ptr<View> view)
{
    mList->ClearDepthStencilView(view->GetDescriptor().CPU, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}

void CommandBuffer::ClearRenderTarget(std::shared_ptr<View> view, float r, float g, float b)
{
    float clear[] = { r, g, b, 1.0f };
    mList->ClearRenderTargetView(view->GetDescriptor().CPU, clear, 0, nullptr);
}

void CommandBuffer::Draw(int vertexCount)
{
    mList->DrawInstanced(vertexCount, 1, 0, 0);
}

void CommandBuffer::DrawIndexed(int indexCount)
{
    mList->DrawIndexedInstanced(indexCount, 1, 0, 0, 0);
}

void CommandBuffer::Dispatch(int x, int y, int z)
{
    mList->Dispatch(x, y, z);
}

void CommandBuffer::CopyBufferToBuffer(std::shared_ptr<Resource> dst, std::shared_ptr<Resource> src)
{
    mList->CopyResource(dst->GetResource(), src->GetResource());
}

void CommandBuffer::CopyBufferToTexture(std::shared_ptr<Resource> dst, std::shared_ptr<Resource> src)
{
    D3D12_RESOURCE_DESC desc = dst->GetResource()->GetDesc();

    std::vector<D3D12_PLACED_SUBRESOURCE_FOOTPRINT> footprints(desc.MipLevels);
    std::vector<uint32_t> num_rows(desc.MipLevels);
    std::vector<uint64_t> row_sizes(desc.MipLevels);
    uint64_t totalSize = 0;

    RHI::GetDevice()->GetDevice()->GetCopyableFootprints(&desc, 0, desc.MipLevels, 0, footprints.data(), num_rows.data(), row_sizes.data(), &totalSize);

    for (uint32_t i = 0; i < desc.MipLevels; i++) {
        D3D12_TEXTURE_COPY_LOCATION srcCopy = {};
        srcCopy.pResource = src->GetResource();
        srcCopy.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
        srcCopy.PlacedFootprint = footprints[i];

        D3D12_TEXTURE_COPY_LOCATION dstCopy = {};
        dstCopy.pResource = dst->GetResource();
        dstCopy.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
        dstCopy.SubresourceIndex = i;

        mList->CopyTextureRegion(&dstCopy, 0, 0, 0, &srcCopy, nullptr);
    }
}

void CommandBuffer::End()
{
    mList->Close();
}

void CommandBuffer::BeginMarker(const std::string& name)
{
    PIXBeginEvent(mList, PIX_COLOR_DEFAULT, name.data());
}

void CommandBuffer::EndMarker()
{
    PIXEndEvent(mList);
}

void CommandBuffer::BeginGUI(int width, int height)
{
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize.x = width;
    io.DisplaySize.y = height;

    ImGui_ImplDX12_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
}

void CommandBuffer::EndGUI()
{
    ImGuiIO& io = ImGui::GetIO();

    ID3D12DescriptorHeap* pHeaps[] = { RHI::GetHeaps()[DescriptorHeapType::ShaderResource]->GetHeap(), RHI::GetHeaps()[DescriptorHeapType::Sampler]->GetHeap() };
    mList->SetDescriptorHeaps(2, pHeaps);

    ImGui::Render();
    ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), mList);
}
