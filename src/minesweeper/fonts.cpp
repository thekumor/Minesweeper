#include "fonts.h"

namespace mwr
{

	Font::Font(const std::wstring& name, std::int32_t size, std::uint32_t style)
		: m_Style(style), m_Size(size), m_ScreenSize(size), m_Name(name)
	{
		bool isSymbol = (name == L"Webdings" || name == L"Wingdings");

		m_Handle = CreateFontW(
			size,
			0,
			0,
			0,
			style & FontStyle::Bold ? FW_BOLD : FW_DONTCARE,
			style & FontStyle::Italic ? TRUE : FALSE,
			style & FontStyle::Underline ? TRUE : FALSE,
			style & FontStyle::StrikeOut ? TRUE : FALSE,
			isSymbol ? SYMBOL_CHARSET : EASTEUROPE_CHARSET,
			OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			CLEARTYPE_QUALITY,
			FF_DONTCARE,
			isSymbol ? L"Arial" : name.c_str()
		);
		MsgIfError("Font.m_Handle");

		m_Listener.AddHook(EventType::Resize, Hook("Font.DefaultResize", [&](const std::any& param)
		{
			Vec2<float> fraction = std::any_cast<Vec2<float>>(param);

			bool isSymbol = (m_Name == L"Webdings" || m_Name == L"Wingdings");

			m_Handle = CreateFontW(
				//m_Size * fraction.x,
				m_Size * fraction.y,
				0,
				0,
				0,
				m_Style & FontStyle::Bold ? FW_BOLD : FW_DONTCARE,
				m_Style & FontStyle::Italic ? TRUE : FALSE,
				m_Style & FontStyle::Underline ? TRUE : FALSE,
				m_Style & FontStyle::StrikeOut ? TRUE : FALSE,
				isSymbol ? SYMBOL_CHARSET : EASTEUROPE_CHARSET,
				OUT_DEFAULT_PRECIS,
				CLIP_DEFAULT_PRECIS,
				CLEARTYPE_QUALITY,
				FF_DONTCARE,
				isSymbol ? L"Arial" : m_Name.c_str()
			);
			MsgIfError("Font.m_Handle");

			m_Dispatcher.CallEvent(EventType::FontsUpdated);
		}));

		m_Listener.AddHook(EventType::ControlDestroyed, Hook("Font.ControlDestroyed", [&](const std::any& param)
		{
			EventListener* listener = std::any_cast<EventListener*>(param);
			m_Dispatcher.RemoveListenerForce(listener);
		}));

		m_Listener.SetTag("Font");
	}

	Font::~Font()
	{
		DeleteObject(m_Handle);
	}

	void Font::SetSize(std::int32_t size, bool isScreen)
	{
		if (m_Handle)
			DeleteObject(m_Handle);

		m_Handle = CreateFontW(
			size,
			0,
			0,
			0,
			m_Style & FontStyle::Bold ? FW_BOLD : FW_DONTCARE,
			m_Style & FontStyle::Italic ? TRUE : FALSE,
			m_Style & FontStyle::Underline ? TRUE : FALSE,
			m_Style & FontStyle::StrikeOut ? TRUE : FALSE,
			EASTEUROPE_CHARSET,
			OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			CLEARTYPE_QUALITY,
			FF_DONTCARE, // FF_MODERN ?
			m_Name.c_str()
		);
		MsgIfError("Font.m_Handle");

		if (isScreen)
			m_ScreenSize = size;
		else
			m_Size = size;
	}

}