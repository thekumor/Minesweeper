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

		std::shared_ptr<Scene> minefieldScene = wnd.CreateScene("Mine field");
		std::shared_ptr<Scene> difficultyScene = wnd.CreateScene("Difficulty");
		std::shared_ptr<Scene> leaderboardScene = wnd.CreateScene("Leaderboard");
		std::shared_ptr<Scene> nameScene = wnd.CreateScene("Name");
		wnd.m_Scenes.push_back(minefieldScene);
		wnd.m_Scenes.push_back(difficultyScene);
		wnd.m_Scenes.push_back(leaderboardScene);
		wnd.m_Scenes.push_back(nameScene);

		std::int32_t i = 0;
		for (int y = 0; y < 20; y++)
			for (int x = 0; x < 30; x++)
			{
				std::shared_ptr<Button> field = minefieldScene->CreateEntity<Button>(L"",
					Vector2<>(32, 32), Vector2<>(x * 33 + 50, y * 33 + 150), &wnd);

				i++;
			}

		std::shared_ptr<Text> timeLeft = minefieldScene->CreateEntity<Text>(L"10:00",
			Vector2<>(100, 32), Vector2<>(50, 40), &wnd);

		std::shared_ptr<Text> flagsLeft = minefieldScene->CreateEntity<Text>(L"5 flags left",
			Vector2<>(100, 32), Vector2<>(250, 40), &wnd);

		std::shared_ptr<Button> newGame = minefieldScene->CreateEntity<Button>(L"New Game",
			Vector2<>(290, 32), Vector2<>(1100, 100), &wnd);

		std::shared_ptr<Button> leaderboardButton = minefieldScene->CreateEntity<Button>(L"Leaderboard",
			Vector2<>(290, 32), Vector2<>(1100, 150), &wnd);

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