#include "application.h"

namespace mwr
{

	Application::Application(HINSTANCE instance, const Vec2i& size, const std::wstring& title)
		: m_MainWindow(instance, size, title), m_Instance(instance), m_CurrentScene(nullptr)
	{
	}

	Application::~Application()
	{
		for (auto& k : m_Scenes)
			delete k;

		for (auto& k : m_Timers)
			delete k;
	}

	static std::wstring FormatTime(std::int32_t secondsLeft)
	{
		std::uint32_t seconds = secondsLeft % 60;
		std::uint32_t minutes = secondsLeft / 60;
		std::wstring fmtSeconds = std::wstring(std::wstring(seconds < 10 ? L"0" : L"") + std::to_wstring(seconds));
		std::wstring fmtMinutes = std::wstring(std::wstring(minutes < 10 ? L"0" : L"") + std::to_wstring(minutes));
		return fmtMinutes + L":" + fmtSeconds;
	}

	int Application::Run()
	{
		Window& window = m_MainWindow;
		Font cascadia(L"Cascadia Code", 24, FontStyle::Normal);
		Font large(L"Georgia", 64, FontStyle::Bold);
		Font smol(L"Arial", 16);

		struct Specification
		{
			Vec2i minefieldSize;
			std::int32_t time, totalBombs, totalFlags;
		};

		Specification easySpec;
		easySpec.minefieldSize = { 10, 10 };
		easySpec.time = 5 * 60;
		easySpec.totalBombs = 4;
		easySpec.totalFlags = 10;

		Specification normalSpec;
		normalSpec.minefieldSize = { 15, 15 };
		normalSpec.time = 4 * 60;
		normalSpec.totalBombs = 6;
		normalSpec.totalFlags = 8;

		Specification hardSpec;
		hardSpec.minefieldSize = { 20, 20 };
		hardSpec.time = 2 * 60;
		hardSpec.totalBombs = 8;
		hardSpec.totalFlags = 6;

		Specification hellSpec;
		hellSpec.minefieldSize = { 35, 25 };
		hellSpec.time = 1 * 60;
		hellSpec.totalBombs = 20;
		hellSpec.totalFlags = 4;

		Specification* currentSpec = nullptr;

		Scene* difficultyScene = CreateScene("Difficulty Scene");
		Scene* minefieldScene = CreateScene("Minefield Scene");

		difficultyScene->AddHook(EventType::SceneOpen, Hook("Scene.Open", [&](const std::any& param)
		{
			Label* title = difficultyScene->CreateControl<Label>(Vec2i(400, 60), Vec2i(150, 30), L"Minesweeper", &window, &large);
			Button* easy = difficultyScene->CreateControl<Button>(Vec2i(200, 60), Vec2i(250, 120), L"Easy", &window, &cascadia);
			Button* normal = difficultyScene->CreateControl<Button>(Vec2i(200, 60), Vec2i(250, 200), L"Normal", &window, &cascadia);
			Button* hard = difficultyScene->CreateControl<Button>(Vec2i(200, 60), Vec2i(250, 280), L"Hard", &window, &cascadia);
			Button* hell = difficultyScene->CreateControl<Button>(Vec2i(200, 60), Vec2i(250, 360), L"Hell", &window, &cascadia);
			Label* author = difficultyScene->CreateControl<Label>(Vec2i(130, 25), Vec2i(520, 625), L"by The Kumor, (2025)", &window, &smol);

			easy->AddHook(EventType::Click, Hook("Easy.Click", [&](const std::any& param)
			{
				currentSpec = &easySpec;
				SwitchScene(minefieldScene);
			}));

			normal->AddHook(EventType::Click, Hook("Normal.Click", [&](const std::any& param)
			{
				currentSpec = &normalSpec;
				SwitchScene(minefieldScene);
			}));

			hard->AddHook(EventType::Click, Hook("Hard.Click", [&](const std::any& param)
			{
				currentSpec = &hardSpec;
				SwitchScene(minefieldScene);
			}));

			hell->AddHook(EventType::Click, Hook("Hell.Click", [&](const std::any& param)
			{
				currentSpec = &hellSpec;
				SwitchScene(minefieldScene);
			}));
		}));
		struct Game
		{
			std::int32_t secondsLeft = 0;
			std::int32_t flagsLeft = 0;
			std::wstring formattedTimeLeft;
		} game;

		Timer* roundClock;

		minefieldScene->AddHook(EventType::SceneOpen, Hook("Scene.Open", [&](const std::any& param)
		{
			roundClock = CreateTimer(1000);

			game.flagsLeft = currentSpec->totalFlags;
			game.secondsLeft = currentSpec->time;
			game.formattedTimeLeft = FormatTime(game.secondsLeft);

			const Vec2i minefieldSize(currentSpec->minefieldSize);
			const Vec2i fieldSize(32, 32);
			const Vec2i margin(30, 90);

			Vec2i windowSize = minefieldSize * fieldSize + margin + Vec2i(250, 100);
			window.SetSize(windowSize);

			Label* time = minefieldScene->CreateControl<Label>(
				Vec2i(200, 30),
				Vec2i(margin.x, 20),
				L"Time left: " + game.formattedTimeLeft,
				&window,
				&cascadia);
			time->SetTag("Time");

			Label* flags = minefieldScene->CreateControl<Label>(
				Vec2i(200, 30),
				Vec2i(margin.x + 220, 20),
				std::wstring(std::wstring(L"Flags left: ") + std::to_wstring(game.flagsLeft)),
				&window,
				&cascadia
			);

			for (std::int32_t y = 0; y < minefieldSize.y; y++)
			{
				for (std::int32_t x = 0; x < minefieldSize.x; x++)
				{
					Button* field = minefieldScene->CreateControl<Button>(
						fieldSize,
						Vec2i(margin.x + x * fieldSize.x, margin.y + y * fieldSize.y),
						L"",
						&window,
						&cascadia
					);
					field->SetTag(std::to_string(y * minefieldSize.x + x));
				}
			}

			roundClock->AddHook(EventType::TimerClock, Hook("roundClock.Clock", [&](const std::any& param)
			{
				game.secondsLeft--;
				game.formattedTimeLeft = FormatTime(game.secondsLeft);

				// Capture wouldn't work here. Alternatively, just put the Timer* before the first lambda.
				minefieldScene->GetControlByTag("Time")->SetString(L"Time left: " + game.formattedTimeLeft);
			}));

			// Side menu
			Button* leaderboard = minefieldScene->CreateControl<Button>(Vec2i(150, 40), Vec2i(windowSize.x - 200, margin.y), L"Leaderboard", &window, &cascadia);
			Button* back = minefieldScene->CreateControl<Button>(Vec2i(150, 40), Vec2i(windowSize.x - 200, margin.y + 50), L"Back", &window, &cascadia);
			back->AddHook(EventType::Click, Hook("Back.Click", [&](const std::any& param)
			{
				roundClock->RemoveHook(EventType::TimerClock, "roundClock.Clock");
				DestroyTimer(roundClock);
				SwitchScene(difficultyScene);
			}));
		}));

		OpenScene(difficultyScene);

		g_Dispatcher.CallEvent(EventType::StartUp);
		MSG msg;
		while (GetMessageW(&msg, nullptr, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);

			g_Dispatcher.RemoveInvalidListeners();
			g_Dispatcher.AddValidListeners();
		}

		return EXIT_SUCCESS;
	}

	Scene* Application::CreateScene(const std::string& name)
	{
		Scene*& ref = m_Scenes.emplace_back(new Scene(name));
		if (!ref)
			MsgIfError("Unable to create a scene.");

		return ref;
	}

	Timer* Application::CreateTimer(std::int32_t delay)
	{
		return m_Timers.emplace_back(new Timer(delay, m_MainWindow.m_Handle));
	}

	void Application::DestroyTimer(Timer* ptr)
	{
		for (std::vector<Timer*>::iterator it = m_Timers.begin(); it != m_Timers.end(); it++)
		{
			if (*it == ptr)
			{
				m_Timers.erase(it);
				return;
			}
		}
	}

	void Application::OpenScene(Scene* scene)
	{
		g_Dispatcher.CallEventQualifier(EventType::SceneOpen, scene);
		m_CurrentScene = scene;
	}

	void Application::CloseScene(Scene* scene)
	{
		g_Dispatcher.CallEventQualifier(EventType::SceneClose, scene);
		m_CurrentScene = nullptr;
	}

	void Application::SwitchScene(Scene* scene)
	{
		CloseScene(m_CurrentScene);
		m_MainWindow.SetSize(Vec2i(MWR_WIDTH, MWR_HEIGHT));
		OpenScene(scene);
	}

	Scene::Scene(const std::string& name) : BaseClass(true),
		m_Name(name)
	{
		m_Listener.SetQualifier(this);

		AddHook(EventType::SceneClose, Hook("Scene.SceneClose", [&](const std::any& param)
		{
			for (auto& k : m_Controls)
			{
				delete k;
			}
			m_Controls.clear();
		}));
	}

	Scene::~Scene()
	{
		for (auto& k : m_Controls)
			delete k;
	}

	Control* Scene::GetControlByTag(const std::string& tag)
	{
		for (auto& k : m_Controls)
			if (k->GetTag() == tag)
				return k;
	}

}