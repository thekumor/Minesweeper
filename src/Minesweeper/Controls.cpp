#include "Controls.h"

namespace mwr
{

	Control::Control(const Vec2i& size, const Vec2i& position, const std::wstring& string, Control* parent, Font* font)
		: m_Parent(parent), m_Font(font), m_Handle(nullptr), m_Size(size), m_Position(position), m_String(string)
	{
	}

	void Control::SetPosition(const Vec2i& position)
	{
		SetWindowPos(m_Handle, nullptr, position.x, position.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		m_Position = position;
	}

	void Control::SetSize(const Vec2i& size)
	{
		SetWindowPos(m_Handle, nullptr, 0, 0, size.x, size.y, SWP_NOREPOSITION | SWP_NOZORDER);
		m_Size = size;
	}

	void Control::SetString(const std::wstring& string)
	{
		SetWindowTextW(m_Handle, string.c_str());
		m_String = string;
	}

	void Control::SetParent(Control* parent)
	{
		::SetParent(m_Handle, parent->m_Handle);
		m_Parent = parent;
	}

	void Control::SetFont(Font* font)
	{
		SendMessageW(m_Handle, WM_SETFONT, reinterpret_cast<WPARAM>(font->m_Handle), TRUE);
		MsgIfError("Control.SendMessageW");
		m_Font = font;
	}

	Label::Label(const Vec2i& size, const Vec2i& position, const std::wstring& string, Control* parent, Font* font)
		: Control(size, position, string, parent, font)
	{
		m_Handle = CreateWindowW(
			L"Static",
			string.c_str(),
			parent ? WS_CHILD : 0,
			position.x,
			position.y,
			size.x,
			size.y,
			parent ? parent->m_Handle : nullptr,
			nullptr,
			GetModuleHandleW(0),
			0
		);
		MsgIfError("Label.m_Handle");

		ShowWindow(m_Handle, SW_SHOW);

		if (font)
			SetFont(font);
	}

	Button::Button(const Vec2i& size, const Vec2i& position, const std::wstring& string, Control* parent, Font* font)
		: Control(size, position, string, parent, font)
	{
		m_Handle = CreateWindowW(
			L"Button",
			string.c_str(),
			parent ? WS_CHILD : 0,
			position.x,
			position.y,
			size.x,
			size.y,
			parent ? parent->m_Handle : nullptr,
			nullptr,
			GetModuleHandleW(0),
			0
		);
		MsgIfError("Button.m_Handle");

		ShowWindow(m_Handle, SW_SHOW);

		if (font)
			SetFont(font);
	}

}