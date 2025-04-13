#pragma once

// STL
#include <string>
#include <list>

// WinAPI
#include <windows.h>

// Minesweeper
#include <minesweeper/window.h>
#include <minesweeper/vectors.h>
#include <minesweeper/controls.h>
#include <minesweeper/fonts.h>
#include <minesweeper/utility.h>

namespace mwr
{

	class Application
	{
	public:
		Application(HINSTANCE instance, const Vec2i& size, const std::wstring& title);
		Application() = default;
		~Application();

		template <typename T>
		T* CreateControl(const Vec2i& size, const Vec2i& position, const std::wstring& string, Control* parent = nullptr, Font* font = nullptr)
		{
			Control* window = dynamic_cast<Control*>(&m_MainWindow);
			T* object = new T(size, position, string, parent ? parent : window, font);
			m_Controls.emplace_back(dynamic_cast<Control*>(object));

			return object;
		}

		int Run();

	private:
		Window m_MainWindow;
		HINSTANCE m_Instance;
		std::list<Control*> m_Controls;
	};

}