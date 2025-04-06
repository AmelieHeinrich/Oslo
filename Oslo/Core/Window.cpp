//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-03-27 13:31:58
//

#include "Window.hpp"

#include <Core/Context.hpp>

Window::Window(uint32_t width, uint32_t height, const std::string& title)
{
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD | SDL_INIT_HAPTIC)) {
        LOG_CRITICAL("Failed to initialize SDL3!");
    }

    mWindow = SDL_CreateWindow(title.c_str(), width, height, 0);
    if (!mWindow) {
        LOG_CRITICAL("Failed to create window!");
    }
}

Window::~Window()
{
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Window::Update()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            mRunning = false;
        }
    }
}

bool Window::IsOpen() const
{
    return mRunning;
}

void Window::GetSize(int& width, int& height)
{
    SDL_GetWindowSize(mWindow, &width, &height);
}
