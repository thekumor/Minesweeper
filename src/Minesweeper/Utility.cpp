#include "Utility.h"

namespace mines
{
	Font::Font(const std::wstring& name, std::int32_t size, HWND window)
		: m_Name(name), m_WindowHandle(window), m_Size(size), m_OriginalSize(size)
	{
		m_OriginalWindowSize = GetWindowSize(window);

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

		m_EventReceiver.SetQualifier(reinterpret_cast<event_qualifier>(m_Handle));

#ifdef MINES_CLASSES_EVENTACTIVE
		m_EventReceiver.AddHook(EventType::Resize, Hook("Font.Resize", [this](const EventData& data)
		{
			Vector2<WORD> windowSize = std::any_cast<Vector2<WORD>>(data.Value);

			float newFontSize = (m_OriginalSize * windowSize.x) / m_OriginalWindowSize.x;
			newFontSize = round(newFontSize);
			m_Size = newFontSize;

			// Recreates the font.
			DeleteObject(m_Handle);
			m_Handle = CreateFont(
				newFontSize,
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

			m_EventSource.CallEvent(EventType::Update, m_Handle);
		}));
#endif
	}

	Font::~Font()
	{
		DeleteObject(m_Handle);
	}
}