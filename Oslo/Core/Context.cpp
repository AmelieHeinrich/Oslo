//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-03-27 14:05:02
//

#include "Context.hpp"

#include "Memory/TrackingAllocator.hpp"
#include "Memory/ArenaAllocator.hpp"
#include "Memory/BasicAllocator.hpp"

#include "Logger/ConsoleLogger.hpp"
#include "Logger/MultiLogger.hpp"
#include "Logger/FileLogger.hpp"

ILogger* Context::Logger;
IMemoryAllocator* Context::Allocator;
IMemoryAllocator* Context::TempAllocator;

void Context::Init()
{
    MultiLogger* multiLogger = new MultiLogger;
    multiLogger->AddLogger(new FileLogger("log.txt"));

    Logger = multiLogger;
    if (IsDebugEnabled()) {
        multiLogger->AddLogger(new ConsoleLogger);
        Allocator = new TrackingAllocator;
    } else {
        Allocator = new BasicAllocator;
    }

    TempAllocator = new ArenaAllocator(8 * MEGABYTE);
    
    LOG_INFO("Initialized context.");
}

void Context::Exit()
{
    LOG_INFO("Deleting context.");

    delete TempAllocator;
    delete Allocator;
    delete Logger;
}
