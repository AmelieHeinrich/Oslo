//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-03-27 20:01:56
//

#pragma once

#include <vector>

#include "Logger.hpp"

class MultiLogger : public ILogger
{
public:
    MultiLogger();
    ~MultiLogger();
    
    void AddLogger(ILogger* logger);
protected:
    virtual void Output(LogLevel level, const std::string& format) override;

    std::vector<ILogger*> mLoggers;
};
