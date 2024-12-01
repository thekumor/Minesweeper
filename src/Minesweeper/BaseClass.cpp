#include "BaseClass.h"

namespace mines
{

	BaseClass::BaseClass()
	{
#ifdef MINES_CLASSES_EVENTACTIVE
		EventReceiver* receiver = &m_EventReceiver; // To show that it's unsafe.
		m_EventSource.PinReceiver(receiver);
#endif
	}

}