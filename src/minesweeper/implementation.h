// STL
#include <unordered_map>

// WinAPI
#include <windows.h>

// Minesweeper
#include <Minesweeper/events.h>
#include <Minesweeper/vectors.h>

#define MWR_WIDTH 700
#define MWR_HEIGHT 700
#define MWR_TITLE L"Minesweeper"

namespace mwr
{

	extern EventDispatcher g_Dispatcher;
	extern std::unordered_map<HWND, Vec2i> g_WindowSizes;

}