//
// > Notice: Amélie Heinrich @ 2024
// > Create Time: 2024-12-03 11:32:04
//

#pragma once

#include "Device.hpp"
#include "View.hpp"
#include "Queue.hpp"
#include "Texture.hpp"

#include <Core/Window.hpp>
#include <array>
#include <memory>

constexpr uint32_t FRAMES_IN_FLIGHT = 3;

class Surface
{
public:
    Surface(std::shared_ptr<Window> window);
    ~Surface();

    void Present(bool vsync);

    uint32_t GetBackbufferIndex() { return mSwapchain->GetCurrentBackBufferIndex(); }
    std::shared_ptr<Texture> GetBackbuffer(uint32_t idx) { return mBackbuffers[idx]; }
    std::shared_ptr<View> GetBackbufferView(uint32_t idx) { return mBackbufferViews[idx]; }
private:
    IDXGISwapChain4* mSwapchain = nullptr;
    std::array<std::shared_ptr<Texture>, FRAMES_IN_FLIGHT> mBackbuffers;
    std::array<std::shared_ptr<View>, FRAMES_IN_FLIGHT> mBackbufferViews;
};
