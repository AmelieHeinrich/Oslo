//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-03-27 19:58:16
//

#include "FileLogger.hpp"

FileLogger::FileLogger(const std::string& path)
{
    mStream.open(path, std::ios::trunc | std::ios::out);
    if (!mStream.is_open()) {
        Output(LogLevel::CRITICAL, "Failed to open output file!");
    }
}

FileLogger::~FileLogger()
{
    mStream.close();
}

void FileLogger::Output(LogLevel level, const std::string& format)
{
    mStream << format << std::endl;
}
