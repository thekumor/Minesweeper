//****************************************************************
// File: Utility.h
// Purpose: Contains font.
// 
// Authors: The Kumor
//****************************************************************

#pragma once

#include <windows.h>

#include <string>
#include <cmath>

#include <Minesweeper/BaseClass.h>
#include <Minesweeper/Errors.h>
#include <Minesweeper/Global.h>
#include <Minesweeper/Vectors.h>

namespace mines
{
	class Font : public BaseClass
	{
	public:
		friend class Control;

		Font(const std::wstring& path, std::int32_t size, HWND window);
		Font() = default;
		~Font();

	private:
		Vector2<WORD> m_OriginalWindowSize = { 0 };
		HFONT m_Handle = nullptr;
		HWND m_WindowHandle = nullptr;
		std::wstring m_Name;
		std::int32_t m_Size, m_OriginalSize;
	};
}

// The Kumor