//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-04-06 12:20:53
//

#include "RHI.hpp"

#include <imgui.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_dx12.h>

RHI::Data RHI::sData;

DWORD AwaitFence(ID3D12Fence* fence, uint64_t val, uint64_t timeout)
{
    DWORD result = WAIT_FAILED;
    if (fence->GetCompletedValue() < val) {
        HANDLE eventHandle = CreateEvent(NULL, FALSE, FALSE, NULL);
        fence->SetEventOnCompletion(val, eventHandle);
        if (eventHandle != 0) {
            result = WaitForSingleObject(eventHandle, timeout);
            CloseHandle(eventHandle);
        }
    } else {
        result = WAIT_OBJECT_0;
    }
    return result;
}

DWORD AwaitQueue(ID3D12Device* device, ID3D12CommandQueue* queue, uint64_t timeout)
{
    ID3D12Fence1* fence = nullptr;
    device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
    if (!fence) {
        return WAIT_FAILED;
    }
    queue->Signal(fence, 1);
    auto result = AwaitFence(fence, 1, timeout);
    fence->Release();
    return result;
}

void RHI::Init()
{
    sData.Device = std::make_shared<Device>();

    sData.Heaps[DescriptorHeapType::RenderTarget] = std::make_shared<DescriptorHeap>(DescriptorHeapType::RenderTarget, 2048);
    sData.Heaps[DescriptorHeapType::DepthTarget] = std::make_shared<DescriptorHeap>(DescriptorHeapType::DepthTarget, 2048);
    sData.Heaps[DescriptorHeapType::ShaderResource] = std::make_shared<DescriptorHeap>(DescriptorHeapType::ShaderResource, 1'000'000);
    sData.Heaps[DescriptorHeapType::Sampler] = std::make_shared<DescriptorHeap>(DescriptorHeapType::Sampler, 2048);

    sData.GraphicsQueue = std::make_shared<Queue>(QueueType::AllGraphics);

    sData.FrameFence = std::make_shared<Fence>();
    sData.FrameIndex = 0;
    for (int i = 0; i < FRAMES_IN_FLIGHT; i++) {
        sData.FrameValues[i] = 0;
        sData.CommandBuffers[i] = std::make_shared<CommandBuffer>(sData.GraphicsQueue);
    }

    sData.FontDescriptor = sData.Heaps[DescriptorHeapType::ShaderResource]->Allocate();
}

void RHI::ConnectWindow(std::shared_ptr<Window> window)
{
    sData.Window = window;
    sData.Surface = std::make_shared<Surface>(window);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsLight();

    ImGuiIO& IO = ImGui::GetIO();
    IO.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    IO.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    IO.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui_ImplSDL3_InitForD3D(sData.Window->GetWindow());
    ImGui_ImplDX12_Init(sData.Device->GetDevice(),
                        FRAMES_IN_FLIGHT,
                        DXGI_FORMAT_R8G8B8A8_UNORM,
                        sData.Heaps[DescriptorHeapType::RenderTarget]->GetHeap(),
                        sData.FontDescriptor.CPU,
                        sData.FontDescriptor.GPU);
    ImGui_ImplDX12_CreateDeviceObjects();
}

void RHI::Exit()
{
    ImGui_ImplDX12_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
    sData.FontDescriptor.Parent->Free(sData.FontDescriptor);

    // In this order
    sData.Surface.reset();
    for (auto& [_, heap] : sData.Heaps) {
        heap.reset();
    }
}

void RHI::Wait()
{
    AwaitQueue(sData.Device->GetDevice(), sData.GraphicsQueue->GetQueue(), 10'000'000);
}

void RHI::Submit(const std::vector<std::shared_ptr<CommandBuffer>>& buffers)
{
    sData.GraphicsQueue->Submit(buffers);
}

Frame RHI::Begin()
{
    Frame frame = {};
    frame.FrameIndex = sData.Surface->GetBackbufferIndex();
    frame.Backbuffer = sData.Surface->GetBackbuffer(frame.FrameIndex);
    frame.BackbufferView = sData.Surface->GetBackbufferView(frame.FrameIndex);
    frame.CommandBuffer = sData.CommandBuffers[frame.FrameIndex];
    
    sData.FrameIndex = frame.FrameIndex;

    sData.Window->GetSize(frame.Width, frame.Height);

    return frame;
}

void RHI::End()
{
    const uint64_t fenceValue = sData.FrameValues[sData.FrameIndex];
    sData.GraphicsQueue->Signal(sData.FrameFence, fenceValue);

    if (sData.FrameFence->GetCompletedValue() < sData.FrameValues[sData.FrameIndex]) {
        sData.FrameFence->Wait(sData.FrameValues[sData.FrameIndex]);
    }
    sData.FrameValues[sData.FrameIndex] = fenceValue + 1;
}

void RHI::Present(bool vsync)
{
    sData.Surface->Present(vsync);
}
