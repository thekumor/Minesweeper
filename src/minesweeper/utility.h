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

	template <typename T>
	class Handle
	{
	public:
		Handle(T* value) : m_Value(value) {}
		Handle() = default;
		~Handle() = default;

		bool IsValid() const { return m_IsValid; }
		void SetValid(bool valid) { m_IsValid = valid; }

		T* operator*() const { return m_Value; }

	private:
		T* m_Value;
		bool m_IsValid;
	};

}