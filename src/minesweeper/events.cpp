#include "events.h"

namespace mwr
{

	Event::Event(const std::string& name, const std::vector<Hook>& hooks)
		: Name(name), Hooks(hooks)
	{
	}

	Hook::Hook(const std::string& name, EventCallback callback)
		: Name(name), Callback(callback)
	{
	}

	void EventDispatcher::AddListener(std::shared_ptr<EventListener> listener)
	{
		m_Listeners.push_back(listener);
	}

	void EventDispatcher::RemoveListener(std::shared_ptr<EventListener> listener)
	{
		for (std::vector<std::shared_ptr<EventListener>>::iterator it = m_Listeners.begin(); it != m_Listeners.end(); it++)
		{
			if (*it == listener)
			{
				m_Listeners.erase(it);
				break;
			}
		}
	}

}