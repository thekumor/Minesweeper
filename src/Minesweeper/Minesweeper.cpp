// ================================================
// 
//	Project: Minesweeper
//	Game resembling Minesweeper from Windows XP.
//	by The Kumor
// 
// ================================================

// STL
#include <cstdlib>

// WinAPI
#include <windows.h>

// Minesweeper
#include <Minesweeper/Application.h>
#include <Minesweeper/Implementation.h>

#pragma warning(suppress:28251)
int APIENTRY wWinMain(HINSTANCE instance, HINSTANCE previousInstance, LPWSTR cmdLine, int cmdShow)
{
	mwr::Application app(instance, mwr::Vec2i(MWR_WIDTH, MWR_HEIGHT), MWR_TITLE);
	return app.Run();
}