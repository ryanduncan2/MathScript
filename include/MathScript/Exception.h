#ifndef MATHSCRIPT_EXCEPTION_H_
#define MATHSCRIPT_EXCEPTION_H_

#include <string>

namespace MathScript
{
    class Exception
    {
    private:
        std::string _origin;
        std::string _message;

        Exception(const std::string& origin, const std::string& message);

    public:
        static Exception FromMessage(const std::string& message) noexcept;
        static Exception FromMessage(const std::string& origin, const std::string& message) noexcept;

        const std::string GetMessage() const noexcept;
    };
}

#endif