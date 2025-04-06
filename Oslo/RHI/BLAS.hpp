//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-04-06 16:01:04
//

#pragma once

#include "AccelerationStructure.hpp"

class BLAS : public AccelerationStructure
{
public:
    BLAS(std::shared_ptr<Buffer> vertex, std::shared_ptr<Buffer> index, uint32_t vtxCount, uint32_t idxCount, const std::string& name = "BLAS");
    ~BLAS() = default;
private:
    D3D12_RAYTRACING_GEOMETRY_DESC mGeometryDesc;
};
