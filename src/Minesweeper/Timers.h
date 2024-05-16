#pragma once

#include <cstdint>
#include <functional>
#include <windows.h>

#include <Minesweeper/BaseClass.h>
#include <Minesweeper/Events.h>
#include <Minesweeper/Errors.h>
#include <Minesweeper/Window.h>

namespace mines
{

	//
	// Stuff that is passed to callback.
	//
	struct TimerData
	{
		TimerData(const std::any& data);
		TimerData() = default;

		std::any Data = MINES_NODATA;
	};

	static std::uint32_t s_LastTimerId;

	//
	// Timer that runs a function n times and every x seconds.
	//
	class Timer : public BaseClass
	{
	public:
		Timer(std::uint32_t repetitions, void (*callback)(HWND, UINT, UINT_PTR, DWORD));
		Timer(std::uint32_t repetitions, std::uint32_t elapse, void (*callback)(HWND, UINT, UINT_PTR, DWORD));
		Timer(Window* owner, std::uint32_t repetitions, std::uint32_t elapse, void (*callback)(HWND, UINT, UINT_PTR, DWORD));
		Timer() = default;

		static void CALLBACK s_TimerProc(HWND, UINT, UINT_PTR, DWORD);

		std::uint64_t GetId() const;
		void SetWindow(Window* window);
		void Apply() const;

	private:
		Window* m_Owner = nullptr;
		std::uint64_t m_Id = 0;
		std::uint32_t m_Repetitions = 1, m_Elapse = 1000;
		void (*m_Callback)(HWND, UINT, UINT_PTR, DWORD) = nullptr;
	};

}