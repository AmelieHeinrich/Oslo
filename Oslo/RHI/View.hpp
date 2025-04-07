//
// > Notice: Amélie Heinrich @ 2024
// > Create Time: 2024-12-03 11:03:43
//

#pragma once

#include <RHI/Resource.hpp>
#include <RHI/DescriptorHeap.hpp>
#include <RHI/Texture.hpp>

enum class ViewType
{
    None,
    RenderTarget,
    DepthTarget,
    ShaderResource,
    Storage
};

enum class ViewDimension
{
    Buffer,
    Texture,
    TextureCube
};

constexpr uint64_t VIEW_ALL_MIPS = 0xFFFFFFFF;

class View
{
public:
    View(std::shared_ptr<Resource> resource, ViewType type, ViewDimension dimension = ViewDimension::Texture, TextureFormat format = TextureFormat::Unknown, uint64_t mip = VIEW_ALL_MIPS, uint64_t depthSlice = 0);
    ~View();

    DescriptorHeap::Descriptor GetDescriptor() { return mDescriptor; }
    std::shared_ptr<Resource> GetParentResource() { return mParent; }
    ViewType GetType() { return mType; }
    ViewDimension GetDimension() { return mDimension; }
private:
    DescriptorHeap::Descriptor mDescriptor;
    std::shared_ptr<Resource> mParent = nullptr;
    ViewType mType;
    ViewDimension mDimension;
};
