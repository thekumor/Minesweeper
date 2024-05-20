#include "Window.h"

namespace mines
{

	Window::Window(const Vector2& size, const std::wstring& title)
		: Entity(title, size, {CW_USEDEFAULT, CW_USEDEFAULT}, nullptr)
	{
		HINSTANCE instance = reinterpret_cast<HINSTANCE>(GetModuleHandle(nullptr));
		const std::wstring className = L"Minesweeper Window";

		m_Class.hInstance = instance;
		m_Class.lpszClassName = className.c_str();
		m_Class.cbClsExtra = 0;
		m_Class.lpfnWndProc = reinterpret_cast<WNDPROC>(s_Procedure);
		m_Class.hCursor = LoadCursor(nullptr, IDC_ARROW);
		RegisterClass(&m_Class);
		CheckErrors("Window.RegisterClass");

		m_Handle = CreateWindow(
			className.c_str(),
			title.c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			size.x,
			size.y,
			nullptr,
			nullptr,
			instance,
			0
		);
		CheckErrors("Window.m_Handle");

		ShowWindow(m_Handle, SW_SHOW);
	}

	LRESULT CALLBACK Window::s_Procedure(HWND handle, UINT msg, WPARAM wp, LPARAM lp)
	{
		switch (msg)
		{
			case WM_CLOSE:
			{
				g_EventSource.CallEvent(EventType::Close, MINES_NODATA);
				PostQuitMessage(0);
			} break;

			case WM_PAINT:
			{
				g_EventSource.CallEvent(EventType::PreDraw, MINES_NODATA);

				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(handle, &ps);
				FillRect(hdc, &ps.rcPaint, reinterpret_cast<HBRUSH>(COLOR_WINDOW + 5));
				EndPaint(handle, &ps);

				g_EventSource.CallEvent(EventType::PostDraw, MINES_NODATA);
			} break;
		}

		return DefWindowProc(handle, msg, wp, lp);
	}

}