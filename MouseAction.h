#pragma once

struct MouseAction;

typedef MouseAction* LPMouseAction;

struct MouseAction
{
    static bool IsRunning();
    static void StartClick(HWND hDlg);
    static void StopClick(HWND hDlg);
private:
    // DWORD mouseClickThreadID;
    bool flag = true;
    const HWND hDlg;
    const DWORD delay, direction;
    static LPMouseAction lpMouseAction;
    static const DWORD directions[3];
    MouseAction(HWND hDlg, DWORD delay, DWORD direction);
    ~MouseAction();
    static DWORD WINAPI mouseClickThread(LPMouseAction lpMouseAction);
};