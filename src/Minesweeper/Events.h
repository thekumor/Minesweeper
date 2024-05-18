#pragma once

#include <string>
#include <vector>
#include <any>
#include <functional>
#include <cstdint>
#include <unordered_map>

#define MINES_NODATA std::any(std::uint32_t(0))
#define MINES_PIN_REC(rec) g_EventSource.PinReceiver(&rec)
#define MINES_PIN_THIS() g_EventSource.PinReceiver(&m_EventReceiver)

namespace mines
{

	enum class EventType : std::int32_t
	{
		Invalid = 0,
		Tick, Update, PreDraw, PostDraw,
		Timer, Command, Close
	};

	//
	// Contains a single std::any variable.
	//
	struct EventData
	{
		EventData(const std::any& val);
		EventData() = default;

		std::any Value = MINES_NODATA;
	};

	using EventCallback = std::function<void(const EventData& data)>;

	//
	// A structure that describes a callback for an event.
	//
	struct Hook
	{
		Hook(const std::string& name, const EventCallback& callback);
		Hook() = default;

		std::string Name = "";
		EventCallback Callback = nullptr;
	};

	//
	// Contains hooks that are run once event is fired.
	//
	struct Event
	{
		Event(EventType type);
		Event() = default;

		EventType Type = EventType::Invalid;
		std::vector<Hook> Hooks = {};
	};

	//
	// Base class for event-related classes.
	//
	class EventBase
	{
	public:
		EventBase() = default;
	};

	//
	// This class runs callbacks when the event source tells it to.
	//
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

	//
	// Tells all the receivers inside it to run callbacks.
	//
	class EventSource : public EventBase
	{
	public:
		EventSource() = default;

		FragileEventRecPtr PinReceiver(EventReceiver* rec);
		void CallEvent(EventType type, const std::any& eventData);

	private:
		std::vector<FragileEventRecPtr> m_Receivers = {};
	};

	//
	// Class for others that need a source-receiver system.
	//
	class EventManager : public EventReceiver, public EventSource
	{
	public:
		EventManager() = default;
	};

	//
	// Class for others that need a source-receiver system.
	//
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