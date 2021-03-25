
#include "pch.h"

LPMouseAction MouseAction::lpMouseAction = nullptr;
const DWORD MouseAction::directions[3] = {
    MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP,
    MOUSEEVENTF_MIDDLEDOWN | MOUSEEVENTF_MIDDLEUP,
    MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP};

MouseAction::MouseAction(HWND hDlg, DWORD delay, DWORD direction)
    : hDlg(hDlg), delay(delay), direction(direction)
{
}

MouseAction::~MouseAction() {}

bool MouseAction::IsRunning()
{
    return lpMouseAction != nullptr;
}

void MouseAction::StartClick(HWND hDlg)
{
    EnableWindow(GetDlgItem(hDlg, IDC_START), FALSE);
    EnableWindow(GetDlgItem(hDlg, IDC_DELAY), FALSE);
    EnableWindow(GetDlgItem(hDlg, IDC_KEY), FALSE);
    EnableWindow(GetDlgItem(hDlg, IDC_DIRECTION), FALSE);
    EnableWindow(GetDlgItem(hDlg, IDC_RANDOM), FALSE);
    EnableWindow(GetDlgItem(hDlg, IDC_STOP), TRUE);
    {
        wchar_t delay[10];
        GetDlgItemTextW(hDlg, IDC_DELAY, delay, 10);
        lpMouseAction = new MouseAction(hDlg, (DWORD)_wtol(delay), directions[ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_DIRECTION))]);
    }
    CreateThread(nullptr, 0, mouseClickThread, lpMouseAction, 0, nullptr); //&mouseClickThreadID);
}

void MouseAction::StopClick(HWND hDlg)
{
    lpMouseAction->flag = false;
    lpMouseAction = nullptr;
    // ResumeThread(&mouseClickThreadID);
    EnableWindow(GetDlgItem(hDlg, IDC_START), TRUE);
    EnableWindow(GetDlgItem(hDlg, IDC_DELAY), TRUE);
    EnableWindow(GetDlgItem(hDlg, IDC_KEY), TRUE);
    EnableWindow(GetDlgItem(hDlg, IDC_DIRECTION), TRUE);
    EnableWindow(GetDlgItem(hDlg, IDC_RANDOM), TRUE);
    EnableWindow(GetDlgItem(hDlg, IDC_STOP), FALSE);
}

DWORD WINAPI MouseAction::mouseClickThread(LPVOID lpThreadParameter)
{
    LPMouseAction lpMouseAction = (LPMouseAction)lpThreadParameter;
    // only one thread can access this variable
    static auto input = INPUT({ 0, MOUSEINPUT({0L, 0L, 0UL, 0UL, 0UL, 0ULL}) });
    input.mi.dwFlags = lpMouseAction->direction;
    wchar_t sleept[10];
    if (IsDlgButtonChecked(lpMouseAction->hDlg, IDC_RANDOM))
    {
        do
        {
            SendInput(1U, &input, sizeof(INPUT));
            {
                DWORD sleep = rand() % lpMouseAction->delay;
                _itow_s(sleep, sleept, 10);
                SetDlgItemTextW(lpMouseAction->hDlg, IDC_DELAYTRUE, sleept);
                Sleep(sleep);
            }
        } while (lpMouseAction->flag);
    }
    else
    {
        _itow_s(lpMouseAction->delay, sleept, 10);
        SetDlgItemTextW(lpMouseAction->hDlg, IDC_DELAYTRUE, sleept);
        do
        {
            SendInput(1U, &input, sizeof(INPUT));
            Sleep(lpMouseAction->delay);
        } while (lpMouseAction->flag);
    }
    delete lpMouseAction;
    return 0;
}
