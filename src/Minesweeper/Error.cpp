#include "Error.h"

namespace mwr
{

	DWORD MsgIfError(const wchar_t* info)
	{
		DWORD errorCode = GetLastError();
		LPWSTR msg = nullptr;
		size_t size = FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			nullptr, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), msg, 0, nullptr);

		if (errorCode)
			MessageBoxW(nullptr, msg, static_cast<LPCWSTR>(info), IDOK);

		return errorCode;
	}

}