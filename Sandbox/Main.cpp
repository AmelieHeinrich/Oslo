//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-04-06 11:14:48
//

#include <Oslo/Oslo.hpp>
#include <memory>

int main(void)
{
    Oslo::Init();
    std::shared_ptr<Window> window = std::make_shared<Window>(1280, 720, "Hello, World!");
    Oslo::AttachWindow(window);

    while (window->IsOpen()) {
        window->Update();

        Frame frame = RHI::Begin();
        frame.CommandBuffer->Begin();
        frame.CommandBuffer->Barrier(frame.Backbuffer, ResourceLayout::ColorWrite);
        frame.CommandBuffer->ClearRenderTarget(frame.BackbufferView, 0.2f, 0.3f, 0.8f);
        frame.CommandBuffer->Barrier(frame.Backbuffer, ResourceLayout::Present);
        frame.CommandBuffer->End();

        RHI::Submit({ frame.CommandBuffer });
        RHI::End();
        RHI::Present(false);
    }
    
    Oslo::Exit();
}
