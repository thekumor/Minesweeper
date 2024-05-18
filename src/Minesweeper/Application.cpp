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
		while (GetMessage(&msg, nullptr, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		return EXIT_SUCCESS;
	}

}