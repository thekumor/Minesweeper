#include "timer.h"

namespace mwr
{

	Timer::Timer(std::int32_t interval, HWND handle)
		: m_Interval(interval), m_Handle(handle)
	{
		s_TimersTotal++;
		m_Id = Timer::s_TimersTotal;

		SetTimer(handle, m_Id, m_Interval, nullptr);
		MsgIfError("Timer.SetTimer");

		m_Listener.SetQualifier(reinterpret_cast<void*>(m_Id));
		m_Listener.SetTag("Timer");
	}

	Timer::~Timer()
	{
		BOOL kill = KillTimer(m_Handle, m_Id);
		MsgIfError("Timer.KillTimer");
	}

	std::int32_t Timer::s_TimersTotal = 0;

}