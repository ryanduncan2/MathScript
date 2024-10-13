#include "MathScript/Functions/Binary/Exponential.h"

#include <cmath>

namespace MathScript
{
    Exponential::Exponential(Function* base, Function* exponent)
    {
        _base = base;
        _exponent = exponent;
    }

    Exponential::~Exponential()
    {
        delete _base;
        delete _exponent;
    }

    double Exponential::Evaluate(double value)
    {
        return std::pow(_base->Evaluate(value), _exponent->Evaluate(value));
    }

    double Exponential::Evaluate(std::map<std::string, double> variables)
    {
        return std::pow(_base->Evaluate(variables), _exponent->Evaluate(variables));
    }
    
    std::string Exponential::ToString()
    {
        return "(" + _base->ToString() + ")^(" + _exponent->ToString() + ")";
    }
}