#pragma once

// STL
#include <string>

// WinAPI
#include <windows.h>

// Minesweeper
#include <Minesweeper/Vectors.h>
#include <Minesweeper/Error.h>

namespace mwr
{

	class Window
	{
	public:
		Window(HINSTANCE instance, const Vec2i& size, const std::wstring& title);
		Window() = default;

		static LRESULT CALLBACK Procedure(HWND handle, UINT msg, WPARAM wp, LPARAM lp);

		static const std::wstring ClassName;

	private:
		Vec2i m_Size;
		std::wstring m_Title;
		HINSTANCE m_Instance;
		WNDCLASSEXW m_Class;
		HWND m_Handle;
	};

}