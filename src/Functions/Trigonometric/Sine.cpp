#include "MathScript/Functions/Trigonometric/Sine.h"

#include <cmath>

namespace MathScript
{
    Sine::Sine(Function* value)
    {
        _value = value;
    }

    Sine::~Sine()
    {
        delete _value;
    }

    double Sine::Evaluate(double value)
    {
        return std::sin(_value->Evaluate(value));
    }

    double Sine::Evaluate(std::map<std::string, double> variables)
    {
        return std::sin(_value->Evaluate(variables));
    }

    std::string Sine::ToString()
    {
        return "sin(" + _value->ToString() + ")";
    }
}