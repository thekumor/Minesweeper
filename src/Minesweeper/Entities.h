//****************************************************************
// File: Entities.h
// Purpose: Has classes for controls that are used for
//			user input/drawing on the screen.
// 
// Authors: The Kumor
//****************************************************************

#pragma once

#include <string>

#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>

#include <Minesweeper/BaseClass.h>
#include <Minesweeper/Vectors.h>
#include <Minesweeper/Errors.h>
#include <Minesweeper/Events.h>

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
		Entity(const std::wstring& text, const Vector2<>& size, const Vector2<>& position, FragileEntityPtr parent);
		Entity() = default;
		virtual ~Entity() = default;

		HWND GetHandle() const;
		void SetPosition(const Vector2<>& position);
		void SetSize(const Vector2<>& size);
		void SetText(const std::wstring& text);
		void Show();
		void Hide();
		void Close();

		operator HWND();

	protected:
		FragileEntityPtr m_Parent = nullptr;
		HWND m_Handle = nullptr;
		Vector2<> m_Size = 0, m_Position = 0;
		std::wstring m_Tag = L"", m_Text = L"";
		bool m_IsVisible = true;
	};

	//----------------------------------------------------------
	// Used for displaying a string on the screen.
	//----------------------------------------------------------
	class Text : public virtual Entity
	{
	public:
		Text(const std::wstring& text, const Vector2<>& size, const Vector2<>& position, FragileEntityPtr parent);
		Text() = default;
	};

	//----------------------------------------------------------
	// Used for user input - mouse.
	//----------------------------------------------------------
	class Button : public virtual Entity
	{
	public:
		Button(const std::wstring& text, const Vector2<>& size, const Vector2<>& position, FragileEntityPtr parent);
		Button() = default;
	};

	//----------------------------------------------------------
	// Used for user input - keyboard.
	//----------------------------------------------------------
	class EditBox : public virtual Entity
	{
	public:
		EditBox(const std::wstring& text, const Vector2<>& size, const Vector2<>& position, FragileEntityPtr parent);
		EditBox() = default;
	};

	//----------------------------------------------------------
	// An image that can be drawn to the screen.
	//----------------------------------------------------------
	class Img : public virtual Entity
	{
	public:
		Img(const std::wstring& text, const Vector2<>& size, const Vector2<>& position, FragileEntityPtr parent);
		Img() = default;
		~Img();

		// Draws the image into a particular HDC (window, control, etc.)
		void Draw(HDC windowDC);

	private:
		HBITMAP m_HandleBitmap = nullptr;
	};

}

// The Kumor