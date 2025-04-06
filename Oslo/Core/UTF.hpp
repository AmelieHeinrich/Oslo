//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-04-06 11:37:21
//

#pragma once

#include <string>

class UTF
{
public:
    static std::string WideToAscii(const wchar_t* text);
    static std::string WideToAscii(const std::wstring& text);
    static std::wstring AsciiToWide(const char* text);
    static std::wstring AsciiToWide(const std::string& text);
};
