#pragma once

#include <cstdint>
#include <string>

#include <windows.h>

#include <Minesweeper/BaseClass.h>
#include <Minesweeper/Vectors.h>
#include <Minesweeper/Window.h>
#include <Minesweeper/Timers.h>

namespace mines
{

	//
	// Class that acts as an instance of the application.
	// Contains a window.
	//
	class Application : public BaseClass
	{
	public:
		Application(const Vector2& windowSize, const std::wstring& windowTitle);
		Application() = default;

		int Run();

	private:
		// Main application's window.
		Window m_Window;
	};

}