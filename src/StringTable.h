#pragma once

#include "pch.h"

#define STCONTENT                  \
    CONTENT(ClassName);            \
    CONTENT(RegisterHotKeyFailed); \
    CONTENT(Warning);              \
    CONTENT(DefaultDelay);         \
    CONTENT(Delaystr);             \
    CONTENT(DelayMaxstr);          \
    CONTENT(DefaultCount);         \
    CONTENT(MouseL);               \
    CONTENT(MouseM);               \
    CONTENT(MouseR);               \
    CONTENT(VK_F1);                \
    CONTENT(VK_F2);                \
    CONTENT(VK_F3);                \
    CONTENT(VK_F4);                \
    CONTENT(VK_F5);                \
    CONTENT(VK_F6);                \
    CONTENT(VK_F7);                \
    CONTENT(VK_F8);                \
    CONTENT(VK_F9);                \
    CONTENT(VK_F10);               \
    CONTENT(VK_F11);               \
    CONTENT(VK_F12);

void StringTableInit(HINSTANCE hInstance);

#define CONTENT(x) extern LPWSTR sz##x

STCONTENT

#undef CONTENT

