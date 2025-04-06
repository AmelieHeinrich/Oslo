//
// > Notice: Amélie Heinrich @ 2024
// > Create Time: 2024-12-03 10:30:38
//

#pragma once

#include <RHI/Device.hpp>
#include <RHI/Resource.hpp>

enum class TextureFormat
{
    Unknown = DXGI_FORMAT_UNKNOWN, ///< Unknown texture format.
    RGBA8 = DXGI_FORMAT_R8G8B8A8_UNORM, ///< 8-bit per channel RGBA texture (unsigned normalized).
    RGBA8_sRGB = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, ///< 8-bit per channel RGBA texture in sRGB space.
    RGBA16Float = DXGI_FORMAT_R16G16B16A16_FLOAT, ///< 16-bit floating point RGBA texture.
    RGBA16Unorm = DXGI_FORMAT_R16G16B16A16_UNORM, ///< 16-bit unsigned normalized RGBA texture.
    RGBA32Float = DXGI_FORMAT_R32G32B32A32_FLOAT, ///< 32-bit floating point RGBA texture.
    RGB11Float = DXGI_FORMAT_R11G11B10_FLOAT, ///< RGB texture with 11 bits for RGB and 10 bits for the alpha channel.
    RG8 = DXGI_FORMAT_R8G8_UNORM, ///< 8-bit per channel RG texture.
    RG16Float = DXGI_FORMAT_R16G16_FLOAT, ///< 16-bit per channel floating point RG texture.
    R8 = DXGI_FORMAT_R8_UNORM, ///< 8-bit single channel texture.
    BC3 = DXGI_FORMAT_BC3_UNORM, ///< BC3 compressed texture format.
    BC6H = DXGI_FORMAT_BC6H_UF16, ///< 16-bit unsigned float BC6H texture format.
    BC7 = DXGI_FORMAT_BC7_UNORM, ///< BC7 compressed texture format.
    R32Float = DXGI_FORMAT_R32_FLOAT, ///< 32-bit floating point R texture.
    Depth32 = DXGI_FORMAT_D32_FLOAT ///< Depth texture with 32-bit floating point precision.
};

enum class TextureUsage
{
    RenderTarget = BIT(1),
    DepthTarget = BIT(2),
    Storage = BIT(3),
    ShaderResource = BIT(4)
};

struct TextureDesc
{
    std::string Name;
    uint32_t Width;
    uint32_t Height;
    uint32_t Depth;
    uint32_t Levels;
    TextureFormat Format;
    TextureUsage Usage;
};

class Texture : public Resource
{
public:
    Texture(ID3D12Resource* resource, TextureDesc desc);
    Texture(TextureDesc desc);
    ~Texture();

    TextureDesc GetDesc() const { return mDesc; }
private:
    TextureDesc mDesc;
};

inline constexpr bool operator&(TextureUsage x, TextureUsage y)
{
    return static_cast<uint32_t>(x) & static_cast<uint32_t>(y);
}

inline constexpr TextureUsage operator|(TextureUsage x, TextureUsage y)
{
    return static_cast<TextureUsage>(static_cast<uint32_t>(x) | static_cast<uint32_t>(y));
}

inline constexpr TextureUsage operator^(TextureUsage x, TextureUsage y)
{
    return static_cast<TextureUsage>(static_cast<uint32_t>(x) ^ static_cast<uint32_t>(y));
}

inline constexpr TextureUsage operator~(TextureUsage x)
{
    return static_cast<TextureUsage>(~static_cast<uint32_t>(x));
}

inline TextureUsage& operator|=(TextureUsage & x, TextureUsage y)
{
    x = x | y;
    return x;
}

inline TextureUsage& operator^=(TextureUsage & x, TextureUsage y)
{
    x = x ^ y;
    return x;
}
