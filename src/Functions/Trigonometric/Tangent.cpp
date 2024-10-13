#include "MathScript/Functions/Trigonometric/Tangent.h"

#include <cmath>

namespace MathScript
{
    Tangent::Tangent(Function* value)
    {
        _value = value;
    }

    Tangent::~Tangent()
    {
        delete _value;
    }

    double Tangent::Evaluate(double value)
    {
        return std::tan(_value->Evaluate(value));
    }

    double Tangent::Evaluate(std::map<std::string, double> variables)
    {
        return std::tan(_value->Evaluate(variables));
    }

    std::string Tangent::ToString()
    {
        return "tan(" + _value->ToString() + ")";
    }
}