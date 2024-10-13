#include "MathScript/Functions/Binary/Product.h"

namespace MathScript
{
    Product::Product(Function* multiplicand, Function* multiplier)
    {
        _multiplicand = multiplicand;
        _multiplier = multiplier;
    }

    Product::~Product()
    {
        delete _multiplicand;
        delete _multiplier;
    }

    double Product::Evaluate(double value)
    {
        return _multiplicand->Evaluate(value) * _multiplier->Evaluate(value);
    }

    double Product::Evaluate(std::map<std::string, double> variables)
    {
        return _multiplicand->Evaluate(variables) * _multiplier->Evaluate(variables);
    }

    std::string Product::ToString()
    {
        return _multiplicand->ToString() + " * " + _multiplier->ToString();
    }
}