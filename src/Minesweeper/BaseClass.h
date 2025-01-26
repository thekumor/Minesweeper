//********************************************************************************************
// File: BaseClass.h
// Purpose: Little neat base class for all stuff in this project.
// 
// Authors: The Kumor
//********************************************************************************************

#pragma once

// Minesweeper
#include <Minesweeper/Events.h>

#define MINES_CLASSES_EVENTACTIVE 1
#ifdef MINES_CLASSES_EVENTACTIVE
#include <Minesweeper/Global.h>
#endif

namespace mines
{

	//------------------------------------------------------------------------------------
	// All classes derive from this.
	//------------------------------------------------------------------------------------
	class BaseClass : public EventActive
	{
	public:
		BaseClass();
	};

}

// The Kumor