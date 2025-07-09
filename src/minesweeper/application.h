#pragma once

// STL
#include <string>
#include <list>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <fstream>

// WinAPI
#include <windows.h>

// Minesweeper
#include <minesweeper/window.h>
#include <minesweeper/vectors.h>
#include <minesweeper/controls.h>
#include <minesweeper/fonts.h>
#include <minesweeper/timer.h>
#include <minesweeper/events.h>

#ifdef _DEBUG
void* operator new(size_t size);
void operator delete(void* ptr, size_t size);
#endif

namespace mwr
{

	class Scene;
	class Leaderboard;

	class Application
	{
	public:
		Application(HINSTANCE instance, const Vec2i& size, const std::wstring& title);
		Application() = default;
		~Application();

		int Run();
		Scene* CreateScene(const std::string& name);
		Timer* CreateTimer(std::int32_t delay);
		void DestroyTimer(Timer* ptr);
		void OpenScene(Scene* scene);
		void CloseScene(Scene* scene);
		void SwitchScene(Scene* scene);

	private:
		Window m_MainWindow;
		HINSTANCE m_Instance;
		std::vector<Scene*> m_Scenes;
		std::vector<Timer*> m_Timers;
		Scene* m_CurrentScene;
	};

	class Scene : public BaseClass
	{
	public:
		Scene(const std::string& name);
		Scene() = default;
		~Scene();

		template <typename T>
		T* CreateControl(const Vec2i& size, const Vec2i& position, const std::wstring& string, Control* parent = nullptr, Font* font = nullptr)
		{
			T* object = new T(size, position, string, parent, font);
			Control* control = dynamic_cast<Control*>(object);
			m_Controls.emplace_back(control);

			return object;
		}

		Control* GetControlByTag(const std::string& tag);

	private:
		std::string m_Name;
		std::vector<Control*> m_Controls;
	};

#define MWR_DUMMY_DATE Date(0, 0, 0, 0, 0, 0)
	struct Date
	{
		Date(std::uint32_t year, std::uint32_t month, std::uint32_t day, std::uint32_t hour, std::uint32_t minute, std::uint32_t second);
		Date() = default;
		std::string GetDateFormat(const std::string& format);

		std::uint32_t Year, Month, Day, Hour, Minute, Second;
	};

	struct LeaderboardEntry
	{
		LeaderboardEntry(const std::string& player, Date timestamp, std::uint32_t time, std::uint32_t flagsUsed, const std::string& difficultyName);
		LeaderboardEntry() = default;

		std::string Player, DifficultyName;
		Date Timestamp;
		std::uint32_t Time;
		std::uint32_t FlagsUsed;
	};

#define MWR_WRITE_HANDLE true
#define MWR_READ_HANDLE false

	class Leaderboard : public BaseClass
	{
	public:
		Leaderboard(const std::string& filePath);
		Leaderboard() = default;
		~Leaderboard();

		const std::vector<LeaderboardEntry>& GetEntries() const;
		void AddEntry(const LeaderboardEntry& entry);

	private:
		bool Impl_OpenFile(bool isForWriting = MWR_READ_HANDLE);
		bool Impl_UpdateFile();
		bool Impl_ReadFromFile();
		bool Impl_CloseFile(bool isForWriting = MWR_READ_HANDLE);

		HANDLE m_Write, m_Read;
		std::vector<LeaderboardEntry> m_Entries;
		std::string m_FilePath;
	};

}