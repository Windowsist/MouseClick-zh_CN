#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <windows.h>
#include <windowsx.h>
#include "resource.h"

typedef struct
{
    bool flag;
    HWND hDlg;
    DWORD delay, direction;
} MouseAction, *LPMouseAction;

ATOM MyRegisterClass(HINSTANCE hInstance);

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

DWORD WINAPI mouseClickThread(LPVOID lpThreadParameter);
