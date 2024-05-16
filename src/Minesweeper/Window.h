#pragma once

#include <string>
#include <any>

#include <windows.h>

#include <Minesweeper/Global.h>
#include <Minesweeper/BaseClass.h>
#include <Minesweeper/Vectors.h>
#include <Minesweeper/Events.h>
#include <Minesweeper/Errors.h>

namespace mines
{

	//
	// A window that can have items such as controls in it.
	//
	class Window : public BaseClass
	{
	public:
		friend class Timer;

		Window(const Vector2& size, const std::wstring& title);
		Window() = default;

		static LRESULT CALLBACK s_Procedure(HWND handle, UINT msg, WPARAM wp, LPARAM lp);

	private:
		Vector2 m_Size = 0;
		HWND m_Handle = nullptr;
		WNDCLASS m_Class = { 0 };
		std::wstring m_Title = L"";
	};

}