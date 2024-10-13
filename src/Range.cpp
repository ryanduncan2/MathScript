#include "MathScript/Range.h"

#include <iostream>

namespace MathScript
{
    ST::RandomGenerator Range::_randGen = ST::RandomGenerator();

    Range::Range(float min, float max)
    {
        _min = min;
        _max = max;
        _includeLeft = true;
        _includeRight = true;
        _number = Number::REAL;
    }

    Range::Range(float min, float max, Number number, bool includeLeft, bool includeRight)
    {
        _min = min;
        _max = max;
        _number = number;
        _includeLeft = includeLeft;
        _includeRight = includeRight;
    }

    Range::~Range()
    {

    }

    float Range::GetMin() const noexcept
    {
        return _min;
    }

    float Range::GetMax() const noexcept
    {
        return _max;
    }

    int Range::GetRandomInt() const noexcept
    {
        return _randGen.GetInt(_min, _max);
    }

    float Range::GetRandomFloat() const noexcept
    {
        return _randGen.GetFloat(_min, _max);
    }

    void Range::Print()
    {
        std::cout << (char)_number << (_includeLeft ? "[" : "(") << _min << "," << _max << (_includeRight ? "]" : ")") << std::endl;
    }
}