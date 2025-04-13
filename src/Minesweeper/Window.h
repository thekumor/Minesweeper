#pragma once

// STL
#include <string>

// WinAPI
#include <windows.h>

// Minesweeper
#include <minesweeper/vectors.h>
#include <minesweeper/error.h>
#include <minesweeper/controls.h>
#include <../resource.h>

namespace mwr
{

	class Window : public Control
	{
	public:
		friend class Application;

		Window(HINSTANCE instance, const Vec2i& size, const std::wstring& title);
		Window() = default;

		static LRESULT CALLBACK Procedure(HWND handle, UINT msg, WPARAM wp, LPARAM lp);

		static const std::wstring ClassName;

	private:
		HINSTANCE m_Instance;
		WNDCLASSEXW m_Class;
	};

}