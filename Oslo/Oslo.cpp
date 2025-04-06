//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-04-06 11:15:44
//

#include "Oslo.hpp"

#include "RHI/RHI.hpp"

void Oslo::Init()
{
    Context::Init();
    RHI::Init();
}

void Oslo::AttachWindow(std::shared_ptr<Window> window)
{
    RHI::ConnectWindow(window);
}

void Oslo::Exit()
{
    RHI::Exit();
    Context::Allocator->Report();
    Context::Exit();
}
