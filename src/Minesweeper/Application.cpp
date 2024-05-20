#include "Application.h"

namespace mines
{
	Application::Application(const Vector2& windowSize, const std::wstring& windowTitle)
		: m_Window(windowSize, windowTitle)
	{
	}

	int Application::Run()
	{
		Window& wnd = m_Window;

		std::shared_ptr<EditBox> txt = wnd.CreateEntity<EditBox>(L"Hello!", { 100, 30 }, { 10, 10 }, &wnd);

		MSG msg = {};
		while (GetMessage(&msg, nullptr, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		return EXIT_SUCCESS;
	}

}