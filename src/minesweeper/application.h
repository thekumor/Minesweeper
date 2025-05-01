#pragma once

// STL
#include <string>
#include <list>
#include <vector>

// WinAPI
#include <windows.h>

// Minesweeper
#include <minesweeper/window.h>
#include <minesweeper/vectors.h>
#include <minesweeper/controls.h>
#include <minesweeper/fonts.h>
#include <minesweeper/utility.h>
#include <minesweeper/events.h>

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
		void OpenScene(Scene* scene);
		void CloseScene(Scene* scene);
		void SwitchScene(Scene* scene);

	private:
		Window m_MainWindow;
		HINSTANCE m_Instance;
		std::list<Scene*> m_Scenes;
		Scene* m_CurrentScene;
	};

	class Scene : public EventActive
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

			g_Dispatcher.AddListener(&control->GetListener());

			return object;
		}

	private:
		std::string m_Name;
		std::vector<Control*> m_Controls;
	};

}