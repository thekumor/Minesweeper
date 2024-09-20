//****************************************************************
// File: Application.h
// Purpose: Stores mines::Application which is the main
//			class of this project.
// 
// Authors: The Kumor
//****************************************************************

#pragma once

#include <cstdint>
#include <string>
#include <algorithm>

#include <windows.h>

#include <Minesweeper/BaseClass.h>
#include <Minesweeper/Vectors.h>
#include <Minesweeper/Window.h>
#include <Minesweeper/Timers.h>
#include <Minesweeper/Entities.h>

namespace mines
{

	//----------------------------------------------------------
	// Class that acts as an instance of the application.
	// Contains a window.
	//----------------------------------------------------------
	class Application : public BaseClass
	{
	public:
		Application(const Vector2<>& windowSize, const std::wstring& windowTitle);
		Application() = default;

		// Runs the application and puts it into it's main loop.
		int Run();

	private:
		Window m_Window;
	};

	//----------------------------------------------------------
	// Player's entry to the leader board. Has his name and score.
	//----------------------------------------------------------
	class LeaderboardEntry : public BaseClass
	{
	public:
		LeaderboardEntry(const std::wstring& playerName, std::int32_t score);
		LeaderboardEntry() = default;

		bool operator==(const LeaderboardEntry& other)
		{
			return m_PlayerName == other.m_PlayerName && m_Score == other.m_Score;
		}
		bool operator>(const LeaderboardEntry& other)
		{
			return m_Score > other.m_Score;
		}
		bool operator<(const LeaderboardEntry& other)
		{
			return m_Score < other.m_Score;
		}
		bool operator>=(const LeaderboardEntry& other)
		{
			return m_Score >= other.m_Score;
		}
		bool operator<=(const LeaderboardEntry& other)
		{
			return m_Score <= other.m_Score;
		}

	private:
		std::wstring m_PlayerName;
		std::int32_t m_Score = -1;
	};

	//----------------------------------------------------------
	// Leader board that sorts players and has capability
	// of displaying itself.
	//----------------------------------------------------------
	class Leaderboard : public BaseClass
	{
	public:
		Leaderboard() = default;

		// Adds a player into the leader board, then sorts itself.
		void AddEntry(const LeaderboardEntry& entry);

		// Removes a particular player from the leader board, then sorts itself.
		void RemoveEntry(const LeaderboardEntry& entry);

		// Removes a particular index from the leader board, then sorts itself.
		void RemoveEntry(std::int32_t index);

		// Draws the leader board onto the screen.
		// TODO: how do we even draw it here?
		void Draw();

	private:
		void Sort();
		std::vector<LeaderboardEntry> m_Entries = {};
	};

}

// The Kumor