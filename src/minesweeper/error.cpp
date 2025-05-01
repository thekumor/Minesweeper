#include "error.h"

namespace mwr
{

	DWORD MsgIfError(const char* info)
	{
		DWORD errorCode = GetLastError();
		LPSTR msg = nullptr;
		size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			nullptr, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<LPSTR>(&msg), 0, nullptr);

		if (errorCode)
			MessageBoxA(nullptr, msg, info, IDOK);

		return errorCode;
	}

}