#include "Global.h"

namespace mines
{

    WindowSize GetWindowSize(HWND handle)
    {
		RECT lpRect = { 0 };
		GetWindowRect(handle, &lpRect);
		CheckErrors("GetWindowRect");
		WORD width = lpRect.right - lpRect.left;
		WORD height = lpRect.bottom - lpRect.top;

        return WindowSize(width, height);
    }

}