#include "main.h"

int
    WINAPI
    wWinMain(_In_ HINSTANCE hInstance,
             _In_opt_ HINSTANCE hPrevInstance,
             _In_ LPWSTR lpCmdLine,
             _In_ int nCmdShow)
{
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    // 主消息循环:
    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    return (int)msg.wParam;
}

//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = DefDlgProcW;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = DLGWINDOWEXTRA;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIconW(hInstance, MAKEINTRESOURCEW(IDI_ICON1));
    wcex.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = L"MouseClickDlg";
    wcex.hIconSm = wcex.hIcon;

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    HWND hDlg = CreateDialogParamW(hInstance, MAKEINTRESOURCEW(IDD_DIALOG1), nullptr, DlgProc, 0L);

    if (!hDlg)
    {
        return FALSE;
    }

    if (!RegisterHotKey(hDlg, 1, MOD_NOREPEAT | MOD_CONTROL, VK_F1)) //0x42 is 'b'
    {
        MessageBoxW(nullptr, L"注册快捷键失败", L"警告", MB_ICONWARNING);
    }

    if (!RegisterHotKey(hDlg, 2, MOD_NOREPEAT, VK_F1)) //0x42 is 'b'
    {
        MessageBoxW(nullptr, L"注册快捷键失败", L"警告", MB_ICONWARNING);
    }

    ShowWindow(hDlg, nCmdShow);
    UpdateWindow(hDlg);
    return TRUE;
}

// 对话框的消息处理程序。
INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
        mouse.Dlg = hDlg;
        mouse.ComboKey = GetDlgItem(hDlg, IDC_KEY);
        mouse.ComboDirection = GetDlgItem(hDlg, IDC_DIRECTION);
        mouse.CheckRandom = GetDlgItem(hDlg, IDC_RANDOM);
        mouse.TextDelay = GetDlgItem(hDlg, IDC_DELAY);
        mouse.ButtonStart = GetDlgItem(hDlg, IDC_START);
        mouse.ButtonStop = GetDlgItem(hDlg, IDC_STOP);
        SetDlgItemText(hDlg, IDC_DELAY, L"1000");
        SetDlgItemText(hDlg, IDC_COUNT, L"0");
        ComboBox_AddItemData(mouse.ComboDirection, L"鼠标左键");
        ComboBox_AddItemData(mouse.ComboDirection, L"鼠标中键");
        ComboBox_AddItemData(mouse.ComboDirection, L"鼠标右键");
        ComboBox_SetCurSel(mouse.ComboDirection, 0);
        ComboBox_AddItemData(mouse.ComboKey, L"F1");
        ComboBox_AddItemData(mouse.ComboKey, L"F2");
        ComboBox_AddItemData(mouse.ComboKey, L"F3");
        ComboBox_AddItemData(mouse.ComboKey, L"F4");
        ComboBox_AddItemData(mouse.ComboKey, L"F5");
        ComboBox_AddItemData(mouse.ComboKey, L"F6");
        ComboBox_AddItemData(mouse.ComboKey, L"F7");
        ComboBox_AddItemData(mouse.ComboKey, L"F8");
        ComboBox_AddItemData(mouse.ComboKey, L"F9");
        ComboBox_AddItemData(mouse.ComboKey, L"F10");
        ComboBox_AddItemData(mouse.ComboKey, L"F11");
        ComboBox_AddItemData(mouse.ComboKey, L"F12");
        ComboBox_SetCurSel(mouse.ComboKey, 0);
        return (INT_PTR)TRUE;
    case WM_HOTKEY:
        if (HIWORD(wParam) == mouse.HotKey)
        {
            if ((lParam & MOD_CONTROL) == MOD_CONTROL)
            {
                static bool shown = true;
                if (shown)
                {
                    shown = false;
                    ShowWindow(hDlg, SW_HIDE);
                }
                else
                {
                    shown = true;
                    ShowWindow(hDlg, SW_SHOW);
                }
            }
            else if (mouse.flag)
                ClickedStop();
            else
                ClickedStart();
            return (INT_PTR)TRUE;
        }
        break;
    case WM_COMMAND:
        if (HIWORD(wParam) == CBN_SELCHANGE)
        {
            if ((HWND)lParam == mouse.ComboKey)
            {
                mouse.HotKey = mouse.HotKeys[ComboBox_GetCurSel(mouse.ComboKey)];
                UnregisterHotKey(hDlg, 1);
                UnregisterHotKey(hDlg, 2);
                if (!RegisterHotKey(hDlg, 1, MOD_NOREPEAT | MOD_CONTROL, mouse.HotKey)) //0x42 is 'b'
                {
                    MessageBoxW(hDlg, L"注册快捷键失败", L"警告", MB_ICONWARNING);
                }
                if (!RegisterHotKey(hDlg, 2, MOD_NOREPEAT, mouse.HotKey)) //0x42 is 'b'
                {
                    MessageBoxW(hDlg, L"注册快捷键失败", L"警告", MB_ICONWARNING);
                }
                return (INT_PTR)TRUE;
            }
        }
        else
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择:
            switch (wmId)
            {
            case IDC_START:
                ClickedStart();
                return (INT_PTR)TRUE;
            case IDC_STOP:
                ClickedStop();
                return (INT_PTR)TRUE;
            case IDC_TEST:
            case IDC_RESET:
            {
                static int count = 0;
                switch (wmId)
                {
                case IDC_TEST:
                    wchar_t countt[10];
                    SetDlgItemTextW(mouse.Dlg, IDC_COUNT, _itow(++count, countt, 10));
                    break;
                case IDC_RESET:
                    SetDlgItemTextW(mouse.Dlg, IDC_COUNT, L"0");
                    count = 0;
                    break;
                }
                return (INT_PTR)TRUE;
            }
            }
        }
        break;
    case WM_CLOSE:
        DestroyWindow(hDlg);
        return (INT_PTR)TRUE;
    case WM_DESTROY:
        PostQuitMessage(0);
        return (INT_PTR)TRUE;
    }
    return (INT_PTR)FALSE;
}

void ClickedStart()
{
    mouse.flag = true;
    EnableWindow(mouse.ButtonStart, FALSE);
    EnableWindow(mouse.TextDelay, FALSE);
    EnableWindow(mouse.ComboKey, FALSE);
    EnableWindow(mouse.ComboDirection, FALSE);
    EnableWindow(mouse.CheckRandom, FALSE);
    EnableWindow(mouse.ButtonStop, TRUE);
    wchar_t delay[10];
    GetDlgItemTextW(mouse.Dlg, IDC_DELAY, delay, 10);
    mouse.delay = _wtol(delay);
    CreateThread(nullptr, 0, &mouseClickThread, nullptr, 0, nullptr); //&mouse.mouseClickThreadID);
}

void ClickedStop()
{
    mouse.flag = false;
    // ResumeThread(&mouse.mouseClickThreadID);
    EnableWindow(mouse.ButtonStart, TRUE);
    EnableWindow(mouse.TextDelay, TRUE);
    EnableWindow(mouse.ComboKey, TRUE);
    EnableWindow(mouse.ComboDirection, TRUE);
    EnableWindow(mouse.CheckRandom, TRUE);
    EnableWindow(mouse.ButtonStop, FALSE);
}

DWORD WINAPI mouseClickThread(LPVOID lpThreadParameter)
{
    int directioni = ComboBox_GetCurSel(mouse.ComboDirection);
    if (IsDlgButtonChecked(mouse.Dlg, IDC_RANDOM))
    {
        DWORD sleep;
        wchar_t sleept[10];
        do
        {
            mouse_event(mouse.directions[directioni], 0, 0, 0, 0);
            sleep = rand() % mouse.delay;
            SetDlgItemTextW(mouse.Dlg, IDC_DELAY, _itow(sleep, sleept, 10));
            Sleep(sleep);
        } while (mouse.flag);
    }
    else
    {
        do
        {
            mouse_event(mouse.directions[directioni], 0, 0, 0, 0);
            Sleep(mouse.delay);
        } while (mouse.flag);
    }
    return 0;
}
