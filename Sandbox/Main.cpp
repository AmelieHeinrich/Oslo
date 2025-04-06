//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-04-06 11:14:48
//

#include <memory>

#include <Oslo/Oslo.hpp>

int main(void)
{
    Oslo::Init();
    std::shared_ptr<Window> window = std::make_shared<Window>(1280, 720, "Hello, World!");
    Oslo::AttachWindow(window);

    ShaderFile file = ShaderCompiler::Load("TestShaders/Triangle.hlsl");

    GraphicsPipelineSpecs specs = {};
    specs.Bytecodes[ShaderType::Vertex] = file.Modules["VSMain"];
    specs.Bytecodes[ShaderType::Pixel] = file.Modules["PSMain"];
    specs.Reflect = false;
    specs.Formats.push_back(TextureFormat::RGBA8);
    specs.Signature = std::make_shared<RootSignature>();

    std::shared_ptr<GraphicsPipeline> pipeline = std::make_shared<GraphicsPipeline>(specs);

    while (window->IsOpen()) {
        window->Update();

        Frame frame = RHI::Begin();
        frame.CommandBuffer->Begin();
        frame.CommandBuffer->Barrier(frame.Backbuffer, ResourceLayout::ColorWrite);
        frame.CommandBuffer->ClearRenderTarget(frame.BackbufferView, 0.0f, 0.0f, 0.0f);
        frame.CommandBuffer->SetRenderTargets({ frame.BackbufferView }, nullptr);
        frame.CommandBuffer->SetGraphicsPipeline(pipeline);
        frame.CommandBuffer->SetViewport(0, 0, frame.Width, frame.Height);
        frame.CommandBuffer->SetTopology(Topology::TriangleList);
        frame.CommandBuffer->Draw(3);
        frame.CommandBuffer->Barrier(frame.Backbuffer, ResourceLayout::Present);
        frame.CommandBuffer->End();

        RHI::Submit({ frame.CommandBuffer });
        RHI::End();
        RHI::Present(false);
    }
    
    Oslo::Exit();
}
