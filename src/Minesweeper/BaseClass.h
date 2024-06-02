//****************************************************************
// File: BaseClass.h
// Purpose: Little neat base class for all stuff in this project.
// 
// Authors: The Kumor
//****************************************************************

#pragma once

#include <Minesweeper/Events.h>

namespace mines
{

	//----------------------------------------------------------
	// All classes derive from this.
	//----------------------------------------------------------
	class BaseClass : public EventActive
	{
	public:
		BaseClass() = default;
	};

}

// The Kumor