#include "Events.h"

namespace mines
{

	EventData::EventData(const std::any& val)
		: Value(val)
	{
	}

	Hook::Hook(const std::string& name, const EventCallback& callback)
		: Name(name), Callback(callback)
	{
	}

	Event::Event(EventType type)
		: Type(type)
	{
	}

	void EventReceiver::FireEvent(EventType type, const std::any& eventData)
	{
		if (m_Events.find(type) != m_Events.end())
			for (auto& ev : m_Events[type].Hooks)
				ev.Callback(eventData);
	}

	void EventReceiver::AddHook(EventType eventType, const std::string& hookName, const EventCallback& callback)
	{
		m_Events[eventType].Hooks.emplace_back(Hook(hookName, callback));
	}

	void EventReceiver::AddHook(EventType eventType, const Hook& hook)
	{
		m_Events[eventType].Hooks.emplace_back(hook);
	}

	FragileEventRecPtr EventSource::PinReceiver(EventReceiver* rec)
	{
		return m_Receivers.emplace_back(rec);
	}

	void EventSource::CallEvent(EventType type, const std::any& eventData)
	{
		for (auto& rec : m_Receivers)
			rec->FireEvent(type, eventData);
	}

	mines::EventSource& EventActive::GetEventSource()
	{
		return m_EventSource;
	}

	mines::EventReceiver& EventActive::GetEventReceiver()
	{
		return m_EventReceiver;
	}

}