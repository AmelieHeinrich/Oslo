//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-04-06 11:14:48
//

#include <Oslo/Oslo.hpp>
#include <memory>

int main(void)
{
    Oslo::Init();

    std::shared_ptr<Window> window = std::make_shared<Window>(1280, 720, "Hello, World!");
    while (window->IsOpen()) {
        window->Update();
    }
    
    Oslo::Exit();
}
