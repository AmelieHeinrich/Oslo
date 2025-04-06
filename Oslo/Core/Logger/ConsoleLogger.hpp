//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-03-27 14:27:16
//

#pragma once

#include "Logger.hpp"

class ConsoleLogger : public ILogger
{
public:
    ConsoleLogger() = default;
    ~ConsoleLogger() = default;
    // ...

protected:
    virtual void Output(LogLevel level, const std::string& format) override;
};
