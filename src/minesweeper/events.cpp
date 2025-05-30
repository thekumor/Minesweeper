#include "events.h"

namespace mwr
{

#if MWR_COMPLEX_EVENT_SYSTEM
	Hook::Hook(const std::string& name, EventCallback callback)
		: Name(name), Callback(callback)
	{
	}

	EventListener::~EventListener()
	{
	}

	void* EventListener::GetQualifier()
	{
		return m_Qualifier;
	}

	void EventDispatcher::AddListener(EventListener* listener)
	{
		m_WaitingListeners.push_back(Handle<EventListener>(listener));
	}

	void EventDispatcher::AddListenerForce(EventListener* listener)
	{
		m_Listeners.push_back(Handle<EventListener>(listener));
	}

	void EventDispatcher::RemoveListener(EventListener* listener)
	{
		for (auto& k : m_Listeners)
		{
			if ((*k) == listener)
			{
				k.SetValid(false);
				break;
			}
		}

		for (auto& k : m_WaitingListeners)
		{
			if ((*k) == listener)
			{
				k.SetValid(false);
				break;
			}
		}
	}

	void EventDispatcher::CallEvent(EventType type, const std::any& data)
	{
		for (auto& k : m_Listeners)
		{
			if (k.IsValid())
				(*k)->OnCallEvent(type, data);
		}
	}

	void EventDispatcher::CallEventQualifier(EventType type, void* qualifier, const std::any& data)
	{
		for (auto& k : m_Listeners)
		{
			if (k.IsValid())
				if ((*k)->GetQualifier() == qualifier)
					(*k)->OnCallEvent(type, data);
		}
	}

	void EventDispatcher::RemoveInvalidListeners()
	{
		for (std::int32_t i = 0; i < m_Listeners.size(); i++)
		{
			if (!m_Listeners[i].IsValid())
			{
				m_Listeners.erase(m_Listeners.begin() + i);
				i--;
			}
		}

		for (std::int32_t i = 0; i < m_WaitingListeners.size(); i++)
		{
			if (!m_WaitingListeners[i].IsValid())
			{
				m_WaitingListeners.erase(m_WaitingListeners.begin() + i);
				i--;
			}
		}
	}

	void EventDispatcher::AddValidListeners()
	{
		for (auto& k : m_WaitingListeners)
			m_Listeners.push_back(k);

		m_WaitingListeners.clear();
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

	void EventListener::RemoveHook(EventType eventType, const std::string& name)
	{
		auto it = m_Hooks.find(eventType);

		if (it == m_Hooks.end())
			return;

		for (std::vector<Hook>::iterator it = m_Hooks[eventType].begin(); it != m_Hooks[eventType].end(); it++)
			if (it->Name == name)
			{
				m_Hooks[eventType].erase(it);
				return;
			}
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

	void EventActive::AddHook(EventType eventType, const Hook& hook)
	{
		m_Listener.AddHook(eventType, hook);
	}

	void EventActive::RemoveHook(EventType eventType, const std::string& name)
	{
		m_Listener.RemoveHook(eventType, name);
	}

#endif

}