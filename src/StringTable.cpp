#include "StringTable.h"

#define CONTENT(x) LoadStringW(hInstance, IDS_##x, (LPWSTR)&sz##x, 0)

void StringTableInit(HINSTANCE hInstance)
{
    STCONTENT
}

#undef CONTENT

#define CONTENT(x) LPWSTR sz##x

STCONTENT

#undef CONTENT
