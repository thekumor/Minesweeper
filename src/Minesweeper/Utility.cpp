#include "Utility.h"

namespace mines
{
	Font::Font(const std::wstring& name, std::int32_t size)
		: m_Name(name), m_Size(size)
	{
		m_Handle = CreateFont(
			size,
			0,
			0,
			0,
			FW_DONTCARE,
			FALSE,
			FALSE,
			FALSE,
			DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_SWISS,
			m_Name.c_str()
		);
		CheckErrors("Font.m_Handle");
	}

	Font::~Font()
	{
		DeleteObject(m_Handle);
	}
}