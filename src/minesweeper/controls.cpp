#include "controls.h"

namespace mwr
{

	Control::Control(const Vec2i& size, const Vec2i& position, const std::wstring& string, Control* parent, Font* font)
		: m_Parent(parent), m_Font(font), m_Handle(nullptr), m_Size(size), m_Position(position), m_String(string),
		m_ScreenSize(size), m_ScreenPosition(position)
	{
		if (parent)
			parent->m_Children.push_back(this);

		m_Listener.AddHook(EventType::Resize, Hook("Control.DefaultResize", [&](const std::any& param)
		{
			Vec2<float> fraction = std::any_cast<Vec2<float>>(param);

			Vec2i newControlSize(m_Size.x * fraction.x, m_Size.y * fraction.y);
			Vec2i newControlPos(m_Position.x * fraction.x, m_Position.y * fraction.y);

			SetPosition(newControlPos, true);
			SetSize(newControlSize, true);
		}));
	}

	Control::~Control()
	{
		DestroyWindow(m_Handle);
	}

	Control* Control::GetParent()
	{
		return m_Parent;
	}

	Vec2i Control::s_GetSize(HWND handle)
	{
		RECT rect;
		GetWindowRect(handle, &rect);

		return Vec2i(rect.right - rect.left, rect.bottom - rect.top);
	}

	const std::vector<Control*>& Control::GetChildren()
	{
		return m_Children;
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
			m_Size = size;
	}

	void Control::SetString(const std::wstring& string)
	{
		SetWindowTextW(m_Handle, string.c_str());
		m_String = string;
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

}