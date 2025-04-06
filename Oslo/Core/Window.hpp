//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-03-27 13:29:51
//

#pragma once

#include <SDL3/SDL.h>
#include <Core/Context.hpp>

#include "Common.hpp"

class Window
{
public:
    USE_TRACKING_ALLOCATOR

    Window(uint32_t width, uint32_t height, const std::string& title);
    ~Window();

    void Update();
    bool IsOpen() const;

    void GetSize(int& width, int& height);
    
    SDL_Window* GetWindow() { return mWindow; }
private:
    SDL_Window* mWindow = nullptr;
    bool mRunning = true;
};
