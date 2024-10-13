#include "MathScript/Functions/Trigonometric/Cotangent.h"

#include <cmath>

namespace MathScript
{
    Cotangent::Cotangent(Function* value)
    {
        _value = value;
    }

    Cotangent::~Cotangent()
    {
        delete _value;
    }

    double Cotangent::Evaluate(double value)
    {
        return 1.0 / std::tan(_value->Evaluate(value));
    }

    double Cotangent::Evaluate(std::map<std::string, double> variables)
    {
        return 1.0 / std::tan(_value->Evaluate(variables));
    }

    std::string Cotangent::ToString()
    {
        return "cot(" + _value->ToString() + ")";
    }
}