//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-03-27 13:43:50
//

#include "BasicAllocator.hpp"

#include <cstdlib>
#include <Core/Context.hpp>

void* BasicAllocator::Allocate(uint64_t size, int line, const char* file)
{
    return std::malloc(size);
}

void BasicAllocator::Free(void* block)
{
    return std::free(block);
}

void BasicAllocator::Clear()
{
    LOG_WARN("Basic Allocator does not support clear!");
}
