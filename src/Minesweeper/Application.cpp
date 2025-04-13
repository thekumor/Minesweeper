#include "application.h"

namespace mwr
{

	Application::Application(HINSTANCE instance, const Vec2i& size, const std::wstring& title)
		: m_MainWindow(instance, size, title), m_Instance(instance)
	{
	}

	Application::~Application()
	{
		for (auto& k : m_Controls)
			delete k;
	}

	int Application::Run()
	{
		Font arial(L"Cascadia Code", 24);
		Button* hello = CreateControl<Button>({ 100, 30 }, MWR_VEC0 + Vec2i(50, 0), L"Hello!", nullptr, &arial);

		MSG msg;
		while (GetMessageW(&msg, nullptr, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}

		return EXIT_SUCCESS;
	}

}