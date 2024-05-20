#pragma once

#include <string>
#include <any>
#include <vector>
#include <memory>

#include <windows.h>

#include <Minesweeper/Global.h>
#include <Minesweeper/BaseClass.h>
#include <Minesweeper/Vectors.h>
#include <Minesweeper/Events.h>
#include <Minesweeper/Errors.h>
#include <Minesweeper/Entities.h>

namespace mines
{

	//
	// A window that can have items such as controls in it.
	//
	class Window : public virtual Entity
	{
	public:
		Window(const Vector2& size, const std::wstring& title);
		Window() = default;

		static LRESULT CALLBACK s_Procedure(HWND handle, UINT msg, WPARAM wp, LPARAM lp);

		std::shared_ptr<Entity> CreateEntity(const std::wstring& text, const Vector2& size, const Vector2& position, FragileEntityPtr parent);
		std::shared_ptr<Text> CreateText(const std::wstring& text, const Vector2& size, const Vector2& position, FragileEntityPtr parent);

	private:
		WNDCLASS m_Class = { 0 };
		std::vector<std::shared_ptr<Entity>> m_Entities = {};
	};

}