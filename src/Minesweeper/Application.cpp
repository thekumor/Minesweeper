#include "Application.h"

namespace mines
{
	Application::Application(const Vector2<>& windowSize, const std::wstring& windowTitle)
		: m_Window(windowSize, windowTitle)
	{
	}

	int Application::Run()
	{
		Window& wnd = m_Window;

		std::shared_ptr<Scene> mainScene = wnd.CreateScene("Main");
		
		for (int i = 0; i < 30; i++)
			std::shared_ptr<Button> btn = mainScene->CreateEntity<Button>(std::to_wstring(i), { 32, 32 }, {i * 40 + 100, 200}, &wnd);

		MSG msg = {};
		while (GetMessage(&msg, nullptr, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		return EXIT_SUCCESS;
	}

	LeaderboardEntry::LeaderboardEntry(const std::wstring& playerName, std::int32_t score)
		: m_PlayerName(playerName), m_Score(score)
	{
	}

	void Leaderboard::AddEntry(const LeaderboardEntry& entry)
	{
		m_Entries.emplace_back(entry);
		Sort();
	}

	void Leaderboard::RemoveEntry(const LeaderboardEntry& entry)
	{
		// 'erase-remove' idiom
		auto newEnd = std::remove(m_Entries.begin(), m_Entries.end(), entry);
		m_Entries.erase(newEnd, m_Entries.end());

		Sort();
	}

	void Leaderboard::RemoveEntry(std::int32_t index)
	{
		m_Entries.erase(m_Entries.begin() + index);
		Sort();
	}

	void Leaderboard::Draw()
	{
	}

	void Leaderboard::Sort()
	{
		std::sort(m_Entries.begin(), m_Entries.end());
	}

}