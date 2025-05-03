#include "base_class.h"

namespace mwr
{

	BaseClass::BaseClass()
	{
		g_Dispatcher.AddListener(&m_Listener);
	}

	BaseClass::~BaseClass()
	{
		g_Dispatcher.RemoveListener(&m_Listener);
	}

}