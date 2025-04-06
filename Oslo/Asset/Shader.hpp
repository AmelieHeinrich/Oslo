//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-04-06 15:26:26
//

#pragma once

#include <Core/Common.hpp>
#include <Agility/d3d12shader.h>

#include <vector>
#include <unordered_map>

enum class ShaderType
{
    None,
    Vertex,
    Pixel,
    Compute,
    Hull,
    Domain,
    Mesh,
    Amplification,
    Library
};

struct ShaderModule
{
    bool Valid;
    ShaderType Type;
    std::vector<uint8_t> Bytecode;
};

struct ShaderFile
{
    std::unordered_map<std::string, ShaderModule> Modules;
};

class ShaderCompiler
{
public:
    static ShaderModule Compile(const std::string& source, const std::string& entry, ShaderType type);
    static ID3D12ShaderReflection* Reflect(ShaderModule shader);

    static ShaderFile Load(const std::string& path);
};