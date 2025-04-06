//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-03-27 14:12:24
//

#pragma once

#include <Core/Common.hpp>
#include <cstdarg>

enum class LogLevel
{
    INFO,
    WARN,
    ERROR,
    CRITICAL,
    DEBUG
};

class ILogger
{
public:
    virtual ~ILogger() = default;

    void Log(LogLevel level, const char* file, int line, const char* fmt, va_list args);

    void Info(const char* file, int line, const char* fmt, ...);
    void Warn(const char* file, int line, const char* fmt, ...);
    void Error(const char* file, int line, const char* fmt, ...);
    void Critical(const char* file, int line, const char* fmt, ...);
    void Debug(const char* file, int line, const char* fmt, ...);
public:
    virtual void Output(LogLevel level, const std::string& format) = 0;

private:
    std::string ToString(LogLevel level);
    std::string GetCurrentTime();
};
