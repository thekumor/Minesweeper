#pragma once

// STL
#include <string>
#include <functional>
#include <unordered_map>
#include <vector>
#include <any>
#include <memory>

// Minesweeper
#include <minesweeper/utility.h>

#define MWR_NODATA 0
#define MWR_COMPLEX_EVENT_SYSTEM 1

namespace mwr
{

#if MWR_COMPLEX_EVENT_SYSTEM
	enum EventType : std::uint32_t
	{
		Invalid = 0,
		Think,
		Resize,
		Close,
		StartUp,
		Click,
		TextEntered,
		SceneOpen,
		SceneClose,
		TimerClock,
		RightClick,
		FontsUpdated,
		ControlDestroyed,
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
		~EventListener();

		std::string GetTag() const;
		void* GetQualifier();
		void OnCallEvent(EventType type, const std::any& data);
		void AddHook(EventType eventType, const Hook& hook);
		void RemoveHook(EventType eventType, const std::string& name);
		void RemoveAllHooks(EventType eventType);
		void SetQualifier(void* qualifier);
		void SetTag(const std::string& tag);

	private:
		std::unordered_map<EventType, std::vector<Hook>> m_Hooks;
		std::string m_Tag;
		void* m_Qualifier;
	};

	class EventDispatcher
	{
	public:
		EventDispatcher() = default;

		void AddListener(EventListener* listener);
		void AddListenerForce(EventListener* listener);
		void RemoveListener(EventListener* listener);
		void RemoveListenerForce(EventListener* listener);
		void CallEvent(EventType type, const std::any& data = MWR_NODATA);
		void CallEventQualifier(EventType type, void* qualifier, const std::any& data = MWR_NODATA);
		void RemoveInvalidListeners();
		void AddValidListeners();

	private:
		std::vector<Handle<EventListener>> m_Listeners;
		std::vector<Handle<EventListener>> m_WaitingListeners;
	};

	class EventActive
	{
	public:
		EventActive() = default;

		EventDispatcher& GetDispatcher();
		EventListener& GetListener();

		void AddHook(EventType eventType, const Hook& hook);
		void RemoveHook(EventType eventType, const std::string& name);
		void RemoveAllHooks(EventType eventType);

	protected:
		EventDispatcher m_Dispatcher;
		EventListener m_Listener;
	};

#endif
}