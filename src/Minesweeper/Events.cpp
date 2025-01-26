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

	void EventReceiver::SetQualifier(event_qualifier qualifier)
	{
		m_Qualifier = qualifier;
	}

	void EventReceiver::ReplaceHook(EventType eventType, const Hook& hook)
	{
		std::vector<Hook>& hooks = m_Events[eventType].Hooks;

		for (std::vector<Hook>::iterator it = hooks.begin(); it != hooks.end(); it++)
		{
			if (it->Name == hook.Name)
			{
				it->Callback = hook.Callback;
				return;
			}
		}
		AddHook(eventType, hook);
	}

	EventReceiver* EventSource::PinReceiver(EventReceiver* rec)
	{
		return m_Receivers.emplace_back(rec);
	}

	void EventSource::CallEvent(EventType type, const std::any& eventData)
	{
		for (auto& rec : m_Receivers)
			rec->FireEvent(type, eventData);
	}

	void EventSource::CallEvent(EventType type, event_qualifier qualifier, const std::any& eventData)
	{
		for (auto& rec : m_Receivers)
			if (rec->m_Qualifier == qualifier)
				rec->FireEvent(type, eventData);
	}

	void EventSource::UnpinReceiver(EventReceiver* m_EventReceiver)
	{
		std::vector<EventReceiver*>::iterator it = std::find(m_Receivers.begin(), m_Receivers.end(), m_EventReceiver);

		if (it != m_Receivers.end())
			m_Receivers.erase(it);
	}

	mines::EventSource& EventActive::GetEventSource()
	{
		return m_EventSource;
	}

	mines::EventReceiver& EventActive::GetEventReceiver()
	{
		return m_EventReceiver;
	}

	EventActive::EventActive()
	{
		MINES_PIN_THIS();

		m_EventReceiver.AddHook(EventType::Destroy, Hook("EventActive.Destroy", [&](const EventData& data)
		{
			EventReceiver* destroyedReceiver = std::any_cast<EventReceiver*>(data.Value);
			m_EventSource.UnpinReceiver(destroyedReceiver);
		}));
	}

	EventActive::~EventActive()
	{
		g_EventSource.UnpinReceiver(&m_EventReceiver);
		g_EventSource.CallEvent(EventType::Destroy, &m_EventReceiver);
	}

}