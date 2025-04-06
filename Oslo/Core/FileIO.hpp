//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-04-03 18:12:31
//

#pragma once

#include <vector>

#include "Common.hpp"

class FileIO
{
public:
    static std::string ReadEntireFile(const std::string& path);
    static std::vector<std::string> ReadLines(const std::string& path);
};
