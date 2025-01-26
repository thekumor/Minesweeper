//********************************************************************************************
// File: Timers.h
// Purpose: Has timers that trigger every x seconds.
// 
// Authors: The Kumor
//********************************************************************************************

#pragma once

// STL
#include <cstdint>
#include <functional>
#include <windows.h>

// Minesweeper
#include <Minesweeper/BaseClass.h>
#include <Minesweeper/Events.h>
#include <Minesweeper/Errors.h>
#include <Minesweeper/Window.h>

namespace mines
{

	//------------------------------------------------------------------------------------
	// Stuff that is passed to callback.
	//------------------------------------------------------------------------------------
	struct TimerData
	{
		TimerData(const std::any& data);
		TimerData() = default;

		// Whatever you want the timer to receive.
		std::any Data = MINES_NODATA;
	};

	static std::uint32_t s_LastTimerId;

	//------------------------------------------------------------------------------------
	// Timer that runs a function n times and every x seconds.
	//------------------------------------------------------------------------------------
	class Timer : public BaseClass
	{
	public:
		Timer(std::uint32_t repetitions, void (*callback)(HWND, UINT, UINT_PTR, DWORD));
		Timer(std::uint32_t repetitions, std::uint32_t elapse, void (*callback)(HWND, UINT, UINT_PTR, DWORD));
		Timer(Window* owner, std::uint32_t repetitions, std::uint32_t elapse, void (*callback)(HWND, UINT, UINT_PTR, DWORD));
		Timer() = default;

		// Is called when timer gets a tick.
		static void CALLBACK s_TimerProc(HWND, UINT, UINT_PTR, DWORD);

		inline std::uint64_t GetId() const { return m_Id; }

		// Because of how WinAPI works, we need to provide a timer with some window.
		void SetWindow(Window* window);

		// Creates a WinAPI timer with member variables acting as config.
		void Apply() const;

	private:
		Window* m_Owner = nullptr;
		std::uint64_t m_Id = 0;
		std::uint32_t m_Repetitions = 1, m_Elapse = 1000;
		void (*m_Callback)(HWND, UINT, UINT_PTR, DWORD) = nullptr;
	};

}

// The Kumor