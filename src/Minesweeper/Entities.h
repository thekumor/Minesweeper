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

#include <Minesweeper/Global.h>
#include <Minesweeper/BaseClass.h>
#include <Minesweeper/Vectors.h>
#include <Minesweeper/Errors.h>
#include <Minesweeper/Events.h>

#define HAS_FLAG(var,val) ((std::int32_t(var) & std::int32_t(val)) != 0)

namespace mines
{

	enum class EntityFlags : std::uint8_t
	{
		None = 0,
		IgnoreResize
	};

	//----------------------------------------------------------
	// Main class used for controls & things you see on
	// the screen.
	//----------------------------------------------------------
	class Entity : public BaseClass
	{
	public:
		friend class Text;
		friend class Button;
		friend class EditBox;
		friend class Img;
		friend class Timer;

		Entity(const std::wstring& text, const Vector2<>& size, const Vector2<>& position, Entity* parent,
			EntityFlags flags = EntityFlags::None);
		Entity() = default;
		~Entity() = default;

		HWND GetHandle() const;

		void SetPosition(const Vector2<>& position);
		void SetSize(const Vector2<>& size);
		void Resize(const Vector2<>& size);
		void Reposition(const Vector2<>& position);
		void SetText(const std::wstring& text);
		void SetFlags(EntityFlags flags);
		void Show();
		void Hide();
		void Close();

	protected:
		Entity* m_Parent = nullptr;
		HWND m_Handle = nullptr;
		Vector2<> m_Size = 0, m_OriginalSize = 0, m_Position = 0, m_OriginalPosition = 0;
		std::wstring m_Tag, m_Text;
		EntityFlags m_Flags = EntityFlags::None;
		bool m_IsVisible = true;
	};

	//----------------------------------------------------------
	// Used for displaying a string on the screen.
	//----------------------------------------------------------
	class Text : public Entity
	{
	public:
		Text(const std::wstring& text, const Vector2<>& size, const Vector2<>& position, Entity* parent);
		Text() = default;
	};

	//----------------------------------------------------------
	// Used for user input - mouse.
	//----------------------------------------------------------
	class Button : public Entity
	{
	public:
		Button(const std::wstring& text, const Vector2<>& size, const Vector2<>& position, Entity* parent);
		Button() = default;
	};

	//----------------------------------------------------------
	// Used for user input - keyboard.
	//----------------------------------------------------------
	class EditBox : public Entity
	{
	public:
		EditBox(const std::wstring& text, const Vector2<>& size, const Vector2<>& position, Entity* parent);
		EditBox() = default;
	};

	//----------------------------------------------------------
	// An image that can be drawn to the screen.
	//----------------------------------------------------------
	class Img : public Entity
	{
	public:
		Img(const std::wstring& text, const Vector2<>& size, const Vector2<>& position, Entity* parent);
		Img() = default;
		~Img();

		// Draws the image into a particular HDC (window, control, etc.)
		void Draw(HDC windowDC);

	private:
		HBITMAP m_HandleBitmap = nullptr;
	};

}

// The Kumor