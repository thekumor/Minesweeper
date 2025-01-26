#include "Timers.h"

namespace mines
{
    
    Timer::Timer(std::uint32_t repetitions, void (*callback)(HWND, UINT, UINT_PTR, DWORD))
        : m_Id(++s_LastTimerId), m_Repetitions(repetitions), m_Callback(callback)
    {
        Apply();
    }

	Timer::Timer(std::uint32_t repetitions, std::uint32_t elapse, void (*callback)(HWND, UINT, UINT_PTR, DWORD))
        : m_Id(++s_LastTimerId), m_Repetitions(repetitions), m_Elapse(elapse), m_Callback(callback)
	{
        Apply();
    }

    Timer::Timer(Window* owner, std::uint32_t repetitions, std::uint32_t elapse, void (*callback)(HWND, UINT, UINT_PTR, DWORD))
        : m_Owner(owner), m_Id(++s_LastTimerId), m_Repetitions(repetitions), m_Elapse(elapse), m_Callback(callback)
    {
        Apply();
    }

    void Timer::s_TimerProc(HWND, UINT, UINT_PTR, DWORD)
	{
		PostQuitMessage(1);
    }

    void Timer::SetWindow(Window* window)
    {
        m_Owner = window;
    }

	void Timer::Apply() const
	{
        UINT_PTR timer = SetTimer(
            (m_Owner ? m_Owner->m_Handle : nullptr),
            m_Id,
            m_Elapse,
            m_Callback
        );
        CheckErrors("SetTimer");
	}

	TimerData::TimerData(const std::any& data)
        : Data(data)
    {}

}