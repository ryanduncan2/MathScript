#include "MathScript/Functions/Trigonometric/Secant.h"

#include <cmath>

namespace MathScript
{
    Secant::Secant(Function* value)
    {
        _value = value;
    }

    Secant::~Secant()
    {
        delete _value;
    }

    double Secant::Evaluate(double value)
    {
        return 1.0 / std::cos(_value->Evaluate(value));
    }

    double Secant::Evaluate(std::map<std::string, double> variables)
    {
        return 1.0 / std::cos(_value->Evaluate(variables));
    }

    std::string Secant::ToString()
    {
        return "sec(" + _value->ToString() + ")";
    }
}