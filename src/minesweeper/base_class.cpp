#include "base_class.h"

namespace mwr
{

	BaseClass::BaseClass(bool forceListener)
	{
		if (forceListener)
			g_Dispatcher.AddListenerForce(&m_Listener);
		else
			g_Dispatcher.AddListener(&m_Listener);
	}

	BaseClass::~BaseClass()
	{
		g_Dispatcher.RemoveListener(&m_Listener);
	}

}