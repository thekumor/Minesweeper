#include "Application.h"

namespace mines
{
    Application::Application(const Vector2& windowSize, const std::wstring& windowTitle)
        : m_Window(windowSize, windowTitle)
    {
    }

    int Application::Run()
    {
        MSG msg = {};

        Timer timer(10, 3000, [](HWND, UINT, UINT_PTR, DWORD)->void
        {
        });

        while (GetMessage(&msg, nullptr, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        return EXIT_SUCCESS;
    }

}