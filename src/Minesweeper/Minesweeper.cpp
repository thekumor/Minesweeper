//****************************************************************
// Project: Minesweeper
// Purpose: To re-create a famous minesweeper game from Windows XP
//			which people can play.
// 
// Authors: The Kumor,
//			Cat Gaeming | BendGMS | STEAM_0:1:41044407
//****************************************************************

#include <windows.h>

#include <Minesweeper/Global.h>
#include <Minesweeper/Application.h>
#include <Minesweeper/Vectors.h>

mines::EventSource mines::g_EventSource;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdLine, int cmdShow)
{
	using namespace mines;

#ifdef _DEBUG
	//AllocConsole();
	//mines::CheckErrors("AllocConsole");
#endif
	
	Application app(Vector2<>(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
	return app.Run();
}

// The Kumor