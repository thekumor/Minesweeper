#pragma once

#include <minesweeper/events.h>
#include <minesweeper/implementation.h>

namespace mwr
{

	class BaseClass : public EventActive
	{
	public:
		BaseClass(bool forceListener = false);
		~BaseClass();
	};

}