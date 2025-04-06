//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-03-27 19:57:34
//

#pragma once

#include <fstream>

#include "Logger.hpp"

class FileLogger : public ILogger
{
public:
    FileLogger(const std::string& path);
    ~FileLogger();
    // ...

protected:
    virtual void Output(LogLevel level, const std::string& format) override;

    std::ofstream mStream;
};
