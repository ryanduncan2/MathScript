#include "MathScript/Exception.h"
#include <iostream>

namespace MathScript
{
    Exception::Exception(const std::string& origin, const std::string& message)
    {
        _origin = origin;
        _message = message;

        std::cout << GetMessage() << std::endl;
    }

    Exception Exception::FromMessage(const std::string& message) noexcept
    {
        return Exception("Unspecified", message);
    }

    Exception Exception::FromMessage(const std::string& origin, const std::string& message) noexcept
    {
        return Exception(origin, message);
    }

    const std::string Exception::GetMessage() const noexcept
    {
        return "Exception:[Origin: " + _origin + ", Message: \"" + _message + "\"]";
    }
}