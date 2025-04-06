//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-04-06 15:26:59
//

#include "Shader.hpp"

#include <RHI/Utils.hpp>

#include <Core/FileIO.hpp>
#include <Core/Context.hpp>
#include <Core/Assert.hpp>

#include <DXC/dxcapi.h>
#include <wrl/client.h>

const char* GetProfileFromType(ShaderType type)
{
    switch (type) {
        case ShaderType::Vertex: {
            return "vs_6_7";
        }
        case ShaderType::Pixel: {
            return "ps_6_7";
        }
        case ShaderType::Compute: {
            return "cs_6_7";
        }
        case ShaderType::Hull: {
            return "hs_6_7";
        }
        case ShaderType::Domain: {
            return "ds_6_7";
        }
        case ShaderType::Mesh: {
            return "ms_6_7";
        }
        case ShaderType::Amplification: {
            return "as_6_7";
        }
        case ShaderType::Library: {
            return "lib_6_7";
        }
    }
    return "???";
}

ShaderModule ShaderCompiler::Compile(const std::string& contents, const std::string& entry, ShaderType type)
{
    ShaderModule result = {};

    const char* source = contents.c_str();

    wchar_t wideTarget[512];
    swprintf_s(wideTarget, 512, L"%hs", GetProfileFromType(type));
    
    wchar_t wideEntry[512];
    swprintf_s(wideEntry, 512, L"%hs", entry.c_str());

    IDxcUtils* pUtils = nullptr;
    IDxcCompiler* pCompiler = nullptr;
    ASSERT(SUCCEEDED(DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&pUtils))), "Failed to create DXC utils!");
    ASSERT(SUCCEEDED(DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&pCompiler))), "Failed too create DXC compiler!");

    IDxcIncludeHandler* pIncludeHandler = nullptr;
    ASSERT(SUCCEEDED(pUtils->CreateDefaultIncludeHandler(&pIncludeHandler)), "Failed to create default include handler!");

    IDxcBlobEncoding* pSourceBlob = nullptr;
    ASSERT(SUCCEEDED(pUtils->CreateBlob(source, contents.size(), 0, &pSourceBlob)), "Failed to create source blob!");

    LPCWSTR pArgs[] = {
        L"-Zi",
        L"-Fd",
        L"-Fre",
        L"-Qembed_debug",
        L"-Wno-payload-access-perf",
        L"-Wno-payload-access-shader"
    };

    IDxcOperationResult* pResult = nullptr;
    ASSERT(SUCCEEDED(pCompiler->Compile(pSourceBlob, L"Shader", wideEntry, wideTarget, pArgs, ARRAYSIZE(pArgs), nullptr, 0, pIncludeHandler, &pResult)), "Failed to create result blob!");

    IDxcBlobEncoding* pErrors = nullptr;
    pResult->GetErrorBuffer(&pErrors);

    if (pErrors && pErrors->GetBufferSize() != 0) {
        IDxcBlobUtf8* pErrorsU8 = nullptr;
        pErrors->QueryInterface(IID_PPV_ARGS(&pErrorsU8));
        LOG_ERROR("[DXC] Shader errors: %s", (char*)pErrorsU8->GetStringPointer());
        pErrorsU8->Release();
        pErrors->Release();
        return { false };
    }

    HRESULT Status;
    pResult->GetStatus(&Status);

    IDxcBlob* pShaderBlob = nullptr;
    pResult->GetResult(&pShaderBlob);

    result.Type = type;
    result.Bytecode.resize(pShaderBlob->GetBufferSize());
    memcpy(result.Bytecode.data(), pShaderBlob->GetBufferPointer(), pShaderBlob->GetBufferSize());

    D3DUtils::Release(pShaderBlob);
    D3DUtils::Release(pErrors);
    D3DUtils::Release(pResult);
    D3DUtils::Release(pSourceBlob);
    D3DUtils::Release(pIncludeHandler);
    D3DUtils::Release(pCompiler);
    D3DUtils::Release(pUtils);
    return result;
}

ID3D12ShaderReflection* ShaderCompiler::Reflect(ShaderModule shader)
{
    ID3D12ShaderReflection* pReflection = nullptr;
    
    IDxcUtils* pUtils = nullptr;
    DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&pUtils));
    
    DxcBuffer ShaderBuffer = {};
    ShaderBuffer.Ptr = shader.Bytecode.data();
    ShaderBuffer.Size = shader.Bytecode.size();
    
    ASSERT(SUCCEEDED(pUtils->CreateReflection(&ShaderBuffer, IID_PPV_ARGS(&pReflection))), "Failed to get shader reflection!");
    pUtils->Release();
    return pReflection;
}

ShaderFile ShaderCompiler::Load(const std::string& path)
{
    std::string source = FileIO::ReadEntireFile(path);
    if (source == "") {
        LOG_ERROR("Failed to read shader record!");
        return {};
    }

    std::unordered_map<std::string, ShaderType> entryPoints;

    std::vector<std::string> lines = FileIO::ReadLines(path);
    for (std::string line : lines) {
        if (line.find("#pragma vertex") != std::string::npos) {
            line = line.substr(std::string("#pragma vertex ").length());
            entryPoints[line] = ShaderType::Vertex;
        }
        if (line.find("#pragma pixel") != std::string::npos) {
            line = line.substr(std::string("#pragma pixel ").length());
            entryPoints[line] = ShaderType::Pixel;
        }
        if (line.find("#pragma kernel") != std::string::npos) {
            line = line.substr(std::string("#pragma kernel ").length());
            entryPoints[line] = ShaderType::Compute;
        }
        if (line.find("#pragma domain") != std::string::npos) {
            line = line.substr(std::string("#pragma domain ").length());
            entryPoints[line] = ShaderType::Domain;
        }
        if (line.find("#pragma hull") != std::string::npos) {
            line = line.substr(std::string("#pragma hull ").length());
            entryPoints[line] = ShaderType::Hull;
        }
        if (line.find("#pragma mesh") != std::string::npos) {
            line = line.substr(std::string("#pragma mesh ").length());
            entryPoints[line] = ShaderType::Mesh;
        }
        if (line.find("#pragma amplification") != std::string::npos) {
            line = line.substr(std::string("#pragma amplification ").length());
            entryPoints[line] = ShaderType::Amplification;
        }
        if (line.find("#pragma rt_library") != std::string::npos) {
            entryPoints["Shader"] = ShaderType::Library;
        }
    }

    ShaderFile record = {};
    for (auto& [entry, type] : entryPoints) {
        record.Modules[entry] = ShaderCompiler::Compile(source, entry, type);
    }
    LOG_INFO("Compiled shader file: %s", path.c_str());

    return record;
}
