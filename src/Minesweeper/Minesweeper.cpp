#include <windows.h>

#include <Minesweeper/Global.h>
#include <Minesweeper/Application.h>
#include <Minesweeper/Vectors.h>

#define WINDOW_WIDTH 1440
#define WINDOW_HEIGHT 900
#define WINDOW_TITLE L"Minesweeper"

mines::EventSource mines::g_EventSource;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdLine, int cmdShow)
{
	using namespace mines;

#ifdef _DEBUG
	//AllocConsole();
	//mines::CheckErrors("AllocConsole");
#endif
	
	Application app(Vector2(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
	return app.Run();
}