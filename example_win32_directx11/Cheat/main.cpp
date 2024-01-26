#include "Gui.h"

void toggleInterfaceOnKey(int key)
{
    if (GetAsyncKeyState(key) & 1) {
        Gui::showInterface = !Gui::showInterface;
    }
}

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
        toggleInterfaceOnKey(VK_INSERT);

        Gui::BeginRender();
        Gui::Render();
        Gui::EndRender();

        // TODO: add timer in loop
    }

    Gui::DestroyImGui();
    Gui::CleanupDeviceD3D();
    Gui::DestroyHWindow();

    return 0;
}