//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-04-06 16:02:15
//

#include "BLAS.hpp"

BLAS::BLAS(std::shared_ptr<Buffer> vertex, std::shared_ptr<Buffer> index, uint32_t vtxCount, uint32_t idxCount, const std::string& name)
    : AccelerationStructure()
{
    mGeometryDesc = {};
    mGeometryDesc.Type = D3D12_RAYTRACING_GEOMETRY_TYPE_TRIANGLES;
    mGeometryDesc.Flags = D3D12_RAYTRACING_GEOMETRY_FLAG_OPAQUE;
    mGeometryDesc.Triangles.IndexBuffer = index->GetAddress();
    mGeometryDesc.Triangles.IndexCount = idxCount;
    mGeometryDesc.Triangles.IndexFormat = DXGI_FORMAT_R32_UINT;
    mGeometryDesc.Triangles.VertexCount = vtxCount;
    mGeometryDesc.Triangles.VertexFormat = DXGI_FORMAT_R32G32B32_FLOAT;
    mGeometryDesc.Triangles.VertexBuffer.StartAddress = vertex->GetAddress();
    mGeometryDesc.Triangles.VertexBuffer.StrideInBytes = vertex->GetStride();
    mGeometryDesc.Triangles.Transform3x4 = 0;

    mInputs = {};
    mInputs.Type = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL;
    mInputs.Flags = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_PREFER_FAST_TRACE;
    mInputs.NumDescs = 1;
    mInputs.DescsLayout = D3D12_ELEMENTS_LAYOUT_ARRAY;
    mInputs.pGeometryDescs = &mGeometryDesc;

    Allocate(name);
}
