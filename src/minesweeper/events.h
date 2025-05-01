#pragma once

// STL
#include <string>
#include <functional>
#include <unordered_map>
#include <vector>
#include <any>
#include <memory>

#define MWR_NODATA 0

namespace mwr
{

	enum EventType : std::uint32_t
	{
		Invalid = 0,
		Think,
		Resize,
		Close,
		StartUp,
		Click,
		SceneOpen,
		SceneClose
	};

	using EventCallback = std::function<void(const std::any&)>;

	struct Hook
	{
		Hook(const std::string& name, EventCallback callback);
		Hook() = default;

		std::string Name;
		EventCallback Callback;
	};

	class EventListener
	{
	public:
		EventListener() = default;

		void* GetQualifier();
		void OnCallEvent(EventType type, const std::any& data);
		void AddHook(EventType eventType, const Hook& hook);
		void SetQualifier(void* qualifier);

	private:
		std::unordered_map<EventType, std::vector<Hook>> m_Hooks;
		void* m_Qualifier;
	};

	class EventDispatcher
	{
	public:
		EventDispatcher() = default;

		void AddListener(EventListener* listener);
		void RemoveListener(EventListener* listener);
		void CallEvent(EventType type, const std::any& data = MWR_NODATA);
		void CallEventQualifier(EventType type, void* qualifier, const std::any& data = MWR_NODATA);

	private:
		std::vector<EventListener*> m_Listeners;
	};

	class EventActive
	{
	public:
		EventActive() = default;

		EventDispatcher& GetDispatcher();
		EventListener& GetListener();

	protected:
		EventDispatcher m_Dispatcher;
		EventListener m_Listener;
	};

}