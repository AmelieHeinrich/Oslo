//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-04-06 11:34:54
//

#include "Assert.hpp"

#include <Windows.h>
#include <Core/Context.hpp>

void Assert::Check(bool condition, const std::string& fileName, const std::string& function, int line, const std::string& message)
{
    if (!condition) {
        LOG_CRITICAL("ASSERTION FAILED (%s:%s - line %d): %s", fileName.c_str(), function.c_str(), line, message.c_str());
        MessageBoxA(nullptr, "Assertion Failed! Check output or log files. for details.", "OSLO", MB_OK | MB_ICONERROR);
        __debugbreak();
    }
}
