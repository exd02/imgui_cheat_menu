#include "Gui.h"

// Main code
int __stdcall wWinMain(
    HINSTANCE instance,
    HINSTANCE previousInstance,
    PWSTR arguments,
    int commandShow)
{
    Gui::CreateHWindow(L"Cheat Menu");
    Gui::CreateDeviceD3D();
    Gui::CreateImGui();

    while (Gui::isRunning) {
        Gui::BeginRender();
        Gui::Render();
        Gui::EndRender();
    }

    Gui::DestroyImGui();
    Gui::CleanupDeviceD3D();
    Gui::DestroyHWindow();

    return 0;
}