//********************************************************************************************
// File: Utility.h
// Purpose: Contains font.
// 
// Authors: The Kumor
//********************************************************************************************

#pragma once

// STL
#include <string>
#include <cmath>

// WinAPI
#include <windows.h>

// Minesweeper
#include <Minesweeper/BaseClass.h>
#include <Minesweeper/Errors.h>
#include <Minesweeper/Global.h>
#include <Minesweeper/Vectors.h>

namespace mines
{

	//------------------------------------------------------------------------------------
	// Font that can be applied to a control via mines::Control.
	//------------------------------------------------------------------------------------
	class Font : public BaseClass
	{
	public:
		friend class Control;

		Font(const std::wstring& path, std::int32_t size);
		Font() = default;
		~Font();

	private:
		HFONT m_Handle = nullptr;
		std::wstring m_Name;
		std::int32_t m_Size;
	};

}

// The Kumor