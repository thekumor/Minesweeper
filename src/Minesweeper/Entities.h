//********************************************************************************************
// File: Entities.h
// Purpose: Has classes for controls that are used for user input/drawing on the screen.
// 
// Authors: The Kumor
//********************************************************************************************

#pragma once

// STL
#include <string>
#include <unordered_map>

// WinAPI
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>

// Minesweeper
#include <Minesweeper/Global.h>
#include <Minesweeper/BaseClass.h>
#include <Minesweeper/Vectors.h>
#include <Minesweeper/Errors.h>
#include <Minesweeper/Events.h>
#include <Minesweeper/Utility.h>

#define HAS_FLAG(var,val) ((std::int32_t(var) & std::int32_t(val)) != 0)

namespace mines
{

	enum class ControlFlags : std::uint8_t
	{
		None = 0,
		IgnoreResize
	};

	//------------------------------------------------------------------------------------
	// Main class used for controls & things you see on the screen.
	//------------------------------------------------------------------------------------
	class Control : public BaseClass
	{
	public:
		friend class Text;
		friend class Button;
		friend class EditBox;
		friend class Img;
		friend class Timer;

		Control(const std::wstring& text, const Vec2& size, const Vec2& position, Control* parent,
			ControlFlags flags = ControlFlags::None);
		Control();
		~Control();

		inline HWND GetHandle() const { return m_Handle; }

		// Re-positions the control. This will adjust the position further down the line to keep aspect ratio with it's parent (e.g a window).
		void SetPosition(const Vec2& position);

		// Re-sizes the control. This will adjust the size further down the line to keep aspect ratio with it's parent (e.g a window).
		void SetSize(const Vec2& size);

		// Sets text, depending on type of control it appears in different places. For example, a window has text on title bar, a button has
		// text on it's center, etc.
		void SetText(const std::wstring& text);

		// Alters the behavior. In practice, there's only one flag and it blocks the window from ever calling callbacks upon resize to avoid
		// recursive calls.
		void SetFlags(ControlFlags flags);

		void SetFont(Font* font);

		// Makes the control appear on it's window.
		void Show();

		// Makes the control disappear on it's window (but not close, delete).
		void Hide();

		// Makes the control cease to exist.
		void Close();

	protected:
		void RegisterSize();

		Control* m_Parent = nullptr;
		Font* m_Font = nullptr;
		HWND m_Handle = nullptr;
		Vector2<> m_Size = 0, m_TranslatedSize = 0, m_Position = 0, m_TranslatedPosition = 0;
		std::wstring m_Tag, m_Text;
		ControlFlags m_Flags = ControlFlags::None;
		bool m_IsVisible = true;
	};

	//------------------------------------------------------------------------------------
	// Used for displaying a string on the screen.
	//------------------------------------------------------------------------------------
	class Text : public Control
	{
	public:
		Text(const std::wstring& text, const Vec2& size, const Vec2& position, Control* parent);
		Text(const std::wstring& text, const Vec2& size, const Vec2& position, Control* parent, Font* font);
		Text() = default;
	};

	//------------------------------------------------------------------------------------
	// Used for user input - mouse.
	//------------------------------------------------------------------------------------
	class Button : public Control
	{
	public:
		Button(const std::wstring& text, const Vec2& size, const Vec2& position, Control* parent);
		Button() = default;
	};

	//------------------------------------------------------------------------------------
	// Used for user input - keyboard.
	//------------------------------------------------------------------------------------
	class EditBox : public Control
	{
	public:
		EditBox(const std::wstring& text, const Vec2& size, const Vec2& position, Control* parent);
		EditBox() = default;
	};

	//------------------------------------------------------------------------------------
	// An image that can be drawn to the screen.
	//------------------------------------------------------------------------------------
	class Img : public Control
	{
	public:
		Img(const std::wstring& text, const Vec2& size, const Vec2& position, Control* parent);
		Img() = default;
		~Img();

		// Draws the image into a particular HDC (window, control, etc.)
		void Draw(HDC windowDC);

	private:
		HBITMAP m_HandleBitmap = nullptr;
	};

}

// The Kumor