//****************************************************************
// File: Errors.h
// Purpose: Error handling (checking & firing).
// 
// Authors: The Kumor
//****************************************************************

#pragma once

#include <cstdint>
#include <string>

#include <windows.h>

namespace mines
{

	// Checks if any of WinAPI errors were raised and displays a message.
	std::int32_t CheckErrors(const std::string& msg);

	// Displays an error message. Terminates the application, if fatal is true.
	void MakeError(const std::string& msg, bool fatal = false);

}

// The Kumor