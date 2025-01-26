//********************************************************************************************
// Project: Minesweeper
// Purpose: To re-create a famous minesweeper game from Windows XP
//			which people can play.
// 
// Authors: The Kumor
//********************************************************************************************

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <Minesweeper/Global.h>
#include <Minesweeper/Application.h>
#include <Minesweeper/Vectors.h>

// This calls events for entities.
mines::EventSource mines::g_EventSource;

#pragma warning(push)
#pragma warning(disable: 28251)
int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdLine, int cmdShow)
{
	mines::Application app(mines::Vec2(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
	return app.Run();
}
#pragma warning(pop)

// The Kumor