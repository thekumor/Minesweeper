#include "Timers.h"

namespace mines
{
    
    Timer::Timer(std::uint32_t repetitions, std::function<void(HWND, UINT, UINT_PTR, DWORD)> callback)
        : m_Id(++s_LastTimerId), m_Repetitions(repetitions), m_Callback(callback)
    {
        Apply();
    }

	Timer::Timer(std::uint32_t repetitions, std::uint32_t elapse, std::function<void(HWND, UINT, UINT_PTR, DWORD)> callback)
        : m_Id(++s_LastTimerId), m_Repetitions(repetitions), m_Elapse(elapse), m_Callback(callback)
	{
        Apply();
    }

    Timer::Timer(Window* owner, std::uint32_t repetitions, std::uint32_t elapse, std::function<void(HWND, UINT, UINT_PTR, DWORD)> callback)
        : m_Owner(owner), m_Id(++s_LastTimerId), m_Repetitions(repetitions), m_Elapse(elapse), m_Callback(callback)
    {
        Apply();
    }

    void Timer::s_TimerProc(HWND, UINT, UINT_PTR, DWORD)
    {
        PostQuitMessage(1);
    }

    std::uint64_t Timer::GetId() const
    {
        return m_Id;
    }

    void Timer::SetWindow(Window* window)
    {
        m_Owner = window;
    }

	void Timer::Apply() const
	{
        UINT_PTR timer = SetTimer(
            m_Owner ? m_Owner->m_Handle : nullptr,
            m_Id,
            m_Elapse,
            s_TimerProc
        );
        CheckErrors("SetTimer");
	}

	TimerData::TimerData(const std::any& data)
        : Data(data)
    {}

}