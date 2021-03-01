#include "StringTable.h"

#define LOADS(x) LoadStringW(hInstance, IDS_##x, (LPWSTR)&sz##x, 0)

void StringTableInit(HINSTANCE hInstance)
{
    LOADS(ClassName);
    LOADS(ClassName);
    LOADS(RegisterHotKeyFailed);
    LOADS(Warning);
    LOADS(DefaultDelay);
    LOADS(Delaystr);
    LOADS(DelayMaxstr);
    LOADS(DefaultCount);
    LOADS(MouseL);
    LOADS(MouseM);
    LOADS(MouseR);
    LOADS(VK_F1);
    LOADS(VK_F2);
    LOADS(VK_F3);
    LOADS(VK_F4);
    LOADS(VK_F5);
    LOADS(VK_F6);
    LOADS(VK_F7);
    LOADS(VK_F8);
    LOADS(VK_F9);
    LOADS(VK_F10);
    LOADS(VK_F11);
    LOADS(VK_F12);
}

LPWSTR szClassName;
LPWSTR szRegisterHotKeyFailed;
LPWSTR szWarning;
LPWSTR szDefaultDelay;
LPWSTR szDelaystr;
LPWSTR szDelayMaxstr;
LPWSTR szDelay;
LPWSTR szDefaultCount;
LPWSTR szMouseL;
LPWSTR szMouseM;
LPWSTR szMouseR;
LPWSTR szVK_F1;
LPWSTR szVK_F2;
LPWSTR szVK_F3;
LPWSTR szVK_F4;
LPWSTR szVK_F5;
LPWSTR szVK_F6;
LPWSTR szVK_F7;
LPWSTR szVK_F8;
LPWSTR szVK_F9;
LPWSTR szVK_F10;
LPWSTR szVK_F11;
LPWSTR szVK_F12;