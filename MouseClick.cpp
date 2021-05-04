
#include "pch.h"
#include "MouseClick.h"
#include "StringTable.h"
#include "MouseAction.h"
#include "resource.h"

int
WINAPI
wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE /* hPrevInstance */,
    _In_ LPWSTR /* lpCmdLine */,
    _In_ int nShowCmd
)
{
    StringTableInit(hInstance);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance(hInstance, nShowCmd))
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
    ExitProcess((int)msg.wParam);
    return 0;
}

//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSW wcex;

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = DefDlgProcW;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = DLGWINDOWEXTRA;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIconW(hInstance, MAKEINTRESOURCEW(IDI_ICON1));
    wcex.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = szClassName;

    return RegisterClassW(&wcex);
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
        MessageBoxW(nullptr, szRegisterHotKeyFailed, szWarning, MB_ICONWARNING);
    }

    if (!RegisterHotKey(hDlg, 2, MOD_NOREPEAT, VK_F1)) //0x42 is 'b'
    {
        MessageBoxW(nullptr, szRegisterHotKeyFailed, szWarning, MB_ICONWARNING);
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
        SetDlgItemTextW(hDlg, IDC_DELAY, szDefaultDelay);
        SetDlgItemTextW(hDlg, IDC_DELAYTRUE, szDefaultDelay);
        SetDlgItemTextW(hDlg, IDC_COUNT, szDefaultCount);
        {
            HWND comboDir = GetDlgItem(hDlg, IDC_DIRECTION);
            ComboBox_AddItemData(comboDir, szMouseL);
            ComboBox_AddItemData(comboDir, szMouseM);
            ComboBox_AddItemData(comboDir, szMouseR);
            ComboBox_SetCurSel(comboDir, 0);
        }
        {
            HWND comboKey = GetDlgItem(hDlg, IDC_KEY);
            ComboBox_AddItemData(comboKey, szVK_F1);
            ComboBox_AddItemData(comboKey, szVK_F2);
            ComboBox_AddItemData(comboKey, szVK_F3);
            ComboBox_AddItemData(comboKey, szVK_F4);
            ComboBox_AddItemData(comboKey, szVK_F5);
            ComboBox_AddItemData(comboKey, szVK_F6);
            ComboBox_AddItemData(comboKey, szVK_F7);
            ComboBox_AddItemData(comboKey, szVK_F8);
            ComboBox_AddItemData(comboKey, szVK_F9);
            ComboBox_AddItemData(comboKey, szVK_F10);
            ComboBox_AddItemData(comboKey, szVK_F11);
            ComboBox_AddItemData(comboKey, szVK_F12);
            ComboBox_SetCurSel(comboKey, 0);
        }
        return (INT_PTR)TRUE;
    case WM_HOTKEY:
    {
        switch (wParam)
        {
        case 1:
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
        return (INT_PTR)TRUE;
        case 2:
            if (MouseAction::IsRunning())
            {
                MouseAction::StopClick(hDlg);
            }
            else
            {

                MouseAction::StartClick(hDlg);
            }
            return (INT_PTR)TRUE;
        }
        return (INT_PTR)FALSE;
    }
    break;
    case WM_COMMAND:
        if (HIWORD(wParam) == CBN_SELCHANGE)
        {
            if ((HWND)lParam == GetDlgItem(hDlg, IDC_KEY))
            {
                UnregisterHotKey(hDlg, 1);
                UnregisterHotKey(hDlg, 2);
                {
                    static UINT HotKeys[12] =
                    { VK_F1, VK_F2, VK_F3, VK_F4, VK_F5, VK_F6, VK_F7, VK_F8, VK_F9, VK_F10, VK_F11, VK_F12 };
                    UINT hotKey = HotKeys[ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_KEY))];
                    if (!RegisterHotKey(hDlg, 1, MOD_NOREPEAT | MOD_CONTROL, hotKey)) //0x42 is 'b'
                    {
                        MessageBoxW(hDlg, szRegisterHotKeyFailed, szWarning, MB_ICONWARNING);
                    }
                    if (!RegisterHotKey(hDlg, 2, MOD_NOREPEAT, hotKey)) //0x42 is 'b'
                    {
                        MessageBoxW(hDlg, szRegisterHotKeyFailed, szWarning, MB_ICONWARNING);
                    }
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
            case IDC_RANDOM:
                if (IsDlgButtonChecked(hDlg, IDC_RANDOM))
                {
                    SetDlgItemTextW(hDlg, IDC_DELAYLABEL, szDelayMaxstr);
                }
                else
                {
                    SetDlgItemTextW(hDlg, IDC_DELAYLABEL, szDelaystr);
                }
                break;
            case IDC_STOP:
                MouseAction::StopClick(hDlg);
                return (INT_PTR)TRUE;
            case IDC_START:
                MouseAction::StartClick(hDlg);
                return (INT_PTR)TRUE;
            case IDC_TEST:
            case IDC_RESET:
            {
                static DWORD count = 0;
                switch (wmId)
                {
                case IDC_TEST:
                {
                    wchar_t countt[10];
                    _itow_s(++count, countt, 10);
                    SetDlgItemTextW(hDlg, IDC_COUNT, countt);
                }
                break;
                case IDC_RESET:
                    SetDlgItemTextW(hDlg, IDC_COUNT, szDefaultCount);
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
