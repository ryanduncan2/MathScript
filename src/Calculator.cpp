#include "MathScript/Calculator.h"

#include "MathScript/Exception.h"
#include <cmath>
#include <iostream>

#define print(x) std::cout << x << std::endl

namespace MathScript
{
    bool Calculator::IsDigit(const char ch)
    {
        return ch >= '0' && ch <= '9';
    }

    bool Calculator::IsNumeric(const std::string& str)
    {
        if (str.length() == 0)
        {
            return false;
        }

        bool decimalReached = false;

        for (std::size_t i = str[0] == '-' ? 1 : 0; i < str.length(); ++i)
        {
            if (IsDigit(str[i]))
            {
                continue;
            }
            
            if (str[i] == '.')
            {
                if (decimalReached)
                {
                    return false;
                }
                else
                {
                    decimalReached = true;
                }
            }
            else
            {
                return false;
            }
        }

        return true;
    }

    int Calculator::ParseDigit(const char ch)
    {
        if (!IsDigit(ch))
        {
            throw Exception::FromMessage("Calculator::ParseDigit()", "Invalid argument.");
        }

        return (int)(ch - 48);
    }

    double Calculator::ParseDouble(const std::string& str)
    {
        if (!IsNumeric(str))
        {
            throw Exception::FromMessage("Calculator::ParseDouble()", "Invalid argument.");
        }

        double result = 0;

        int decimalPlace = str.length();

        for (std::size_t i = 0; i < str.length(); ++i)
        {
            if (str[i] == '.')
            {
                decimalPlace = i;
            }
        }

        bool negative = str[0] == '-';

        for (int i = negative ? 1 : 0; i < decimalPlace; ++i)
        {
            result += ParseDigit(str[i]) * std::pow(10, decimalPlace - i - 1);
        }

        for (std::size_t i = decimalPlace + 1; i < str.length(); ++i)
        {
            result += (double)ParseDigit(str[i]) * std::pow(10, decimalPlace - (int)i);
        }

        if (negative)
        {
            result *= -1;
        }

        return result;
    }
}