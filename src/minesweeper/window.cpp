#include "window.h"

namespace mwr
{

	Window::Window(HINSTANCE instance, const Vec2i& size, const std::wstring& title)
		: Control(size, { CW_USEDEFAULT, CW_USEDEFAULT }, title)
	{
		m_Instance = instance;
		m_Class = { 0 };

		m_Class.lpszClassName = Window::s_ClassName.c_str();
		m_Class.hInstance = instance;
		m_Class.cbSize = sizeof(WNDCLASSEXW);
		m_Class.lpszMenuName = nullptr;
		m_Class.hCursor = LoadCursorW(nullptr, IDC_ARROW);
		m_Class.hIcon = LoadIconW(instance, MAKEINTRESOURCEW(IDI_ICON1));
		m_Class.hIconSm = LoadIconW(instance, MAKEINTRESOURCEW(IDI_ICON1));
		m_Class.lpfnWndProc = &Window::Procedure;

		RegisterClassExW(&m_Class);
		MsgIfError("Window.m_Class");

		m_Handle = CreateWindowW(
			Window::s_ClassName.c_str(),
			title.c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			size.x,
			size.y,
			nullptr,
			nullptr,
			instance,
			nullptr
		);
		MsgIfError("Window.m_Handle");

		ShowWindow(m_Handle, SW_SHOW);
		UpdateWindow(m_Handle);

		g_WindowSizes[m_Handle] = size;
	}

	LRESULT CALLBACK Window::Procedure(HWND handle, UINT msg, WPARAM wp, LPARAM lp)
	{
		switch (msg)
		{
			case WM_CLOSE:
			{
				g_Dispatcher.CallEvent(EventType::Close);
				PostQuitMessage(0);
			} break;

			case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(handle, &ps);

				FillRect(hdc, &ps.rcPaint, reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1));

				EndPaint(handle, &ps);
			} break;

			case WM_SIZE:
			{
				auto windowSizeValue = g_WindowSizes.find(handle);

				if (windowSizeValue != g_WindowSizes.end())
				{
					Vec2i initialWindowSize = windowSizeValue->second;
					Vec2i currentWindowSize = Control::s_GetSize(handle);

					Vec2<float> fraction(
						static_cast<float>(currentWindowSize.x) / initialWindowSize.x,
						static_cast<float>(currentWindowSize.y) / initialWindowSize.y
					);

					g_Dispatcher.CallEvent(EventType::Resize, fraction);
				}
			} break;

			case WM_COMMAND:
			{
				void* qualifier = reinterpret_cast<void*>(lp);
				g_Dispatcher.CallEventQualifier(EventType::Click, qualifier);
			} break;
		}

		return DefWindowProcW(handle, msg, wp, lp);
	}

	const std::wstring Window::s_ClassName = L"MinesweeperWindow";

}