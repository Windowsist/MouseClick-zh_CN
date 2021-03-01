#pragma once

#include "pch.h"

ATOM MyRegisterClass(HINSTANCE hInstance);

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
