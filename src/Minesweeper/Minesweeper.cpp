// ================================================
// 
//	Project: Minesweeper
//	Game resembling Minesweeper from Windows XP.
//	by The Kumor
// 
// ================================================

// STL
#include <cstdlib>
#include <unordered_map>

// WinAPI
#include <windows.h>

// Minesweeper
#include <minesweeper/application.h>
#include <minesweeper/implementation.h>
#include <minesweeper/vectors.h>

// Globals
mwr::EventDispatcher mwr::g_Dispatcher;
std::unordered_map<HWND, mwr::Vec2i> mwr::g_WindowSizes;

#pragma warning(suppress:28251)
int APIENTRY wWinMain(HINSTANCE instance, HINSTANCE previousInstance, LPWSTR cmdLine, int cmdShow)
{
	mwr::Application app(instance, mwr::Vec2i(MWR_WIDTH, MWR_HEIGHT), MWR_TITLE);
	return app.Run();
}