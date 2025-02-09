#include "Application.h"

namespace mines
{
	Application::Application(const Vec2& windowSize, const std::wstring& windowTitle)
		: m_Window(windowSize, windowTitle)
	{
	}

	int Application::Run()
	{
		Window& wnd = m_Window;

		using ScenePtr = std::shared_ptr<Scene>;
		using TextPtr = std::shared_ptr<Text>;
		using ButtonPtr = std::shared_ptr<Button>;

		Font defaultFont(L"Segoe UI", 24);
		Font bigFont(L"Segoe UI", 36);

		ScenePtr minefieldScene = wnd.CreateScene("Mine field");
		{
			TextPtr timeLeft = minefieldScene->CreateControl<Text>(
				L"10:00", Vec2(200, 64), Vec2(40, 40), &wnd
			);
			timeLeft->SetFont(&bigFont);

			TextPtr flagsLeft = minefieldScene->CreateControl<Text>(
				L"4 flags left", Vec2(200, 64), Vec2(280, 40), &wnd
			);
			flagsLeft->SetFont(&bigFont);

			ButtonPtr newGame = minefieldScene->CreateControl<Button>(
				L"New Game", Vec2(170, 48), Vec2(1200, 200), &wnd
			);
			newGame->SetFont(&bigFont);

			ButtonPtr loadGame = minefieldScene->CreateControl<Button>(
				L"Load Game", Vec2(170, 48), Vec2(1200, 260), &wnd
			);
			loadGame->SetFont(&bigFont);

			ButtonPtr saveGame = minefieldScene->CreateControl<Button>(
				L"Save Game", Vec2(170, 48), Vec2(1200, 320), &wnd
			);
			saveGame->SetFont(&bigFont);

			ButtonPtr myLeaderboard = minefieldScene->CreateControl<Button>(
				L"Leaderboard", Vec2(170, 48), Vec2(1200, 380), &wnd
			);
			myLeaderboard->SetFont(&bigFont);

			for (std::int32_t y = 0; y < 12; y++)
			{
				for (std::int32_t x = 0; x < 28; x++)
				{
					ButtonPtr field = minefieldScene->CreateControl<Button>(
						L"", Vec2(40, 40), Vec2(40 + x * 40, 200 + y * 40), &wnd
					);
					field->SetFont(&defaultFont);
				}
			}
		}

		ScenePtr difficultyScene = wnd.CreateScene("Difficulty");
		{

		}

		ScenePtr leaderboardScene = wnd.CreateScene("Leaderboard");
		{

		}

		ScenePtr nameScene = wnd.CreateScene("Name");
		{

		}

		wnd.m_Scenes.push_back(minefieldScene);
		wnd.m_Scenes.push_back(difficultyScene);
		wnd.m_Scenes.push_back(leaderboardScene);
		wnd.m_Scenes.push_back(nameScene);

		MSG msg;
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