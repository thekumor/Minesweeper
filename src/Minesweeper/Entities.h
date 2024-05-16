#pragma once

#include <string>

#include <windows.h>

#include <Minesweeper/BaseClass.h>
#include <Minesweeper/Vectors.h>

namespace mines
{

	class Entity;
	using FragileEntityPtr = Entity*;

	class Entity : public BaseClass
	{
	public:
		Entity(const std::wstring& text, const Vector2& size, const Vector2& position, FragileEntityPtr parent);
		Entity() = default;

		void SetPosition(const Vector2& position);
		void SetSize(const Vector2& size);
		void SetText(const std::wstring& text);
		void Show();
		void Hide();
		//void SetFont(Font font);

	protected:
		FragileEntityPtr m_Parent = nullptr;
		Vector2 m_Size = 0, m_Position = 0;
		HWND m_Handle = nullptr;
		std::wstring m_Tag = L"", m_Text = L"";
		bool m_IsVisible = true;
	};

	class Text : public Entity
	{
	public:
		Text(const std::wstring& text, const Vector2& size, const Vector2& position, FragileEntityPtr parent);
		Text() = default;
	};

}