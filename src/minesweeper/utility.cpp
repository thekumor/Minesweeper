#include "utility.h"

namespace mwr
{

	Timer::Timer(std::int32_t interval, TIMERPROC callback, HWND handle)
		: m_Interval(interval), m_Procedure(callback), m_Handle(handle)
	{
		s_TimersTotal++;
		m_Id = Timer::s_TimersTotal;

		SetTimer(handle, m_Id, m_Interval, callback);
		MsgIfError("Timer.SetTimer");
	}

	Timer::~Timer()
	{
		BOOL kill = KillTimer(m_Handle, m_Id);
		MsgIfError("Timer.KillTimer");
	}

	std::int32_t Timer::s_TimersTotal = 0;

}