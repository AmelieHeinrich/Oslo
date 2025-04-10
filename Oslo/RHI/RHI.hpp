//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-04-06 12:08:20
//

#pragma once

#include <memory>

#include <Core/Window.hpp>

#include "Device.hpp"
#include "DescriptorHeap.hpp"
#include "Queue.hpp"
#include "Surface.hpp"
#include "CommandBuffer.hpp"
#include "Fence.hpp"

struct Frame
{
    std::shared_ptr<CommandBuffer> CommandBuffer;
    std::shared_ptr<Texture> Backbuffer;
    std::shared_ptr<View> BackbufferView;
    uint32_t FrameIndex;
    uint32_t FrameCount;

    int Width;
    int Height;
};

class RHI
{
public:
    static void Init();
    static void Exit();
    static void ConnectWindow(std::shared_ptr<Window> window);

    static void Wait();
    static void Submit(const std::vector<std::shared_ptr<CommandBuffer>>& buffers);

    static Frame Begin();
    static void End();
    static void Present(bool vsync);
    static void ResetFrameCount();

    static std::shared_ptr<Device> GetDevice() { return sData.Device; }
    static std::shared_ptr<Queue> GetGraphicsQueue() { return sData.GraphicsQueue; }
    static DescriptorHeaps& GetHeaps() { return sData.Heaps; }
private:
    static struct Data {
        std::shared_ptr<Window> Window;
        std::shared_ptr<Device> Device;
        std::shared_ptr<Queue> GraphicsQueue;
        std::shared_ptr<Surface> Surface;
        DescriptorHeaps Heaps;

        std::shared_ptr<Fence> FrameFence;
        std::array<uint64_t, FRAMES_IN_FLIGHT> FrameValues;
        std::array<std::shared_ptr<CommandBuffer>, FRAMES_IN_FLIGHT> CommandBuffers;
        uint32_t FrameIndex;
        uint32_t FrameCount;

        DescriptorHeap::Descriptor FontDescriptor;
    } sData;
};
