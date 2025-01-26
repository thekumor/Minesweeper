//********************************************************************************************
// File: Events.h
// Purpose: Stores the entire event system (hooks, callbacks, etc).
// 
// Authors: The Kumor
//********************************************************************************************

#pragma once

// STL
#include <string>
#include <vector>
#include <any>
#include <functional>
#include <cstdint>
#include <unordered_map>

// WinAPI
#include <windows.h>

#define MINES_NODATA nullptr
#define MINES_PIN_REC(rec) g_EventSource.PinReceiver(&rec)
#define MINES_PIN_THIS() g_EventSource.PinReceiver(&m_EventReceiver)

namespace mines
{

	class EventSource;
	extern EventSource g_EventSource;

	typedef void* event_qualifier;

	enum class EventType : std::int32_t
	{
		Invalid = 0, Tick, Update, PreDraw, PostDraw, Timer, Command, Close, Resize, Destroy
	};

	//------------------------------------------------------------------------------------
	// Contains a single std::any variable.
	//------------------------------------------------------------------------------------
	struct EventData
	{
		EventData(const std::any& val);
		EventData() = default;

		// Whatever you want the event to receive.
		std::any Value = MINES_NODATA;
	};

	using EventCallback = std::function<void(const EventData& data)>;

	//------------------------------------------------------------------------------------
	// A structure that describes a callback for an event.
	//------------------------------------------------------------------------------------
	struct Hook
	{
		Hook(const std::string& name, const EventCallback& callback);
		Hook() = default;

		// Unique identifier.
		std::string Name;

		// Function that's run upon the hook is called.
		EventCallback Callback = nullptr;
	};

	//------------------------------------------------------------------------------------
	// Contains hooks that are run once event is fired.
	//------------------------------------------------------------------------------------
	struct Event
	{
		Event(EventType type);
		Event() = default;

		EventType Type = EventType::Invalid;

		// All the hooks (and ultimately, functions) that are literally 'hooked' to this event. Meaning they're called
		// upon event is run.
		std::vector<Hook> Hooks;
	};

	//------------------------------------------------------------------------------------
	// Base class for event-related classes.
	//------------------------------------------------------------------------------------
	class EventBase
	{
	public:
		EventBase() = default;
	};

	//------------------------------------------------------------------------------------
	// This class runs callbacks when the event source tells it to.
	//------------------------------------------------------------------------------------
	class EventReceiver : public EventBase
	{
	public:
		friend class EventSource;

		EventReceiver() = default;

		// Runs a particular event on this receiver.
		void FireEvent(EventType type, const std::any& eventData);

		// Adds a callback function to event.
		void AddHook(EventType eventType, const std::string& hookName, const EventCallback& callback);

		// Adds a callback function to event.
		void AddHook(EventType eventType, const Hook& hook);

		// Replaces a hook under given event that has a specified name.
		void ReplaceHook(EventType eventType, const Hook& hook);

		// Sets it's object handle to particular address. This is done because some events are only run on a particular receiver.
		// Example of it's use would be a button click.
		void SetQualifier(event_qualifier qualifier);

	private:
		event_qualifier m_Qualifier = nullptr;
		std::unordered_map<EventType, Event> m_Events;
	};

	//------------------------------------------------------------------------------------
	// Tells all the receivers inside it to run callbacks.
	//------------------------------------------------------------------------------------
	class EventSource : public EventBase
	{
	public:
		EventSource() = default;

		// Adds a receiver to this source and returns it as a pointer from within vector of receivers.
		EventReceiver* PinReceiver(EventReceiver* rec);

		// Runs a particular event on all of it's receivers.
		void CallEvent(EventType type, const std::any& eventData = MINES_NODATA);

		// Runs a particular event on particular receivers (usually one). Example of it's use would be a button click.
		void CallEvent(EventType type, event_qualifier qualifier, const std::any& eventData);

		// Detaches given receiver.
		void UnpinReceiver(EventReceiver* m_EventReceiver);

	private:
		std::vector<EventReceiver*> m_Receivers;
	};

	//------------------------------------------------------------------------------------
	// Class for others that need a source-receiver system.
	//------------------------------------------------------------------------------------
	class EventManager : public EventReceiver, public EventSource
	{
	public:
		EventManager() = default;
	};

	//------------------------------------------------------------------------------------
	// Class for others that need a source-receiver system.
	//------------------------------------------------------------------------------------
	class EventActive : public EventBase
	{
	public:
		EventActive();
		~EventActive();

		EventSource& GetEventSource();
		EventReceiver& GetEventReceiver();

	protected:
		EventSource m_EventSource;
		EventReceiver m_EventReceiver;
	};

}

// The Kumor