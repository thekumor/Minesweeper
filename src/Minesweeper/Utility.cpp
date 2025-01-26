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

		m_EventReceiver.SetQualifier(reinterpret_cast<event_qualifier>(m_Handle));

		m_EventReceiver.AddHook(EventType::Resize, Hook("Font.Resize", [&](const EventData& data)
		{
			DeleteObject(static_cast<HGDIOBJ>(m_Handle));

			WindowSize windowSize = std::any_cast<WindowSize>(data.Value);
			WindowSize originalSize(WINDOW_WIDTH, WINDOW_HEIGHT);
			Vector2<float> fraction = {
				static_cast<float>(windowSize.x) / originalSize.x,
				static_cast<float>(windowSize.y) / originalSize.y
			};

			std::int32_t newSize = m_Size * fraction.Y;

			this->m_Handle = CreateFont(
				newSize,
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

			m_EventSource.CallEvent(EventType::Update, m_Handle);
		}));
	}

	Font::~Font()
	{
		DeleteObject(m_Handle);
	}
}