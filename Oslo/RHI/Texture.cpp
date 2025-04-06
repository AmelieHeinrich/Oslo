//
// > Notice: Amélie Heinrich @ 2024
// > Create Time: 2024-12-03 10:52:32
//

#include "Texture.hpp"
#include "RHI.hpp"

#include <Core/UTF.hpp>

Texture::Texture(ID3D12Resource* resource, TextureDesc desc)
    : Resource(), mDesc(desc)
{
    mShouldFree = false;
    mResource = resource;
}

Texture::Texture(TextureDesc desc)
    : Resource(), mDesc(desc)
{
    mShouldFree = true;

    D3D12_HEAP_PROPERTIES heapProperties = {};
    heapProperties.Type = D3D12_HEAP_TYPE_DEFAULT;
    
    D3D12_RESOURCE_DESC resourceDesc = {};
    resourceDesc.Width = desc.Width;
    resourceDesc.Height = desc.Height;
    resourceDesc.DepthOrArraySize = desc.Depth;
    resourceDesc.Format = DXGI_FORMAT(desc.Format);
    resourceDesc.MipLevels = desc.Levels;
    resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
    resourceDesc.SampleDesc.Count = 1;
    resourceDesc.SampleDesc.Quality = 0;
    resourceDesc.Alignment = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT;

    if (desc.Usage & TextureUsage::RenderTarget)
        resourceDesc.Flags |= D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;
    if (desc.Usage & TextureUsage::Storage)
        resourceDesc.Flags |= D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
    if (desc.Usage & TextureUsage::DepthTarget)
        resourceDesc.Flags |= D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
    
    CreateResource(&heapProperties, &resourceDesc, D3D12_RESOURCE_STATE_COMMON);
    SetName(desc.Name);
}

Texture::~Texture()
{
    // Everything will automatically be cleaned up by Resource::~Resource().
}
