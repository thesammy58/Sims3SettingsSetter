#pragma once
#include <d3d9.h>
#include <memory>

// Function typedefs
typedef HRESULT(__stdcall* EndScene_t)(LPDIRECT3DDEVICE9);
typedef HRESULT(__stdcall* Reset_t)(LPDIRECT3DDEVICE9, D3DPRESENT_PARAMETERS*);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);

// Global variables
extern LPDIRECT3DDEVICE9 g_pd3dDevice;
extern EndScene_t original_EndScene;
extern Reset_t original_Reset;
extern WNDPROC original_WndProc;
extern HWND g_hookedWindow;

// enableOverlay=false installs the device hooks (needed for borderless window support) but skips ImGui/WndProc entirely
bool InitializeD3D9Hook(bool enableOverlay = true);
void CleanupD3D9Hook();

// Rewrites fullscreen present params to windowed when a borderless mode is configured
// Checks the configured mode rather than IsEnabled(), the applied flag only goes true after the first style apply, which happens after the device already exists
// Returns true if params were modified
bool EnforceBorderlessWindowedParams(D3DPRESENT_PARAMETERS* pPresentationParameters, const char* logTag);

// Hook functions
HRESULT __stdcall HookedEndScene(LPDIRECT3DDEVICE9 pDevice);
HRESULT __stdcall HookedReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
LRESULT CALLBACK HookedWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);