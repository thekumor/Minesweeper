#include "Entities.h"

namespace mines
{

	Entity::Entity(const std::wstring& text, const Vector2& size, const Vector2& position, FragileEntityPtr parent)
		: m_Parent(parent), m_Size(size), m_Position(position), m_Text(text)
	{
	
	}

	void Entity::SetPosition(const Vector2& position)
	{
		SetWindowPos(m_Handle, nullptr, position.x, position.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}

	void Entity::SetSize(const Vector2& size)
	{
		SetWindowPos(m_Handle, nullptr, 0, 0, size.x, size.y, SWP_NOREPOSITION | SWP_NOZORDER);
	}

	void Entity::SetText(const std::wstring& text)
	{
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

	Text::Text(const std::wstring& text, const Vector2& size, const Vector2& position, FragileEntityPtr parent)
		: Entity(text, size, position, parent)
	{
	
	}

}