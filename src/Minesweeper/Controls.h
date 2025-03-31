#pragma once

// STL
#include <string>

// WinAPI
#include <windows.h>

// Minesweeper
#include <Minesweeper/Vectors.h>
#include <Minesweeper/Error.h>
#include <Minesweeper/Fonts.h>

namespace mwr
{

	class Control
	{
	public:
		friend class Label;
		friend class Button;

		Control(const Vec2i& size, const Vec2i& position, const std::wstring& string, Control* parent = nullptr, Font* font = nullptr);
		Control() = default;
		virtual ~Control() = default;

		void SetPosition(const Vec2i& position);
		void SetSize(const Vec2i& size);
		void SetString(const std::wstring& string);
		void SetParent(Control* parent);
		void SetFont(Font* font);

	protected:
		Control* m_Parent;
		Font* m_Font;
		HWND m_Handle;
		Vec2i m_Size, m_Position;
		std::wstring m_String;
	};

	class Label : public Control
	{
	public:
		Label(const Vec2i& size, const Vec2i& position, const std::wstring& string, Control* parent = nullptr, Font* font = nullptr);
		Label() = default;
	};

	class Button : public Control
	{
	public:
		Button(const Vec2i& size, const Vec2i& position, const std::wstring& string, Control* parent = nullptr, Font* font = nullptr);
		Button() = default;
	};

}