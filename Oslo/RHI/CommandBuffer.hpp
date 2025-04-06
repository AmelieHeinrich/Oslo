//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-04-06 15:04:03
//

#pragma once

#include "Queue.hpp"
#include "View.hpp"
#include "Resource.hpp"
#include "Buffer.hpp"
#include "GraphicsPipeline.hpp"
#include "ComputePipeline.hpp"
#include "RaytracingPipeline.hpp"
#include "MeshPipeline.hpp"
#include "TLAS.hpp"

#include <vector>

enum class Topology
{
    LineList = D3D_PRIMITIVE_TOPOLOGY_LINELIST,
    LineStrip = D3D_PRIMITIVE_TOPOLOGY_LINESTRIP,
    PointList = D3D_PRIMITIVE_TOPOLOGY_POINTLIST,
    TriangleList = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
    TriangleStrip = D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP
};

class CommandBuffer
{
public:
    CommandBuffer(std::shared_ptr<Queue> queue, bool singleTime = false);
    ~CommandBuffer();

    void Begin();
    void End();

    void BeginMarker(const std::string& name);
    void EndMarker();

    void UAVBarrier(std::shared_ptr<Resource> resource);
    void Barrier(std::shared_ptr<Resource> resource, ResourceLayout layout, uint32_t mip = VIEW_ALL_MIPS);
    
    void SetViewport(float x, float y, float width, float height);
    void SetTopology(Topology topology);

    void SetGraphicsPipeline(std::shared_ptr<GraphicsPipeline> pipeline);
    void SetComputePipeline(std::shared_ptr<ComputePipeline> pipeline);
    void SetRaytracingPipeline(std::shared_ptr<RaytracingPipeline> pipeline);
    void SetMeshPipeline(std::shared_ptr<MeshPipeline> pipeline);

    void SetRenderTargets(const std::vector<std::shared_ptr<View>> targets, std::shared_ptr<View> depth);
    void SetVertexBuffer(std::shared_ptr<Buffer> buffer);
    void SetIndexBuffer(std::shared_ptr<Buffer> buffer);

    void GraphicsPushConstants(const void *data, uint32_t size, int index);
    void ComputePushConstants(const void *data, uint32_t size, int index);

    void ClearDepth(std::shared_ptr<View> view);
    void ClearRenderTarget(std::shared_ptr<View> view, float r, float g, float b);

    void Draw(int vertexCount);
    void DrawIndexed(int indexCount);
    void Dispatch(int x, int y, int z);
    void TraceRays(int width, int height);

    void CopyTextureToTexture(std::shared_ptr<Resource> dst, std::shared_ptr<Resource> src) { CopyBufferToBuffer(dst, src); } // It's all buffers anyway innit?
    void CopyBufferToBuffer(std::shared_ptr<Resource> dst, std::shared_ptr<Resource> src);
    void CopyBufferToTexture(std::shared_ptr<Resource> dst, std::shared_ptr<Resource> src);
    void UpdateTLAS(std::shared_ptr<TLAS> tlas, std::shared_ptr<Buffer> instanceBuffer, int numInstances);
    void BuildAccelerationStructure(std::shared_ptr<AccelerationStructure> as);

    void BeginGUI(int width, int height);
    void EndGUI();

    ID3D12GraphicsCommandList10* GetList() { return mList; }
    operator ID3D12CommandList*() { return mList; }
private:
    bool mSingleTime;
    std::shared_ptr<Queue> mParentQueue;

    ID3D12CommandAllocator* mAllocator = nullptr;
    ID3D12GraphicsCommandList10* mList = nullptr;

    std::shared_ptr<RaytracingPipeline> mCurrentRT = nullptr;
};
