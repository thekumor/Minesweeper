//********************************************************************************************
// File: Window.h
// Purpose: Contains window and scene classes.
// 
// Authors: The Kumor
//********************************************************************************************

#pragma once

// STL
#include <string>
#include <any>
#include <vector>
#include <memory>
#include <optional>

// WinAPI
#include <windows.h>

// Minesweeper
#include <Minesweeper/Global.h>
#include <Minesweeper/BaseClass.h>
#include <Minesweeper/Vectors.h>
#include <Minesweeper/Events.h>
#include <Minesweeper/Errors.h>
#include <Minesweeper/Entities.h>

namespace mines
{

	//------------------------------------------------------------------------------------
	// A container for entities.
	//------------------------------------------------------------------------------------
	class Scene : public BaseClass
	{
	public:
		Scene(const std::string& name = "");
		Scene() = default;

		// Creates an Control and puts it on the screen, even if scene is inactive.
		// TODO: make it not do that.
		template <typename T>
		std::shared_ptr<T> CreateControl(const std::wstring& text, const Vec2& size, const Vec2& position, Control* parent)
		{
			std::shared_ptr<T> ent = std::make_shared<T>(text, size, position, parent);
			m_Entities.push_back(ent);
			return ent;
		}
		
		inline const std::string& GetName() const { return m_Name; }

		// Every Control that this scene had is gone upon calling.
		void Clear();

		// Entities will appear on the screen.
		void Switch(bool on);

	private:
		bool m_Switched = true;
		std::string m_Name;
		std::vector<std::shared_ptr<Control>> m_Entities;
	};

	//------------------------------------------------------------------------------------
	// A window that can contains scenes that can be swapped.
	//------------------------------------------------------------------------------------
	class Window : public Control
	{
	public:
		friend class Application;

		Window(const Vec2& size, const std::wstring& title);
		Window() = default;

		// Gets a window's size by handle.
		static Vector2<WORD> s_GetSize(HWND handle);

		// Handles window's input, output and events from WinAPI.
		static LRESULT CALLBACK s_Procedure(HWND handle, UINT msg, WPARAM wp, LPARAM lp);

		// Draws a bitmap onto a context and puts it on the screen.
		static bool s_DrawBitmap(HDC winDC, const std::wstring& path);

		// Gets the window's size.
		Vector2<WORD> GetSize();

		// Gets a scene by given name, otherwise returns nullptr.
		std::shared_ptr<Scene> GetSceneByName(const std::string& name);

		// Makes a new scene.
		std::shared_ptr<Scene> CreateScene(const std::string& name);

	private:
		WNDCLASS m_Class = { 0 };
		std::vector<std::shared_ptr<Scene>> m_Scenes;
	};

}

// The Kumor