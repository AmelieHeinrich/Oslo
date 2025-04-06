//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-03-27 14:19:31
//

#include "Logger.hpp"

#include <iostream>
#include <sstream>
#include <cstdarg>
#include <ctime>
#include <iomanip>
#include <vector>

void ILogger::Log(LogLevel level, const char* file, int line, const char* fmt, va_list args)
{
    char buffer[2048];
    vsnprintf(buffer, sizeof(buffer), fmt, args);  // Format the log message

    std::ostringstream stream;
    stream << "[" << GetCurrentTime() << "] "
           << "[" << file << ":" << line << "] "
           << "[" << ToString(level) << "] "
           << buffer;
    
    Output(level, stream.str());  // Output the formatted message
}

void ILogger::Info(const char* file, int line, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    Log(LogLevel::INFO, file, line, fmt, args);
    va_end(args);
}

void ILogger::Warn(const char* file, int line, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    Log(LogLevel::WARN, file, line, fmt, args);
    va_end(args);
}

void ILogger::Error(const char* file, int line, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    Log(LogLevel::ERROR, file, line, fmt, args);
    va_end(args);
}

void ILogger::Critical(const char* file, int line, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    Log(LogLevel::CRITICAL, file, line, fmt, args);
    va_end(args);
}

void ILogger::Debug(const char* file, int line, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    Log(LogLevel::DEBUG, file, line, fmt, args);
    va_end(args);
}

std::string ILogger::ToString(LogLevel level)
{
    switch (level)
    {
        case LogLevel::INFO: return "INFO";
        case LogLevel::WARN: return "WARN";
        case LogLevel::ERROR: return "ERROR";
        case LogLevel::CRITICAL: return "CRITICAL";
        case LogLevel::DEBUG: return "DEBUG";
        default: return "UNKNOWN";
    }
}

std::string ILogger::GetCurrentTime()
{
    std::time_t now = std::time(nullptr);
    std::tm tm = *std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}
