#pragma once

#include <string>
#include <any>
#include <vector>
#include <memory>

#include <windows.h>

#include <Minesweeper/Global.h>
#include <Minesweeper/BaseClass.h>
#include <Minesweeper/Vectors.h>
#include <Minesweeper/Events.h>
#include <Minesweeper/Errors.h>
#include <Minesweeper/Entities.h>

namespace mines
{

	//
	// A window that can have items such as controls in it.
	//
	class Window : public virtual Entity
	{
	public:
		Window(const Vector2& size, const std::wstring& title);
		Window() = default;

		static LRESULT CALLBACK s_Procedure(HWND handle, UINT msg, WPARAM wp, LPARAM lp);

	private:
		WNDCLASS m_Class = { 0 };
	};

}