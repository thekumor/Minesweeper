#pragma once

#include <string>
#include <vector>
#include <any>
#include <functional>
#include <cstdint>
#include <unordered_map>

#define MINES_NODATA std::any(std::uint32_t(0))

namespace mines
{

	enum class EventType : std::int32_t
	{
		Invalid = 0,
		Tick, Update, PreDraw, PostDraw,
		Timer, Command, Close
	};

	struct EventData
	{
		EventData(const std::any& val);
		EventData() = default;

		std::any Value = MINES_NODATA;
	};

	using EventCallback = std::function<void(const EventData& data)>;

	struct Hook
	{
		Hook(const std::string& name, const EventCallback& callback);
		Hook() = default;

		std::string Name = "";
		EventCallback Callback = nullptr;
	};

	struct Event
	{
		Event(EventType type);
		Event() = default;

		EventType Type = EventType::Invalid;
		std::vector<Hook> Hooks = {};
	};

	class EventBase
	{
	public:
		EventBase() = default;
	};

	class EventReceiver : public EventBase
	{
	public:
		EventReceiver() = default;

		void FireEvent(EventType type, const std::any& eventData);
		void AddHook(EventType eventType, const std::string& hookName, const EventCallback& callback);
		void AddHook(EventType eventType, const Hook& hook);

	private:
		std::unordered_map<EventType, Event> m_Events = {};
	};

	using FragileEventRecPtr = EventReceiver*;

	class EventSource : public EventBase
	{
	public:
		EventSource() = default;

		FragileEventRecPtr PinReceiver(EventReceiver* rec);
		void CallEvent(EventType type, const std::any& eventData);

	private:
		std::vector<FragileEventRecPtr> m_Receivers = {};
	};

	class EventManager : public EventReceiver, public EventSource
	{
	public:
		EventManager() = default;
	};

	class EventActive : public EventBase
	{
	public:
		EventActive() = default;

		EventSource& GetEventSource();
		EventReceiver& GetEventReceiver();

	protected:
		EventSource m_EventSource;
		EventReceiver m_EventReceiver;
	};

}