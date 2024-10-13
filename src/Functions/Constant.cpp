#include "MathScript/Functions/Constant.h"

namespace MathScript
{
    Constant::Constant(double value)
    {
        _value = value;
    }

    double Constant::Evaluate(double value)
    {
        return _value;
    }

    double Constant::Evaluate(std::map<std::string, double> variables)
    {
        return _value;
    }

    std::string Constant::ToString()
    {
        return std::to_string(_value);
    }
}