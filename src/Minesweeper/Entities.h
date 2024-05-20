#pragma once

#include <string>

#include <windows.h>
//#include <gdiplus.h>

#include <Minesweeper/BaseClass.h>
#include <Minesweeper/Vectors.h>
#include <Minesweeper/Errors.h>

namespace mines
{

	class Entity;
	using FragileEntityPtr = Entity*;

	//----------------------------------------------------------
	// Main class used for controls & things you see on
	// the screen.
	//----------------------------------------------------------
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

	//----------------------------------------------------------
	// Used for displaying a string on the screen.
	//----------------------------------------------------------
	class Text : public virtual Entity
	{
	public:
		Text(const std::wstring& text, const Vector2& size, const Vector2& position, FragileEntityPtr parent);
		Text() = default;
	};

	//----------------------------------------------------------
	// Used for user input - mouse.
	//----------------------------------------------------------
	class Button : public virtual Entity
	{
	public:
		Button(const std::wstring& text, const Vector2& size, const Vector2& position, FragileEntityPtr parent);
		Button() = default;
	};

	//----------------------------------------------------------
	// Used for user input - keyboard.
	//----------------------------------------------------------
	class EditBox : public virtual Entity
	{
	public:
		EditBox(const std::wstring& text, const Vector2& size, const Vector2& position, FragileEntityPtr parent);
		EditBox() = default;
	};

	//----------------------------------------------------------
	// Used for displaying and storing an image.
	//----------------------------------------------------------
	class Img : public virtual Entity
	{
	public:
		Img(const std::wstring& path, const Vector2& size, const Vector2& position, FragileEntityPtr parent);
		Img() = default;
	};

}