#pragma once

// STL
#include <string>

// WinAPI
#include <windows.h>

// Minesweeper
#include <minesweeper/vectors.h>
#include <minesweeper/error.h>
#include <minesweeper/fonts.h>
#include <minesweeper/events.h>
#include <minesweeper/implementation.h>
#include <minesweeper/base_class.h>

namespace mwr
{

	class Control : public BaseClass
	{
	public:
		friend class Label;
		friend class Button;
		friend class TextEntry;

		Control(const Vec2i& size, const Vec2i& position, const std::wstring& string, Control* parent = nullptr, Font* font = nullptr);
		Control(const Control&& other);
		Control();
		virtual ~Control();

		static Vec2i GetSize(HWND handle);

		Control* GetParent();
		const std::vector<Control*>& GetChildren();
		const std::wstring& GetString() const;
		const std::string& GetTag() const;
		bool IsDisabled() const;
		bool IsInvalidated() const;
		void SetPosition(const Vec2i& position, bool isScreen = false);
		void SetSize(const Vec2i& size, bool isScreen = false);
		void SetString(const std::wstring& string);
		void SetTag(const std::string& tag);
		void SetParent(Control* parent);
		void SetFont(Font* font);
		void SetDisabled(bool disabled);
		void Invalidate(bool invalidate = true);

	protected:
		bool m_Disabled;
		bool m_Invalidated;
		Control* m_Parent;
		Font* m_Font;
		HWND m_Handle;
		Vec2i m_Size, m_Position;
		Vec2i m_ScreenSize, m_ScreenPosition;
		std::wstring m_String;
		std::string m_Tag;
		std::vector<Control*> m_Children;
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

	class TextEntry : public Control
	{
	public:
		TextEntry(const Vec2i& size, const Vec2i& position, const std::wstring& string, Control* parent = nullptr, Font* font = nullptr);
		TextEntry() = default;
	};

}