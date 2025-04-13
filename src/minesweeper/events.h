#pragma once

// STL
#include <string>
#include <functional>
#include <unordered_map>
#include <vector>
#include <memory>

namespace mwr
{

	using EventCallback = std::function<void(void*)>;

	struct Hook
	{
		Hook(const std::string& name, EventCallback callback);
		Hook() = default;

		std::string Name;
		EventCallback Callback;
	};

	struct Event
	{
		Event(const std::string& name, const std::vector<Hook>& hooks = {});
		Event() = default;

		std::string Name;
		std::vector<Hook> Hooks;
	};

	class EventListener
	{
	public:
		EventListener() = default;

	private:
		std::unordered_map<Event, std::vector<Hook>> hooks;
	};

	class EventDispatcher
	{
	public:
		EventDispatcher() = default;

		void AddListener(std::shared_ptr<EventListener> listener);
		void RemoveListener(std::shared_ptr<EventListener> listener);

	private:
		std::vector<std::shared_ptr<EventListener>> m_Listeners;
	};

}