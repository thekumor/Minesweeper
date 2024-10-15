#pragma once

#include <windows.h>

#include <string>

#include <Minesweeper/BaseClass.h>
#include <Minesweeper/Errors.h>

namespace mines
{
	class Font : public BaseClass
	{
	public:
		friend class Entity;

		Font(const std::wstring& path, std::int32_t size);
		Font() = default;
		~Font();

	private:
		HFONT m_Handle = nullptr;
		std::wstring m_Name;
		std::int32_t m_Size;
	};
}