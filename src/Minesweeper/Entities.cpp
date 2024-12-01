#include "Entities.h"

namespace mines
{

	Control::Control(const std::wstring& text, const Vec2& size, const Vec2& position, Control* parent, ControlFlags flags)
		: m_Parent(parent), m_Size(size), m_TranslatedSize(size), m_Position(position), m_TranslatedPosition(position),
		m_Text(text), m_Flags(flags)
	{
		m_EventReceiver.AddHook(EventType::Resize, Hook("Control.Resize", [this](const EventData& data)
		{
			if (!HAS_FLAG(m_Flags, ControlFlags::IgnoreResize))
			{
				// Doesn't change the size, just re-translates it to fit the new resolution.
				SetSize(m_Size);
				SetPosition(m_Position);
			}
		}
		));
	}

	Control::~Control()
	{
		DeleteObject(m_Handle);
	}

	HWND Control::GetHandle() const
	{
		return m_Handle;
	}

	void Control::SetPosition(const Vec2& position)
	{
		m_Position = position;

		if (m_Parent)
		{
			HWND parentHandle = m_Parent->m_Handle;
			RECT rect;

			if (GetWindowRect(parentHandle, &rect))
			{
				Vector2<LONG> parentSize = { rect.right - rect.left, rect.bottom - rect.top };
				Vector2<std::int32_t> originalParentSize = m_Parent->m_Size;
				Vector2<float> fraction = {
					static_cast<float>(parentSize.x) / originalParentSize.x,
					static_cast<float>(parentSize.y) / originalParentSize.y
				};

				m_TranslatedPosition = m_Position * fraction;
			}
		}
		else
			m_TranslatedPosition = position;

		SetWindowPos(m_Handle, nullptr, m_TranslatedPosition.x, m_TranslatedPosition.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}

	void Control::SetSize(const Vec2& size)
	{
		m_Size = size;

		if (m_Parent)
		{
			HWND parentHandle = m_Parent->m_Handle;
			RECT rect;
			if (GetWindowRect(parentHandle, &rect))
			{
				Vector2<LONG> parentSize = { rect.right - rect.left, rect.bottom - rect.top };
				Vector2<std::int32_t> originalParentSize = m_Parent->m_Size;
				Vector2<float> fraction = {
					static_cast<float>(parentSize.x) / originalParentSize.x,
					static_cast<float>(parentSize.y) / originalParentSize.y
				};

				m_TranslatedSize = m_Size * fraction;
			}
		}
		else
			m_TranslatedSize = size;

		SetWindowPos(m_Handle, nullptr, 0, 0, m_TranslatedSize.x, m_TranslatedSize.y, SWP_NOMOVE | SWP_NOZORDER);
	}

	void Control::SetText(const std::wstring& text)
	{
		m_Text = text;
		SetWindowText(m_Handle, text.c_str());
	}

	void Control::Show()
	{
		m_IsVisible = true;
		ShowWindow(m_Handle, SW_SHOW);
	}

	void Control::Hide()
	{
		m_IsVisible = false;
		ShowWindow(m_Handle, SW_HIDE);
	}

	void Control::SetFlags(ControlFlags flags)
	{
		m_Flags = flags;
	}

	void Control::SetFont(Font* font)
	{
		SendMessage(m_Handle, WM_SETFONT, reinterpret_cast<WPARAM>(font->m_Handle), TRUE);

		if (m_Font)
			m_Font->m_EventSource.UnpinReceiver(&m_EventReceiver);

		if (font)
			font->m_EventSource.PinReceiver(&m_EventReceiver);

		m_Font = font;

		m_EventReceiver.ReplaceHook(EventType::Update, Hook("Control.FontUpdate", [this](const EventData& data)
		{
			HFONT fontHandle = std::any_cast<HFONT>(data.Value);
			SendMessage(m_Handle, WM_SETFONT, reinterpret_cast<WPARAM>(fontHandle), TRUE);
		}));
	}

	void Control::Close()
	{
		CloseWindow(m_Handle);
	}

	Text::Text(const std::wstring& text, const Vec2& size, const Vec2& position, Control* parent)
		: Control(text, size, position, parent)
	{
		m_Handle = CreateWindow(
			L"Static",
			text.c_str(),
			WS_VISIBLE | (parent ? WS_CHILD : 0),
			position.x,
			position.y,
			size.x,
			size.y,
			(parent ? parent->m_Handle : nullptr),
			nullptr,
			reinterpret_cast<HINSTANCE>(GetModuleHandle(nullptr)),
			0
		);
		CheckErrors("Text.m_Handle");

		GetEventReceiver().SetQualifier(reinterpret_cast<event_qualifier>(m_Handle));
		Show();
	}

	Text::Text(const std::wstring& text, const Vec2& size, const Vec2& position, Control* parent, Font* font)
		: Text(text, size, position, parent)
	{
		SetFont(font);
	}

	Button::Button(const std::wstring& text, const Vec2& size, const Vec2& position, Control* parent)
		: Control(text, size, position, parent)
	{
		m_Handle = CreateWindow(
			L"Button",
			text.c_str(),
			WS_VISIBLE | BS_PUSHBUTTON | (parent ? WS_CHILD : 0),
			position.x,
			position.y,
			size.x,
			size.y,
			(parent ? parent->m_Handle : nullptr),
			nullptr,
			reinterpret_cast<HINSTANCE>(GetModuleHandle(nullptr)),
			0
		);
		CheckErrors("Button.m_Handle");

		GetEventReceiver().SetQualifier(reinterpret_cast<event_qualifier>(m_Handle));
		Show();
	}

	EditBox::EditBox(const std::wstring& text, const Vec2& size, const Vec2& position, Control* parent)
		: Control(text, size, position, parent)
	{
		m_Handle = CreateWindow(
			L"Edit",
			text.c_str(),
			WS_VISIBLE | WS_TABSTOP | (parent ? WS_CHILD : 0),
			position.x,
			position.y,
			size.x,
			size.y,
			(parent ? parent->m_Handle : nullptr),
			nullptr,
			reinterpret_cast<HINSTANCE>(GetModuleHandle(nullptr)),
			0
		);
		CheckErrors("EditBox.m_Handle");

		GetEventReceiver().SetQualifier(reinterpret_cast<event_qualifier>(m_Handle));
		Show();
	}

	Img::Img(const std::wstring& text, const Vec2& size, const Vec2& position, Control* parent)
		: Control(text, size, position, parent)
	{
		m_HandleBitmap = static_cast<HBITMAP>(LoadImage(nullptr, text.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		CheckErrors("LoadImage");
		if (!m_HandleBitmap)
			MakeError("Cannot load a bitmap", false);
	}

	Img::~Img()
	{
		if (m_HandleBitmap)
			DeleteObject(reinterpret_cast<HGDIOBJ>(m_HandleBitmap));
	}

	void Img::Draw(HDC windowDC)
	{
		BITMAP bitmap = { 0 };
		if (!GetObject(reinterpret_cast<HGDIOBJ>(m_HandleBitmap), sizeof(BITMAP), reinterpret_cast<LPVOID>(&bitmap)))
		{
			MakeError("Cannot make a bitmap");
			return;
		}

		HDC hdc = CreateCompatibleDC(windowDC);
		CheckErrors("CreateCompatibleDC");
		if (!hdc)
			return;

		SelectObject(hdc, m_HandleBitmap);
		BitBlt(windowDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdc, m_Position.x, m_Position.y, SRCCOPY);
		CheckErrors("BitBlt");

		SelectObject(hdc, windowDC);
		DeleteDC(hdc);
	}

}