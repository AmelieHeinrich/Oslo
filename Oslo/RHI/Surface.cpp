//
// > Notice: Amélie Heinrich @ 2024
// > Create Time: 2024-12-03 11:37:25
//

#include "Surface.hpp"
#include "Utils.hpp"
#include "RHI.hpp"

#include <Core/Assert.hpp>
#include <Core/UTF.hpp>

Surface::Surface(std::shared_ptr<Window> window)
{
    int width, height;
    window->GetSize(width, height);

    DXGI_SWAP_CHAIN_DESC1 desc = {};
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    desc.BufferCount = FRAMES_IN_FLIGHT;
    desc.Scaling = DXGI_SCALING_NONE;
    desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    desc.Width = width;
    desc.Height = height;
    desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;

    IDXGISwapChain1* temp;
    HRESULT result = RHI::GetDevice()->GetFactory()->CreateSwapChainForHwnd(RHI::GetGraphicsQueue()->GetQueue(), reinterpret_cast<HWND>(window->GetHandle()), &desc, nullptr, nullptr, &temp);
    temp->QueryInterface(&mSwapchain);
    temp->Release();

    for (int i = 0; i < FRAMES_IN_FLIGHT; i++) {
        ID3D12Resource* backbuffer = nullptr;
        mSwapchain->GetBuffer(i, IID_PPV_ARGS(&backbuffer));
        backbuffer->SetName(UTF::AsciiToWide("Backbuffer " + std::to_string(i)).data());

        TextureDesc desc;
        desc.Width = width;
        desc.Height = height;
        desc.Format = TextureFormat::RGBA8;
        mBackbuffers[i] = std::make_shared<Texture>(backbuffer, desc);

        mBackbufferViews[i] = std::make_shared<View>(mBackbuffers[i], ViewType::RenderTarget, ViewDimension::Texture, TextureFormat::RGBA8);
    }
}

Surface::~Surface()
{
    D3DUtils::Release(mSwapchain);
}

void Surface::Present(bool vsync)
{
    mSwapchain->Present(vsync ? 1 : 0, vsync ? 0 : DXGI_PRESENT_ALLOW_TEARING);
}
