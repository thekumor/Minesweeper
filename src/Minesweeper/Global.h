//********************************************************************************************
// File: Global.h
// Purpose: Stores all project's globals.
// 
// Authors: The Kumor
//********************************************************************************************

#pragma once

// WinAPI
#include <Windows.h>

// Minesweeper
#include <Minesweeper/Errors.h>
#include <Minesweeper/Vectors.h>

#define WINDOW_WIDTH 1440
#define WINDOW_HEIGHT 900
#define WINDOW_TITLE L"Minesweeper"

namespace mines
{

	using WindowSize = Vector2<WORD>;
	WindowSize GetWindowSize(HWND);

}

// The Kumor