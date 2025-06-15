#pragma once

// STL
#include <string>
#include <list>
#include <vector>
#include <cstdlib>
#include <cmath>

// WinAPI
#include <windows.h>

// Minesweeper
#include <minesweeper/window.h>
#include <minesweeper/vectors.h>
#include <minesweeper/controls.h>
#include <minesweeper/fonts.h>
#include <minesweeper/timer.h>
#include <minesweeper/events.h>

#ifdef _DEBUG
void* operator new(size_t size);
void operator delete(void* ptr, size_t size);
#endif

namespace mwr
{

	class Scene;

	class Application
	{
	public:
		Application(HINSTANCE instance, const Vec2i& size, const std::wstring& title);
		Application() = default;
		~Application();

		int Run();
		Scene* CreateScene(const std::string& name);
		Timer* CreateTimer(std::int32_t delay);
		void DestroyTimer(Timer* ptr);
		void OpenScene(Scene* scene);
		void CloseScene(Scene* scene);
		void SwitchScene(Scene* scene);

	private:
		Window m_MainWindow;
		HINSTANCE m_Instance;
		std::vector<Scene*> m_Scenes;
		std::vector<Timer*> m_Timers;
		Scene* m_CurrentScene;
	};

	class Scene : public BaseClass
	{
	public:
		Scene(const std::string& name);
		Scene() = default;
		~Scene();

		template <typename T>
		T* CreateControl(const Vec2i& size, const Vec2i& position, const std::wstring& string, Control* parent = nullptr, Font* font = nullptr)
		{
			T* object = new T(size, position, string, parent, font);
			Control* control = dynamic_cast<Control*>(object);
			m_Controls.emplace_back(control);

			return object;
		}

		Control* GetControlByTag(const std::string& tag);

	private:
		std::string m_Name;
		std::vector<Control*> m_Controls;
	};

}