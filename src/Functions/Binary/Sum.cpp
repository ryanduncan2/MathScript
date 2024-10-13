#include "MathScript/Functions/Binary/Sum.h"

namespace MathScript
{
    Sum::Sum(Function* addend1, Function* addend2)
    {
        _addend1 = addend1;
        _addend2 = addend2;
    }

    Sum::~Sum()
    {
        delete _addend1;
        delete _addend2;
    }

    double Sum::Evaluate(double value)
    {
        return _addend1->Evaluate(value) + _addend2->Evaluate(value);
    }

    double Sum::Evaluate(std::map<std::string, double> variables)
    {
        return _addend1->Evaluate(variables) + _addend2->Evaluate(variables);
    }

    std::string Sum::ToString()
    {
        return _addend1->ToString() + " + " + _addend2->ToString();
    }
}