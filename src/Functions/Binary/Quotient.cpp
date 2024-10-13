#include "MathScript/Functions/Binary/Quotient.h"

namespace MathScript
{
    Quotient::Quotient(Function* numerator, Function* denominator)
    {
        _numerator = numerator;
        _denominator = denominator;
    }

    Quotient::~Quotient()
    {
        delete _numerator;
        delete _denominator;
    }

    double Quotient::Evaluate(double value)
    {
        return _numerator->Evaluate(value) / _denominator->Evaluate(value);
    }

    double Quotient::Evaluate(std::map<std::string, double> variables)
    {
        return _numerator->Evaluate(variables) / _denominator->Evaluate(variables);
    }

    std::string Quotient::ToString()
    {
        return _numerator->ToString() + " / " + _denominator->ToString();
    }
}