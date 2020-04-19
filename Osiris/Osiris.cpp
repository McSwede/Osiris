#include "Config.h"
#include "GUI.h"
#include "Hooks.h"
#include "Interfaces.h"
#include "Memory.h"
#include "Netvars.h"
#include "AntiDetection.h"

static HMODULE module;
static WNDPROC originalWndproc;

static LRESULT WINAPI init(HWND window, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
    SetWindowLongPtr(FindWindowW(L"Valve001", nullptr), GWLP_WNDPROC, LONG_PTR(originalWndproc));
    config = std::make_unique<Config>("Trigon");
    gui = std::make_unique<GUI>();
    interfaces = std::make_unique<const Interfaces>();
    memory = std::make_unique<Memory>();
    netvars = std::make_unique<Netvars>();
    hooks = std::make_unique<Hooks>(module);
	antiDetection = std::make_unique<AntiDetection>();

    return CallWindowProc(originalWndproc, window, msg, wParam, lParam);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        module = hModule;
        originalWndproc = WNDPROC(SetWindowLongPtr(FindWindowW(L"Valve001", nullptr), GWLP_WNDPROC, LONG_PTR(init)));
    }
    return TRUE;
}
