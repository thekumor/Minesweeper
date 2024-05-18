#pragma once

#include <string>

#include <windows.h>

#include <Minesweeper/BaseClass.h>
#include <Minesweeper/Vectors.h>
#include <Minesweeper/Errors.h>

namespace mines
{

	class Entity;
	using FragileEntityPtr = Entity*;

	class Entity : public BaseClass
	{
	public:
		Entity(const std::wstring& text, const Vector2& size, const Vector2& position, FragileEntityPtr parent);
		Entity() = default;
		virtual ~Entity() = default;

		HWND GetHandle() const;
		void SetPosition(const Vector2& position);
		void SetSize(const Vector2& size);
		void SetText(const std::wstring& text);
		void Show();
		void Hide();

		operator HWND();

	protected:
		FragileEntityPtr m_Parent = nullptr;
		HWND m_Handle = nullptr;
		Vector2 m_Size = 0, m_Position = 0;
		std::wstring m_Tag = L"", m_Text = L"";
		bool m_IsVisible = true;
	};

	class Text : public virtual Entity
	{
	public:
		Text(const std::wstring& text, const Vector2& size, const Vector2& position, FragileEntityPtr parent);
		Text() = default;
	};

}