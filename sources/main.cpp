
#include "App.hpp"
#include <crtdbg.h>

int main() 
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    Core::App::Create();
    Core::App* app = Core::App::Get();

    app->Run("Vulkan", 1920, 1080);
    app->Release();

    delete app;
    return 0;
}