//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-04-06 11:15:00
//

#pragma once

#include <memory>

#include "Asset/Image.hpp"
#include "Asset/Shader.hpp"

#include "Core/Assert.hpp"
#include "Core/Common.hpp"
#include "Core/Context.hpp"
#include "Core/FileIO.hpp"
#include "Core/UTF.hpp"
#include "Core/Window.hpp"

#include "RHI/AccelerationStructure.hpp"
#include "RHI/BLAS.hpp"
#include "RHI/Buffer.hpp"
#include "RHI/CommandBuffer.hpp"
#include "RHI/ComputePipeline.hpp"
#include "RHI/DescriptorHeap.hpp"
#include "RHI/Device.hpp"
#include "RHI/Fence.hpp"
#include "RHI/GraphicsPipeline.hpp"
#include "RHI/MeshPipeline.hpp"
#include "RHI/Queue.hpp"
#include "RHI/RaytracingPipeline.hpp"
#include "RHI/Resource.hpp"
#include "RHI/RHI.hpp"
#include "RHI/RootSignature.hpp"
#include "RHI/Sampler.hpp"
#include "RHI/Texture.hpp"
#include "RHI/TLAS.hpp"
#include "RHI/Uploader.hpp"
#include "RHI/Utils.hpp"
#include "RHI/View.hpp"

namespace Oslo
{
    void Init();
    void AttachWindow(std::shared_ptr<Window> window);
    void Exit();
}
