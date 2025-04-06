//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-03-27 20:02:56
//

#include "MultiLogger.hpp"

MultiLogger::MultiLogger()
{

}

MultiLogger::~MultiLogger()
{
    for (ILogger* logger : mLoggers) {
        delete logger;
    }
    mLoggers.clear();
}
    
void MultiLogger::AddLogger(ILogger* logger)
{
    mLoggers.push_back(logger);
}

void MultiLogger::Output(LogLevel level, const std::string& format)
{
    for (ILogger* logger : mLoggers) {
        logger->Output(level, format);
    }
}
