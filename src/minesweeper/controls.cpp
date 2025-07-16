#include "controls.h"

namespace mwr
{

	Control::Control(const Vec2i& size, const Vec2i& position, const std::wstring& string, Control* parent, Font* font)
		: m_Parent(parent), m_Font(nullptr), m_Handle(nullptr), m_Size(size), m_Position(position), m_String(string),
		m_ScreenSize(size), m_ScreenPosition(position), m_Disabled(false)
	{
		if (parent)
		{
			parent->m_Children.push_back(this);

			m_Listener.AddHook(EventType::Resize, Hook("Control.DefaultResize", [&](const std::any& param)
			{
				Vec2<float> fraction = std::any_cast<Vec2<float>>(param);

				Vec2i newControlSize(m_Size.x * fraction.x, m_Size.y * fraction.y);
				Vec2i newControlPos(m_Position.x * fraction.x, m_Position.y * fraction.y);

				SetPosition(newControlPos, true);
				SetSize(newControlSize, true);
			}));

			m_Listener.AddHook(EventType::FontsUpdated, Hook("Control.DefaultFontsUpdated", [&](const std::any& param)
			{
				// Font's handle is changed, but object stays the same. Easiest way is to just set font to its own again
				// so that font is updated properly.
				SetFont(m_Font);
			}));
		}

		m_Listener.SetTag("Control");
	}

	Control::Control(const Control&& other)
		: Control(other.m_Size, other.m_Position, other.m_String, other.m_Parent, other.m_Font)
	{
	}

	Control::Control()
	{

	}

	Control::~Control()
	{
		g_Dispatcher.CallEvent(EventType::ControlDestroyed, &m_Listener);
		DestroyWindow(m_Handle);
	}

	Control* Control::GetParent()
	{
		return m_Parent;
	}

	const std::string& Control::GetTag() const
	{
		return m_Tag;
	}

	bool Control::IsDisabled() const
	{
		return m_Disabled;
	}

	bool Control::IsInvalidated() const
	{
		return m_Invalidated;
	}

	Vec2i Control::GetSize(HWND handle)
	{
		RECT rect;
		GetWindowRect(handle, &rect);

		return Vec2i(rect.right - rect.left, rect.bottom - rect.top);
	}

	const std::vector<Control*>& Control::GetChildren()
	{
		return m_Children;
	}

	const std::wstring& Control::GetString() const
	{
		return m_String;
	}

	void Control::SetPosition(const Vec2i& position, bool isScreen)
	{
		SetWindowPos(m_Handle, nullptr, position.x, position.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		if (isScreen)
			m_ScreenPosition = position;
		else
			m_Position = position;
	}

	void Control::SetSize(const Vec2i& size, bool isScreen)
	{
		SetWindowPos(m_Handle, nullptr, 0, 0, size.x, size.y, SWP_NOMOVE | SWP_NOZORDER);
		if (isScreen)
			m_ScreenSize = size;
		else
		{
			m_Size = size;
			g_WindowSizes[m_Handle] = size;
		}
	}

	void Control::SetString(const std::wstring& string)
	{
		SetWindowTextW(m_Handle, string.c_str());
		m_String = string;
	}

	void Control::SetTag(const std::string& tag)
	{
		m_Tag = tag;
	}

	void Control::SetParent(Control* parent)
	{
		::SetParent(m_Handle, parent ? parent->m_Handle : nullptr);

		if (m_Parent)
			std::erase(m_Parent->m_Children, this);

		m_Parent = parent;
	}

	void Control::SetFont(Font* font)
	{
		if (!font)
			return;

		if (m_Font != font)
		{
			font->GetDispatcher().AddListenerForce(&m_Listener);

			if (m_Font)
				m_Font->GetDispatcher().RemoveListenerForce(&m_Listener);
		}

		SendMessageW(m_Handle, WM_SETFONT, reinterpret_cast<WPARAM>(font->m_Handle), TRUE);
		MsgIfError("Control.SendMessageW");

		// Mark itself to be repainted.
		RECT rect;
		GetClientRect(m_Handle, &rect);
		InvalidateRect(m_Handle, &rect, TRUE);

		m_Font = font;
	}

	void Control::SetDisabled(bool disabled)
	{
		m_Disabled = disabled;
		EnableWindow(m_Handle, !disabled);
	}

	void Control::Invalidate(bool invalidate)
	{
		m_Invalidated = invalidate;
	}

	Label::Label(const Vec2i& size, const Vec2i& position, const std::wstring& string, Control* parent, Font* font)
		: Control(size, position, string, parent, font)
	{
		m_Handle = CreateWindowW(
			L"Static",
			string.c_str(),
			(parent ? WS_CHILD : 0) | SS_CENTER,
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
		m_Listener.SetQualifier(static_cast<void*>(m_Handle));

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
		m_Listener.SetQualifier(static_cast<void*>(m_Handle));

		ShowWindow(m_Handle, SW_SHOW);

		if (font)
			SetFont(font);
	}

	TextEntry::TextEntry(const Vec2i& size, const Vec2i& position, const std::wstring& string, Control* parent, Font* font)
		: Control(size, position, string, parent, font)
	{
		m_Handle = CreateWindowW(
			L"Edit",
			string.c_str(),
			(parent ? WS_CHILD : 0) | WS_BORDER,
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
		m_Listener.SetQualifier(static_cast<void*>(m_Handle));

		ShowWindow(m_Handle, SW_SHOW);

		if (font)
			SetFont(font);

		m_Listener.AddHook(EventType::TextEntered, Hook("TextEntry.DefaultTextEntered", [&](const std::any& param)
		{
			std::int32_t length = GetWindowTextLengthW(m_Handle) + 1;
			wchar_t* text = (wchar_t*)alloca(sizeof(wchar_t) * length);

			GetWindowTextW(m_Handle, text, length);

			m_String = text;
		}));
	}

}