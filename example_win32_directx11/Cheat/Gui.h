#pragma once

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_win32.h"
#include "../imgui/imgui_impl_dx11.h"
#include "Memory.h"

#include <d3d11.h>
#include <tchar.h>

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

class Gui
{
private:
	// Data
	static ID3D11Device* g_pd3dDevice;
	static ID3D11DeviceContext* g_pd3dDeviceContext;
	static IDXGISwapChain* g_pSwapChain;
	static UINT g_ResizeWidth, g_ResizeHeight;
	static ID3D11RenderTargetView* g_mainRenderTargetView;
	static ImGuiWindowFlags window_flags;

	// Windows
	static WNDCLASSEXW wc; // Window Class
	static HWND hwnd; // Window

	static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

public:
	static bool isRunning;
	static bool showInterface;

	static void CreateHWindow(const wchar_t* windowName);
	static void DestroyHWindow();

	static void CreateDeviceD3D();
	static void CleanupDeviceD3D();

	static void CreateRenderTarget();
	static void CleanupRenderTarget();

	static void CreateImGui();
	static void DestroyImGui();

	static void BeginRender();
	static void EndRender();

	static void Render();
};