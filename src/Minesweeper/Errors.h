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

	std::int32_t CheckErrors(const std::string& msg);
	void MakeError(const std::string& msg, bool fatal = false);

}

// The Kumor