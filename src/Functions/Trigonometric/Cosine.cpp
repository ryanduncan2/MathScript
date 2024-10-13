#include "MathScript/Functions/Trigonometric/Cosine.h"

#include <cmath>

namespace MathScript
{
    Cosine::Cosine(Function* value)
    {
        _value = value;
    }

    Cosine::~Cosine()
    {
        delete _value;
    }

    double Cosine::Evaluate(double value)
    {
        return std::cos(_value->Evaluate(value));
    }

    double Cosine::Evaluate(std::map<std::string, double> variables)
    {
        return std::cos(_value->Evaluate(variables));
    }

    std::string Cosine::ToString()
    {
        return "cos(" + _value->ToString() + ")";
    }
}