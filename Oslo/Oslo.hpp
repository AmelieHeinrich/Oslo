//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-04-06 11:15:00
//

#pragma once

#include <memory>

#include "Core/Context.hpp"
#include "Core/FileIO.hpp"
#include "Core/Window.hpp"

#include "RHI/RHI.hpp"

namespace Oslo
{
    void Init();
    void AttachWindow(std::shared_ptr<Window> window);
    void Exit();
}
