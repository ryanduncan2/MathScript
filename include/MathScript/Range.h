#ifndef MATHSCRIPT_RANGE_H_
#define MATHSCRIPT_RANGE_H_

#include "ST/Data/RandomGenerator.h"

#include "MathScript/Number.h"

namespace MathScript
{
    class Range
    {
    private:
        static ST::RandomGenerator _randGen;

        Number _number;
        float _min;
        float _max;
        bool _includeLeft;
        bool _includeRight;

    public:
        Range(float min, float max);
        Range(float min, float max, Number number, bool includeLeft, bool includeRight);
        ~Range();

        float GetMin() const noexcept;
        float GetMax() const noexcept;

        int GetRandomInt() const noexcept;
        float GetRandomFloat() const noexcept;

        void Print();
    };
}

#endif