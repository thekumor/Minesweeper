#include "application.h"

namespace mwr
{

	Application::Application(HINSTANCE instance, const Vec2i& size, const std::wstring& title)
		: m_MainWindow(instance, size, title), m_Instance(instance)
	{
	}

	Application::~Application()
	{
		for (auto& k : m_Scenes)
			delete k;
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
		easySpec.minefieldSize = { 6, 6 };
		easySpec.time = 5 * 60;
		easySpec.totalBombs = 4;
		easySpec.totalFlags = 10;

		Specification normalSpec;
		normalSpec.minefieldSize = { 7, 7 };
		normalSpec.time = 4 * 60;
		normalSpec.totalBombs = 6;
		normalSpec.totalFlags = 8;

		Specification hardSpec;
		hardSpec.minefieldSize = { 8, 8 };
		hardSpec.time = 2 * 60;
		hardSpec.totalBombs = 8;
		hardSpec.totalFlags = 6;

		Specification hellSpec;
		hellSpec.minefieldSize = { 9, 9 };
		hellSpec.time = 1 * 60;
		hellSpec.totalBombs = 20;
		hellSpec.totalFlags = 4;

		Specification* currentSpec = nullptr;

		Scene* difficultyScene = CreateScene("Difficulty Scene");
		//Scene* minefieldScene = CreateScene("Minefield Scene");

		difficultyScene->GetListener().AddHook(EventType::SceneOpen, Hook("Scene.Open", [&](const std::any& param)
		{
			Label* title = difficultyScene->CreateControl<Label>(Vec2i(400, 60), Vec2i(150, 30), L"Minesweeper", &window, &large);
			Button* easy = difficultyScene->CreateControl<Button>(Vec2i(200, 60), Vec2i(250, 120), L"Easy", &window, &cascadia);
			Button* normal = difficultyScene->CreateControl<Button>(Vec2i(200, 60), Vec2i(250, 200), L"Normal", &window, &cascadia);
			Button* hard = difficultyScene->CreateControl<Button>(Vec2i(200, 60), Vec2i(250, 280), L"Hard", &window, &cascadia);
			Button* hell = difficultyScene->CreateControl<Button>(Vec2i(200, 60), Vec2i(250, 360), L"Hell", &window, &cascadia);
			Label* author = difficultyScene->CreateControl<Label>(Vec2i(130, 25), Vec2i(520, 625), L"by The Kumor, (2025)", &window, &smol);

			easy->GetListener().AddHook(EventType::Click, Hook("Easy.Click", [&](const std::any& param)
			{
				currentSpec = &easySpec;
				//SwitchScene(minefieldScene);
			}));

			normal->GetListener().AddHook(EventType::Click, Hook("Normal.Click", [&](const std::any& param)
			{
				currentSpec = &normalSpec;
				//SwitchScene(minefieldScene);
			}));

			hard->GetListener().AddHook(EventType::Click, Hook("Hard.Click", [&](const std::any& param)
			{
				currentSpec = &hardSpec;
				//SwitchScene(minefieldScene);
			}));

			hell->GetListener().AddHook(EventType::Click, Hook("Hell.Click", [&](const std::any& param)
			{
				currentSpec = &hellSpec;
				//SwitchScene(minefieldScene);
			}));
		}));

		OpenScene(difficultyScene);

		g_Dispatcher.CallEvent(EventType::StartUp);
		MSG msg;
		while (GetMessageW(&msg, nullptr, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}

		return EXIT_SUCCESS;
	}

	Scene* Application::CreateScene(const std::string& name)
	{
		Scene* newScene = new Scene(name);
		if (!newScene)
			MsgIfError("Unable to create a scene.");

		m_Scenes.push_back(newScene);

		return newScene;
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
		OpenScene(scene);
	}

	Scene::Scene(const std::string& name)
		: m_Name(name)
	{
		g_Dispatcher.AddListener(&m_Listener);
		m_Listener.SetQualifier(this);
	}

	Scene::~Scene()
	{
		for (auto& k : m_Controls)
			delete k;
	}

}