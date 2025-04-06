//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-04-06 11:15:44
//

#include "Oslo.hpp"

void Oslo::Init()
{
    Context::Init();
}

void Oslo::Exit()
{
    Context::Allocator->Report();
    Context::Exit();
}
