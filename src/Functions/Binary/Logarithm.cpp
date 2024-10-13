#include "MathScript/Functions/Binary/Logarithm.h"

#include <cmath>

namespace MathScript
{
    Logarithm::Logarithm(Function* base, Function* argument)
    {
        _base = base;
        _argument = argument;
    }

    Logarithm::~Logarithm()
    {
        delete _base;
        delete _argument;
    }

    double Logarithm::Evaluate(double value)
    {
        return std::log(_argument->Evaluate(value)) / std::log(_base->Evaluate(value));
    }

    double Logarithm::Evaluate(std::map<std::string, double> variables)
    {
        return std::log(_argument->Evaluate(variables)) / std::log(_base->Evaluate(variables));
    }

    std::string Logarithm::ToString()
    {
        return "log_(" + _base->ToString() + ")(" + _argument->ToString() + ")";
    }
}