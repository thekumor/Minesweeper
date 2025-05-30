#pragma once

// STL
#include <cstdint>

// WinAPI
#include <windows.h>

// Minesweeper
#include <minesweeper/error.h>
#include <minesweeper/events.h>
#include <minesweeper/base_class.h>

namespace mwr
{

	class Timer : public BaseClass
	{
	public:
		Timer(std::int32_t interval, HWND handle = nullptr);
		Timer() = default;
		~Timer();

		static std::int32_t s_TimersTotal;

	private:
		HWND m_Handle;
		UINT_PTR m_Id;
		std::int32_t m_Interval;
	};

}