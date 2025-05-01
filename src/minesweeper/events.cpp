#include "events.h"

namespace mwr
{

	Hook::Hook(const std::string& name, EventCallback callback)
		: Name(name), Callback(callback)
	{
	}

	void* EventListener::GetQualifier()
	{
		return m_Qualifier;
	}

	void EventDispatcher::AddListener(EventListener* listener)
	{
		m_Listeners.push_back(listener);
	}

	void EventDispatcher::RemoveListener(EventListener* listener)
	{
		std::erase(m_Listeners, listener);
	}

	void EventDispatcher::CallEvent(EventType type, const std::any& data)
	{
		for (auto& k : m_Listeners)
			k->OnCallEvent(type, data);
	}

	void EventDispatcher::CallEventQualifier(EventType type, void* qualifier, const std::any& data)
	{
		for (auto& k : m_Listeners)
		{
			if (k->GetQualifier() == qualifier)
				k->OnCallEvent(type, data);
		}
	}

	void EventListener::OnCallEvent(EventType type, const std::any& data)
	{
		if (m_Hooks.find(type) != m_Hooks.end())
		{
			for (auto& k : m_Hooks[type])
				k.Callback(data);
		}
	}

	void EventListener::AddHook(EventType eventType, const Hook& hook)
	{
		m_Hooks[eventType].push_back(hook);
	}

	void EventListener::SetQualifier(void* qualifier)
	{
		m_Qualifier = qualifier;
	}

	mwr::EventDispatcher& EventActive::GetDispatcher()
	{
		return m_Dispatcher;
	}

	mwr::EventListener& EventActive::GetListener()
	{
		return m_Listener;
	}

}