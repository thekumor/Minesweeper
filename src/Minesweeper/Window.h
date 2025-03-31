#pragma once

// STL
#include <string>

// WinAPI
#include <windows.h>

// Minesweeper
#include <Minesweeper/Vectors.h>
#include <Minesweeper/Error.h>
#include <Minesweeper/Controls.h>

namespace mwr
{

	class Window : public Control
	{
	public:
		Window(HINSTANCE instance, const Vec2i& size, const std::wstring& title);
		Window() = default;

		static LRESULT CALLBACK Procedure(HWND handle, UINT msg, WPARAM wp, LPARAM lp);

		static const std::wstring ClassName;

	private:
		HINSTANCE m_Instance;
		WNDCLASSEXW m_Class;
	};

}