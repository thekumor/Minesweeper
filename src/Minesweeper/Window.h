//****************************************************************
// File: Window.h
// Purpose: Contains window and scene classes.
// 
// Authors: The Kumor
//****************************************************************

#pragma once

#include <string>
#include <any>
#include <vector>
#include <memory>
#include <optional>

#include <windows.h>

#include <Minesweeper/Global.h>
#include <Minesweeper/BaseClass.h>
#include <Minesweeper/Vectors.h>
#include <Minesweeper/Events.h>
#include <Minesweeper/Errors.h>
#include <Minesweeper/Entities.h>

namespace mines
{

	//----------------------------------------------------------
	// A container for entities.
	//----------------------------------------------------------
	class Scene : public BaseClass
	{
	public:
		Scene(const std::string& name = "");
		Scene() = default;

		template <typename T>
		std::shared_ptr<T> CreateEntity(const std::wstring& text, const Vector2<>& size, const Vector2<>& position, FragileEntityPtr parent)
		{
			std::shared_ptr<T> ent = std::make_shared<T>(text, size, position, parent);
			m_Entities.push_back(ent);
			return ent;
		}
		
		const std::string& GetName() const;

		void Clear();
		void Switch(bool on);

	private:
		bool m_Switched = true;
		std::string m_Name = "";
		std::vector<std::shared_ptr<Entity>> m_Entities = {};
	};

	//----------------------------------------------------------
	// A window that can contains scenes that can be swapped.
	//----------------------------------------------------------
	class Window : public virtual Entity
	{
	public:
		Window(const Vector2<>& size, const std::wstring& title);
		Window() = default;

		static LRESULT CALLBACK s_Procedure(HWND handle, UINT msg, WPARAM wp, LPARAM lp);
		static bool s_DrawBitmap(HDC winDC, const std::wstring& path);

		std::optional<std::shared_ptr<Scene>> GetSceneByName(const std::string& name = "");

		std::shared_ptr<Scene> CreateScene(const std::string& name = "");

	private:
		WNDCLASS m_Class = { 0 };
		std::vector<std::shared_ptr<Scene>> m_Scenes = {};
	};

}

// The Kumor