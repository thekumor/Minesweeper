#include "fonts.h"

namespace mwr
{

	Font::Font(const std::wstring& name, std::int32_t size, std::uint32_t style)
		: m_Style(style), m_Size(size), m_Name(name)
	{
		m_Handle = CreateFontW(
			size,
			0,
			0,
			0,
			style & FontStyle::Bold ? FW_BOLD : FW_DONTCARE,
			style & FontStyle::Italic ? TRUE : FALSE,
			style & FontStyle::Underline ? TRUE : FALSE,
			style & FontStyle::StrikeOut ? TRUE : FALSE,
			EASTEUROPE_CHARSET,
			OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			CLEARTYPE_QUALITY,
			FF_DONTCARE, // FF_MODERN ?
			name.c_str()
		);
		MsgIfError("Font.m_Handle");
	}

}