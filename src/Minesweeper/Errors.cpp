#include "Errors.h"

namespace mines
{

    std::int32_t CheckErrors(const std::string& msg)
    {
        std::int32_t errorCode = GetLastError();
        
        if (errorCode)
        {
            LPSTR message = 0;

            size_t size = FormatMessageA(
                FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                nullptr, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<LPSTR>(&message), 0, nullptr
            );

            MessageBoxA(nullptr, message, msg.c_str(), IDOK);
            LocalFree(message);
        }

        return errorCode;
    }

    void MakeError(const std::string& msg, bool fatal)
    {
        MessageBoxA(nullptr, msg.c_str(), "Error", IDOK);
        if (fatal)
            PostQuitMessage(1);
    }

}