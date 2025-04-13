#pragma once

// STL
#include <string>
#include <cstdint>

// WinAPI
#include <windows.h>

// Minesweeper
#include <minesweeper/error.h>

namespace mwr
{

	enum FontStyle : std::uint32_t
	{
		Normal = 0,
		Italic = 1,
		Bold = 2,
		Underline = 4,
		StrikeOut = 8
	};

	class Font
	{
	public:
		friend class Control;

		Font(const std::wstring& name, std::int32_t size, std::uint32_t style = FontStyle::Normal);
		Font() = default;

	private:
		HFONT m_Handle;
		std::uint32_t m_Style;
		std::int32_t m_Size;
		std::wstring m_Name;
	};

}