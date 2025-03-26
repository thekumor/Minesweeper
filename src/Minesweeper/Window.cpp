#include "Window.h"

namespace mwr
{

	Window::Window(HINSTANCE instance, const Vec2i& size, const std::wstring& title)
		: m_Size(size), m_Title(title), m_Instance(instance)
	{
		m_Class = { 0 };

		m_Class.lpszClassName = Window::ClassName.c_str();
		m_Class.hInstance = instance;
		m_Class.cbSize = sizeof(WNDCLASSEXW);
		m_Class.lpszMenuName = nullptr;
		m_Class.hCursor = LoadCursor(nullptr, IDC_ARROW);
		m_Class.lpfnWndProc = &Window::Procedure;

		RegisterClassExW(&m_Class);
		MsgIfError(L"Window.m_Class");

		m_Handle = CreateWindowW(
			Window::ClassName.c_str(),
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
		MsgIfError(L"Window.m_Handle");

		ShowWindow(m_Handle, SW_SHOW);
		UpdateWindow(m_Handle);
	}

	LRESULT CALLBACK Window::Procedure(HWND handle, UINT msg, WPARAM wp, LPARAM lp)
	{
		switch (msg)
		{
			case WM_CLOSE:
			{
				PostQuitMessage(0);
			} break;

			case WM_PAINT:
			{

			} break;
		}

		return DefWindowProcW(handle, msg, wp, lp);
	}

	const std::wstring Window::ClassName = L"MinesweeperWindow";

}