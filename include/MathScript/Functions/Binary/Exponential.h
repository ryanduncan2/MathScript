#ifndef MATHSCRIPT_FUNCTIONS_BINARY_EXPONENTIAL_H_
#define MATHSCRIPT_FUNCTIONS_BINARY_EXPONENTIAL_H_

#include "MathScript/Function.h"

namespace MathScript
{
    class Exponential : public Function
    {
    private:
        Function* _base;
        Function* _exponent;

    public:
        Exponential(Function* base, Function* exponent);
        virtual ~Exponential();

        double Evaluate(double value) override;
        double Evaluate(std::map<std::string, double> variables) override;

        std::string ToString() override;
    };
}

#endif