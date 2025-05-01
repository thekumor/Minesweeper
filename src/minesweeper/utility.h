#pragma once

// STL
#include <cstdint>

// WinAPI
#include <windows.h>

// Minesweeper
#include <minesweeper/error.h>

namespace mwr
{

	class Timer
	{
	public:
		Timer(std::int32_t interval, TIMERPROC callback, HWND handle = nullptr);
		Timer() = default;
		~Timer();

		static std::int32_t s_TimersTotal;
		
	private:
		HWND m_Handle;
		UINT_PTR m_Id;
		TIMERPROC m_Procedure;
		std::int32_t m_Interval;
	};

}