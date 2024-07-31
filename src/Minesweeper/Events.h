//****************************************************************
// File: Events.h
// Purpose: Stores the entire event system (hooks, callbacks, etc).
// 
// Authors: The Kumor
//****************************************************************

#pragma once

#include <string>
#include <vector>
#include <any>
#include <functional>
#include <cstdint>
#include <unordered_map>

#include <windows.h>

#define MINES_NODATA nullptr
#define MINES_PIN_REC(rec) g_EventSource.PinReceiver(&rec)
#define MINES_PIN_THIS() g_EventSource.PinReceiver(&m_EventReceiver)

namespace mines
{

	typedef void* event_qualifier;

	enum class EventType : std::int32_t
	{
		Invalid = 0,
		Tick, Update, PreDraw, PostDraw,
		Timer, Command, Close, Resize
	};

	//----------------------------------------------------------
	// Contains a single std::any variable.
	//----------------------------------------------------------
	struct EventData
	{
		EventData(const std::any& val);
		EventData() = default;

		// Whatever you want the event to receive.
		std::any Value = MINES_NODATA;
	};

	using EventCallback = std::function<void(const EventData& data)>;

	//----------------------------------------------------------
	// A structure that describes a callback for an event.
	//----------------------------------------------------------
	struct Hook
	{
		Hook(const std::string& name, const EventCallback& callback);
		Hook() = default;

		// Unique identifier.
		std::string Name = "";

		// Function that's run upon the hook is called.
		EventCallback Callback = nullptr;
	};

	//----------------------------------------------------------
	// Contains hooks that are run once event is fired.
	//----------------------------------------------------------
	struct Event
	{
		Event(EventType type);
		Event() = default;

		EventType Type = EventType::Invalid;

		// All the hooks (and ultimately, functions) that are literally
		// 'hooked' to this event. Meaning they're called upon event is
		// run.
		std::vector<Hook> Hooks = {};
	};

	//----------------------------------------------------------
	// Base class for event-related classes.
	//----------------------------------------------------------
	class EventBase
	{
	public:
		EventBase() = default;
	};

	//----------------------------------------------------------
	// This class runs callbacks when the event source tells it to.
	//----------------------------------------------------------
	class EventReceiver : public EventBase
	{
	public:
		friend class EventSource;

		EventReceiver() = default;

		void FireEvent(EventType type, const std::any& eventData);
		void AddHook(EventType eventType, const std::string& hookName, const EventCallback& callback);
		void AddHook(EventType eventType, const Hook& hook);
		void SetQualifier(event_qualifier qualifier);

	private:
		event_qualifier m_Qualifier = nullptr;
		std::unordered_map<EventType, Event> m_Events = {};
	};

	using FragileEventRecPtr = EventReceiver*;

	//----------------------------------------------------------
	// Tells all the receivers inside it to run callbacks.
	//----------------------------------------------------------
	class EventSource : public EventBase
	{
	public:
		EventSource() = default;

		FragileEventRecPtr PinReceiver(EventReceiver* rec);
		void CallEvent(EventType type, const std::any& eventData);
		void CallEvent(EventType type, event_qualifier qualifier, const std::any& eventData);

	private:
		std::vector<FragileEventRecPtr> m_Receivers = {};
	};

	//----------------------------------------------------------
	// Class for others that need a source-receiver system.
	//----------------------------------------------------------
	class EventManager : public EventReceiver, public EventSource
	{
	public:
		EventManager() = default;
	};

	//----------------------------------------------------------
	// Class for others that need a source-receiver system.
	//----------------------------------------------------------
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

// The Kumor