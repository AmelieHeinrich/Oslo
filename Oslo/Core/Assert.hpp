//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-04-06 11:34:27
//

#pragma once

#include <string>

class Assert
{
public:
    static void Check(bool condition, const std::string& fileName, const std::string& function, int line, const std::string& message);
};

#define ASSERT(cond, msg) ::Assert::Check(cond, __FILE__, __FUNCTION__, __LINE__, msg)
