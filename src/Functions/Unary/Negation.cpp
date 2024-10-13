#include "MathScript/Functions/Unary/Negation.h"

namespace MathScript
{
    Negation::Negation(Function* value)
    {
        _value = value;
    }

    Negation::~Negation()
    {
        delete _value;
    }

    double Negation::Evaluate(double value)
    {
        return -1 * _value->Evaluate(value);
    }

    double Negation::Evaluate(std::map<std::string, double> variables)
    {
        return -1 * _value->Evaluate(variables);
    }

    std::string Negation::ToString()
    {
        return "-" + _value->ToString();
    }
}