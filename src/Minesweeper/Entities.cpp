#include "Entities.h"

namespace mines
{

	Entity::Entity(const std::wstring& text, const Vector2& size, const Vector2& position, FragileEntityPtr parent)
		: m_Parent(parent), m_Size(size), m_Position(position), m_Text(text)
	{
	
	}

	HWND Entity::GetHandle() const
	{
		return m_Handle;
	}

	void Entity::SetPosition(const Vector2& position)
	{
		m_Position = position;
		SetWindowPos(m_Handle, nullptr, position.x, position.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}

	void Entity::SetSize(const Vector2& size)
	{
		m_Size = size;
		SetWindowPos(m_Handle, nullptr, 0, 0, size.x, size.y, SWP_NOREPOSITION | SWP_NOZORDER);
	}

	void Entity::SetText(const std::wstring& text)
	{
		m_Text = text;
		SetWindowText(m_Handle, text.c_str());
	}

	void Entity::Show()
	{
		m_IsVisible = true;
		ShowWindow(m_Handle, SW_SHOW);
	}

	void Entity::Hide()
	{
		m_IsVisible = false;
		ShowWindow(m_Handle, SW_HIDE);
	}

	Entity::operator HWND()
	{
		return GetHandle();
	}

	Text::Text(const std::wstring& text, const Vector2& size, const Vector2& position, FragileEntityPtr parent)
		: Entity(text, size, position, parent)
	{
		m_Handle = CreateWindow(
			L"Static",
			text.c_str(),
			WS_VISIBLE | (parent ? WS_CHILD : 0),
			position.x,
			position.y,
			size.x,
			size.y,
			(parent ? static_cast<HWND>(*parent) : nullptr),
			nullptr,
			reinterpret_cast<HINSTANCE>(GetModuleHandle(nullptr)),
			0
		);
		CheckErrors("Text.m_Handle");
		
		Show();
	}

	Button::Button(const std::wstring& text, const Vector2& size, const Vector2& position, FragileEntityPtr parent)
		: Entity(text, size, position, parent)
	{
		m_Handle = CreateWindow(
			L"Button",
			text.c_str(),
			WS_VISIBLE | BS_PUSHBUTTON | (parent ? WS_CHILD : 0),
			position.x,
			position.y,
			size.x,
			size.y,
			(parent ? static_cast<HWND>(*parent) : nullptr),
			nullptr,
			reinterpret_cast<HINSTANCE>(GetModuleHandle(nullptr)),
			0
		);
		CheckErrors("Button.m_Handle");

		Show();
	}

	EditBox::EditBox(const std::wstring& text, const Vector2& size, const Vector2& position, FragileEntityPtr parent)
		: Entity(text, size, position, parent)
	{
		m_Handle = CreateWindow(
			L"Edit",
			text.c_str(),
			WS_VISIBLE | WS_TABSTOP | (parent ? WS_CHILD : 0),
			position.x,
			position.y,
			size.x,
			size.y,
			(parent ? static_cast<HWND>(*parent) : nullptr),
			nullptr,
			reinterpret_cast<HINSTANCE>(GetModuleHandle(nullptr)),
			0
		);
		CheckErrors("EditBox.m_Handle");

		Show();
	}

	Img::Img(const std::wstring& path, const Vector2& size, const Vector2& position, FragileEntityPtr parent)
		: Entity(path, size, position, parent)
	{
		//Image image(path.c_str());
	}

}