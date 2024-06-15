#include "Window.h"

namespace mines
{

	Window::Window(const Vector2& size, const std::wstring& title)
		: Entity(title, size, { CW_USEDEFAULT, CW_USEDEFAULT }, nullptr)
	{
		HINSTANCE instance = reinterpret_cast<HINSTANCE>(GetModuleHandle(nullptr));
		const std::wstring className = L"Minesweeper Window";

		m_Class.hInstance = instance;
		m_Class.lpszClassName = className.c_str();
		m_Class.cbClsExtra = 0;
		m_Class.lpfnWndProc = reinterpret_cast<WNDPROC>(s_Procedure);
		m_Class.hCursor = LoadCursor(nullptr, IDC_ARROW);
		RegisterClass(&m_Class);
		CheckErrors("Window.RegisterClass");

		m_Handle = CreateWindow(
			className.c_str(),
			title.c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			size.x,
			size.y,
			nullptr,
			nullptr,
			instance,
			0
		);
		CheckErrors("Window.m_Handle");

		ShowWindow(m_Handle, SW_SHOW);
	}

	LRESULT CALLBACK Window::s_Procedure(HWND handle, UINT msg, WPARAM wp, LPARAM lp)
	{
		switch (msg)
		{
			case WM_CLOSE:
			{
				g_EventSource.CallEvent(EventType::Close, MINES_NODATA);
				PostQuitMessage(0);
			} break;

			case WM_PAINT:
			{
				g_EventSource.CallEvent(EventType::PreDraw, MINES_NODATA);

				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(handle, &ps);
				FillRect(hdc, &ps.rcPaint, reinterpret_cast<HBRUSH>(COLOR_WINDOW + 5));
				EndPaint(handle, &ps);

				g_EventSource.CallEvent(EventType::PostDraw, MINES_NODATA);
			} break;
		}

		return DefWindowProc(handle, msg, wp, lp);
	}

	bool Window::s_DrawBitmap(HDC winDC, const std::wstring& path)
	{
		HBITMAP handleBitmap = static_cast<HBITMAP>(LoadImage(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		CheckErrors("LoadImage");

		if (!handleBitmap)
		{
			MakeError("Cannot load a bitmap");
			return false;
		}

		BITMAP qBitmap = { 0 };
		if (!GetObject(reinterpret_cast<HGDIOBJ>(handleBitmap), sizeof(BITMAP), reinterpret_cast<LPVOID>(&qBitmap)))
		{
			MakeError("Cannot make a bitmap");
			return false;
		}

		HDC hdc = CreateCompatibleDC(winDC);
		CheckErrors("CreateCompatibleDC");

		SelectObject(hdc, handleBitmap);
		BitBlt(winDC, 0, 0, qBitmap.bmWidth, qBitmap.bmHeight, hdc, 0, 0, SRCCOPY);
		CheckErrors("BitBlt");

		SelectObject(hdc, winDC);
		DeleteDC(hdc);
		DeleteObject(handleBitmap);

		return true;
	}

	std::optional<std::shared_ptr<Scene>> Window::GetSceneByName(const std::string& name)
	{
		for (auto& ptr : m_Scenes)
			if (ptr->GetName() == name)
				return ptr;

		return {};
	}

	std::shared_ptr<Scene> Window::CreateScene(const std::string& name)
	{
		return m_Scenes.emplace_back(std::make_shared<Scene>(name));
	}

	Scene::Scene(const std::string& name)
		: m_Name(name)
	{
	}

	const std::string& Scene::GetName() const
	{
		return m_Name;
	}

	void Scene::Clear()
	{
		for (auto& k : m_Entities)
			k->Close();
	}

	void Scene::Switch(bool on)
	{
		m_Switched = on;

		if (m_Switched)
			for (auto& k : m_Entities)
				k->Show();
		else
			for (auto& k : m_Entities)
				k->Hide();
	}

}