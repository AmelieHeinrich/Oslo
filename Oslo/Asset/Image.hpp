//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-04-06 16:46:13
//

#pragma once

#include <Core/Common.hpp>
#include <vector>
#include <string>

struct ImageData
{
    int Width;
    int Height;
    int Levels;
    bool HDR = false;
    
    std::vector<uint8_t> Pixels;

    void Load(const std::string& path);
    void LoadHDR(const std::string& path);
};
