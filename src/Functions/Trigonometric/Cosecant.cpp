#include "MathScript/Functions/Trigonometric/Cosecant.h"

#include <cmath>

namespace MathScript
{
    Cosecant::Cosecant(Function* value)
    {
        _value = value;
    }

    Cosecant::~Cosecant()
    {
        delete _value;
    }

    double Cosecant::Evaluate(double value)
    {
        return 1.0 / std::sin(_value->Evaluate(value));
    }

    double Cosecant::Evaluate(std::map<std::string, double> variables)
    {
        return 1.0 / std::sin(_value->Evaluate(variables));
    }

    std::string Cosecant::ToString()
    {
        return "csc(" + _value->ToString() + ")";
    }
}