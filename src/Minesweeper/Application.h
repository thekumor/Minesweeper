#pragma once

// STL
#include <string>

// WinAPI
#include <windows.h>

// Minesweeper
#include <Minesweeper/Window.h>
#include <Minesweeper/Vectors.h>

namespace mwr
{

	class Application
	{
	public:
		Application(HINSTANCE instance, const Vec2i& size, const std::wstring& title);
		Application() = default;

		int Run();

	private:
		Window m_MainWindow;
		HINSTANCE m_Instance;
	};

}