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

	static std::vector<std::int32_t> RandomNoRepetitions(std::int32_t amount, std::int32_t minimum, std::int32_t maximum)
	{
		std::vector<std::int32_t> values(amount);

		for (std::int32_t i = 0; i < amount; i++)
		{
			std::int32_t value = minimum + rand() % (maximum + 1 - minimum);
			bool existed = false;

			for (std::int32_t j = 0; j < i; j++)
			{
				if (values[j] == value)
				{
					i--;
					existed = true;
					break;
				}
			}
			if (!existed)
				values[i] = value;
		}

		return values;
	}

	static bool FieldHasFlag(Control* field)
	{
		return field->GetTag()[1] == '1';
	}

	static bool FieldHasBomb(Control* field)
	{
		return field->GetTag()[0] == '1';
	}

	static void FieldSetHasFlag(Control* field, bool has)
	{
		std::string newTag = field->GetTag();
		newTag[1] = has ? '1' : '0';
		field->SetTag(newTag);
	}

	static void FieldSetHasBomb(Control* field, bool has)
	{
		std::string newTag = field->GetTag();
		newTag[0] = has ? '1' : '0';
		field->SetTag(newTag);
	}

	static struct FieldNeighbors
	{
		std::int32_t up, down, left, right, leftUp, leftDown, rightUp, rightDown;
	};

	static FieldNeighbors GetNeighbors(std::shared_ptr<std::vector<Button*>> fields, const Vec2i& minefieldSize, std::int32_t id)
	{
		const std::int32_t minefieldCount = fields->size();

		std::int32_t up = (id >= minefieldSize.x) ? (id - minefieldSize.x) : (-1);
		std::int32_t down = (id < minefieldCount - minefieldSize.x) ? (id + minefieldSize.x) : (-1);
		std::int32_t left = (id % minefieldSize.x != 0) ? (id - 1) : (-1);
		std::int32_t right = ((id + 1) % minefieldSize.x != 0) ? (id + 1) : (-1);
		std::int32_t leftUp = (left != -1 && up != -1) ? (id - minefieldSize.x - 1) : (-1);
		std::int32_t leftDown = (left != -1 && down != -1) ? (id + minefieldSize.x - 1) : (-1);
		std::int32_t rightUp = (right != -1 && up != -1) ? (id - minefieldSize.x + 1) : (-1);
		std::int32_t rightDown = (right != -1 && down != -1) ? (id + minefieldSize.x + 1) : (-1);

		FieldNeighbors neighbors;
		neighbors.up = up;
		neighbors.down = down;
		neighbors.left = left;
		neighbors.right = right;
		neighbors.leftUp = leftUp;
		neighbors.leftDown = leftDown;
		neighbors.rightUp = rightUp;
		neighbors.rightDown = rightDown;

		return neighbors;
	}

	static std::vector<std::pair<std::int32_t, Button*>> GetFieldsWithinRadius(std::shared_ptr<std::vector<Button*>> fields, const Vec2i& minefieldSize, std::int32_t o, float radius)
	{
		std::vector<std::pair<std::int32_t, Button*>> buttons;
		std::int32_t xO = o % minefieldSize.x;
		std::int32_t yO = o / minefieldSize.x;

		for (std::int32_t i = 0; i < fields->size(); i++)
		{
			std::int32_t x = i % minefieldSize.x;
			std::int32_t y = i / minefieldSize.x;

			float distance = sqrt(pow(xO - x, 2) + pow(yO - y, 2));

			if (distance <= radius)
				buttons.push_back(std::pair<std::int32_t, Button*>(i, fields->at(i)));
		}

		return buttons;
	}

	int Application::Run()
	{
		Window& window = m_MainWindow;
		Font cascadia(L"Cascadia Code", 24, FontStyle::Normal);
		Font large(L"Georgia", 64, FontStyle::Bold);
		Font smol(L"Arial", 16);
		Font webdings(L"Webdings", 24);
		Font wingdings(L"Wingdings", 24);

		struct Specification
		{
			Vec2i minefieldSize;
			std::int32_t time, totalBombs, totalFlags;
			float sweepForce;
		};

		Specification easySpec;
		easySpec.minefieldSize = { 10, 10 };
		easySpec.time = 4.5 * 60;
		easySpec.totalBombs = 3;
		easySpec.totalFlags = 5;
		easySpec.sweepForce = 2.0f;

		Specification normalSpec;
		normalSpec.minefieldSize = { 15, 15 };
		normalSpec.time = 4 * 60;
		normalSpec.totalBombs = 12;
		normalSpec.totalFlags = 14;
		normalSpec.sweepForce = 3.0f;

		Specification hardSpec;
		hardSpec.minefieldSize = { 20, 20 };
		hardSpec.time = 3.5 * 60;
		hardSpec.totalBombs = 28;
		hardSpec.totalFlags = 30;
		hardSpec.sweepForce = 3.0f;

		Specification hellSpec;
		hellSpec.minefieldSize = { 35, 25 };
		hellSpec.time = 3 * 60;
		hellSpec.totalBombs = 64;
		hellSpec.totalFlags = 64;
		hellSpec.sweepForce = 2.0f;

		Specification* currentSpec = nullptr;

		Scene* difficultyScene = CreateScene("Difficulty Scene");
		Scene* minefieldScene = CreateScene("Minefield Scene");
		Scene* loseScene = CreateScene("Lose Scene");
		Scene* winScene = CreateScene("Win Scene");

		difficultyScene->AddHook(EventType::SceneOpen, Hook("Scene.Open", [&](const std::any& param)
		{
			Label* title = difficultyScene->CreateControl<Label>(Vec2i(400, 67), Vec2i(150, 30), L"Minesweeper", &window, &large);
			Button* easy = difficultyScene->CreateControl<Button>(Vec2i(200, 60), Vec2i(250, 120), L"Easy", &window, &cascadia);
			Button* normal = difficultyScene->CreateControl<Button>(Vec2i(200, 60), Vec2i(250, 200), L"Normal", &window, &cascadia);
			Button* hard = difficultyScene->CreateControl<Button>(Vec2i(200, 60), Vec2i(250, 280), L"Hard", &window, &cascadia);
			Button* hell = difficultyScene->CreateControl<Button>(Vec2i(200, 60), Vec2i(250, 360), L"Hell", &window, &cascadia);
			Button* leaderboard = difficultyScene->CreateControl<Button>(Vec2i(200, 60), Vec2i(250, 440), L"High Scores", &window, &cascadia);
			Label* author = difficultyScene->CreateControl<Label>(Vec2i(130, 20), Vec2i(520, 625), L"by The Kumor, (2025)", &window, &smol);

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
			const std::int32_t minefieldCount = minefieldSize.x * minefieldSize.y;

			Vec2i windowSize = minefieldSize * fieldSize + margin + Vec2i(250, 100);
			window.SetSize(windowSize);

			Button* back = minefieldScene->CreateControl<Button>(Vec2i(150, 40), Vec2i(windowSize.x - 200, margin.y), L"Back", &window, &cascadia);
			back->AddHook(EventType::Click, Hook("back.Click", [&](const std::any& param)
			{
				DestroyTimer(roundClock);
				SwitchScene(difficultyScene);
			}));

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

			// Randomize field indexes that would contain a bomb.
			std::vector<std::int32_t> bombIndexes = RandomNoRepetitions(currentSpec->totalBombs, 0, minefieldCount - 1);

			// This is std::shared_ptr so that lambdas don't store an expired copy.
			std::shared_ptr<std::vector<Button*>> fields(new std::vector<Button*>);
			std::shared_ptr<std::vector<std::int32_t>> adjacentBombs(new std::vector<std::int32_t>(minefieldCount));
			fields->reserve(minefieldCount);

			for (std::int32_t i = 0; i < minefieldCount; i++)
			{
				std::int32_t x = i % minefieldSize.x;
				std::int32_t y = i / minefieldSize.x;

				bool containsBomb = false;
				for (std::int32_t j = 0; j < currentSpec->totalBombs; j++)
					if (bombIndexes[j] == i)
					{
						containsBomb = true;
						break;
					}

				Button* field = minefieldScene->CreateControl<Button>(
					fieldSize,
					Vec2i(margin.x + x * fieldSize.x, margin.y + y * fieldSize.y),
					//(containsBomb) ? L"M" : L"",
					L"",
					&window,
					(containsBomb) ? &wingdings : &cascadia
				);

				// Tag goes: bomb;flag
				field->SetTag("xx");
				FieldSetHasBomb(field, containsBomb);
				FieldSetHasFlag(field, false);

				field->AddHook(EventType::Click, Hook("field.Click", [=, &wingdings, &cascadia](const std::any& param)
				{
					if (FieldHasBomb(field))
					{
						back->RemoveHook(EventType::Click, "back.Click");
						DestroyTimer(roundClock);

						for (std::int32_t j : bombIndexes)
						{
							fields->at(j)->SetFont(&wingdings);
							fields->at(j)->SetString(L"M");
						}

						Timer* delay = CreateTimer(5000);
						delay->AddHook(EventType::TimerClock, Hook("delay.TimerClock", [=](const std::any& param)
						{
							SwitchScene(loseScene);
							DestroyTimer(delay);
						}));
					}
					else
					{
						std::vector<std::pair<std::int32_t, Button*>> fieldsWithinRadius = GetFieldsWithinRadius(fields, minefieldSize, i, currentSpec->sweepForce);

						for (auto[id, btn] : fieldsWithinRadius)
						{
							if (FieldHasBomb(btn)) continue;

							if (adjacentBombs->at(id) != 0)
							{
								btn->SetFont(&cascadia);
								btn->SetString(std::to_wstring(adjacentBombs->at(id)));
								btn->SetDisabled(true);
							}
							else
								btn->SetPosition(Vec2i(-100, -100));
						}
					}
				}));

				field->AddHook(EventType::RightClick, Hook("field.RightClick", [=, &game, &cascadia, &wingdings](const std::any& param)
				{
					// Already has a flag - remove it.
					if (FieldHasFlag(field))
					{
						game.flagsLeft++;
						FieldSetHasFlag(field, false);
						field->SetFont(&cascadia);
						field->SetString(L"");
					}
					// Has no flag - place it.
					else
					{
						if (game.flagsLeft <= 0) return;

						game.flagsLeft--;
						FieldSetHasFlag(field, true);
						field->SetFont(&wingdings);
						field->SetString(L"P");

						// Check if player wins by flagging all mines.
						std::int32_t flaggedMines = 0;
						for (std::int32_t j : bombIndexes)
						{
							if (FieldHasFlag(fields->at(j)))
								flaggedMines++;
						}
						if (flaggedMines == currentSpec->totalBombs)
						{
							DestroyTimer(roundClock);
							SwitchScene(winScene);
							return;
						}
					}

					// Update the flag counter.
					flags->SetString(std::wstring(std::wstring(L"Flags left: ") + std::to_wstring(game.flagsLeft)));
				}));

				fields->push_back(field);
			}

			for (std::int32_t i = 0; i < currentSpec->totalBombs; i++)
			{
				std::int32_t bombIndex = bombIndexes[i];

				FieldNeighbors neighbors = GetNeighbors(fields, minefieldSize, bombIndex);

				if (neighbors.up != -1) adjacentBombs->at(neighbors.up)++;
				if (neighbors.down != -1) adjacentBombs->at(neighbors.down)++;
				if (neighbors.left != -1) adjacentBombs->at(neighbors.left)++;
				if (neighbors.right != -1) adjacentBombs->at(neighbors.right)++;
				if (neighbors.leftUp != -1) adjacentBombs->at(neighbors.leftUp)++;
				if (neighbors.leftDown != -1) adjacentBombs->at(neighbors.leftDown)++;
				if (neighbors.rightUp != -1) adjacentBombs->at(neighbors.rightUp)++;
				if (neighbors.rightDown != -1) adjacentBombs->at(neighbors.rightDown)++;
			}

			roundClock->AddHook(EventType::TimerClock, Hook("roundClock.TimerClock", [=, &game](const std::any& param)
			{
				game.secondsLeft--;
				game.formattedTimeLeft = FormatTime(game.secondsLeft);

				if (game.secondsLeft == -1)
				{
					SwitchScene(loseScene);
					DestroyTimer(roundClock);
					return;
				}

				time->SetString(L"Time left: " + game.formattedTimeLeft);
			}));
		}));

		loseScene->AddHook(EventType::SceneOpen, Hook("Scene.Open", [&](const std::any& param)
		{
			Label* title = loseScene->CreateControl<Label>(Vec2i(280, 67), Vec2i(200, 30), L"You lost!", &window, &large);
			Button* back = loseScene->CreateControl<Button>(Vec2i(200, 60), Vec2i(250, 200), L"Return to menu", &window, &cascadia);
			back->AddHook(EventType::Click, Hook("Back.Click", [&](const std::any& param)
			{
				SwitchScene(difficultyScene);
			}));
		}));

		winScene->AddHook(EventType::SceneOpen, Hook("Scene.Open", [&](const std::any& param)
		{
			Label* title = winScene->CreateControl<Label>(Vec2i(280, 67), Vec2i(200, 30), L"You won!", &window, &large);
			Button* back = winScene->CreateControl<Button>(Vec2i(200, 60), Vec2i(250, 200), L"Return to menu", &window, &cascadia);
			back->AddHook(EventType::Click, Hook("Back.Click", [&](const std::any& param)
			{
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
				ptr->RemoveAllHooks(EventType::TimerClock); //TODO: remove this
				m_Timers.erase(it);
				delete ptr;
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
		m_Listener.SetTag("Scene");

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

#ifdef _DEBUG
static std::int64_t s_memoryUse;
void* operator new(size_t size)
{
	void* address = malloc(size);
	s_memoryUse += size;

	return address;
}

void operator delete(void* ptr, size_t size)
{
	s_memoryUse -= size;

	free(ptr);
}
#endif