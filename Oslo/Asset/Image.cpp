//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-04-06 16:47:53
//

#include "Image.hpp"

#include <stb_image.h>
#include <Core/Context.hpp>

void ImageData::Load(const std::string& path)
{
    int channels = 0;
    stbi_uc* buffer = stbi_load(path.c_str(), &Width, &Height, &channels, STBI_rgb_alpha);
    if (!buffer) {
        LOG_ERROR("Failed to load bitmap %s", path);
        return;
    }

    Pixels.resize(Width * Height * 4);
    Levels = 1;
    memcpy(Pixels.data(), buffer, Pixels.size());
    delete buffer;
}

void ImageData::LoadHDR(const std::string& path)
{
    HDR = true;

    int channels = 0;
    stbi_us* buffer = stbi_load_16(path.c_str(), &Width, &Height, &channels, STBI_rgb_alpha);
    if (!buffer) {
        LOG_ERROR("Failed to load bitmap %s", path);
        return;
    }

    Pixels.resize(Width * Height * 4 * sizeof(short));
    Levels = 1;
    memcpy(Pixels.data(), buffer, Pixels.size());
    delete buffer;
}
