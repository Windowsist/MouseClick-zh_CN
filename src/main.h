#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <windows.h>
#include <windowsx.h>
#include "resource.h"

struct
{
    HICON icon;
    HWND Dlg,
        ComboKey, ComboDirection,
        CheckRandom,
        TextDelay,
        ButtonStart, ButtonStop;
    LPDWORD mouseClickThreadID = nullptr;
    bool flag = false;
    BOOL isRandomDelay = FALSE;
    DWORD delay = 1000L;
    UINT HotKeys[12] =
        {
            VK_F1,
            VK_F2,
            VK_F3,
            VK_F4,
            VK_F5,
            VK_F6,
            VK_F7,
            VK_F8,
            VK_F9,
            VK_F10,
            VK_F11,
            VK_F12};
    int direction = 0;
} mouse;

INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

void ClickedStart();

void ClickedStop();

DWORD WINAPI mouseClickThread(LPVOID lpThreadParameter);
