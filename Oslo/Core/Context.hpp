//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-03-27 14:03:03
//

#pragma once

#include "Memory/MemoryAllocator.hpp"
#include "Logger/Logger.hpp"

class Context
{
public:
    static void Init();
    static void Exit();

    static IMemoryAllocator* Allocator;
    static IMemoryAllocator* TempAllocator;
    static ILogger* Logger;
};

#define LOG_INFO(fmt, ...)      Context::Logger->Info(__FILE__, __LINE__, fmt, __VA_ARGS__)
#define LOG_WARN(fmt, ...)      Context::Logger->Warn(__FILE__, __LINE__, fmt, __VA_ARGS__)
#define LOG_ERROR(fmt, ...)     Context::Logger->Error(__FILE__, __LINE__, fmt, __VA_ARGS__)
#define LOG_CRITICAL(fmt, ...)  Context::Logger->Critical(__FILE__, __LINE__, fmt, __VA_ARGS__)
#define LOG_DEBUG(fmt, ...)     Context::Logger->Debug(__FILE__, __LINE__, fmt, __VA_ARGS__)

#define MEMORY_ALLOC(size)      Context::Allocator->Allocate(size, __LINE__, __FILE__)
#define MEMORY_FREE(block)      Context::Allocator->Free(block)
#define TEMP_MEMORY_ALLOC(size) Context::TempAllocator->Allocate(size, __LINE__, __FILE__)

#define USE_TRACKING_ALLOCATOR \
    static void* operator new(std::size_t size) { return Context::Allocator->Allocate(size, __LINE__, __FILE__); } \
    static void operator delete(void* ptr) noexcept { Context::Allocator->Free(ptr); } \
    static void* operator new[](std::size_t size) { return Context::Allocator->Allocate(size, __LINE__, __FILE__); } \
    static void operator delete[](void* ptr) noexcept { Context::Allocator->Free(ptr); }
