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

	class Entity;
	using FragileEntityPtr = Entity*;

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
		Entity(const std::wstring& text, const Vector2<>& size, const Vector2<>& position, FragileEntityPtr parent,
			EntityFlags flags = EntityFlags::None);
		Entity() = default;
		virtual ~Entity() = default;

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

		operator HWND();

	protected:
		FragileEntityPtr m_Parent = nullptr;
		HWND m_Handle = nullptr;
		Vector2<> m_Size = 0, m_OriginalSize = 0, m_Position = 0, m_OriginalPosition = 0;
		std::wstring m_Tag = L"", m_Text = L"";
		EntityFlags m_Flags = EntityFlags::None;
		bool m_IsVisible = true;
	};

	class Font : public BaseClass
	{
	public:
		friend class Text;

		Font(const std::wstring& path, std::int32_t size, bool italic, bool underline, bool strikeout);
		Font() = default;

	private:
		HFONT m_Font = nullptr;
		std::int32_t m_Size = 0;
		bool m_Italic = false, m_Underline = false, m_Strikeout = false;
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