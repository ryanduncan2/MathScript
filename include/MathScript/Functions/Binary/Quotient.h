#ifndef MATHSCRIPT_FUNCTIONS_BINARY__QUOTIENT_H_
#define MATHSCRIPT_FUNCTIONS_BINARY__QUOTIENT_H_

#include "MathScript/Function.h"

namespace MathScript
{
    class Quotient : public Function
    {
    private:
        Function* _numerator;
        Function* _denominator;

    public:
        Quotient(Function* numerator, Function* denominator);
        virtual ~Quotient();

        double Evaluate(double value) override;
        double Evaluate(std::map<std::string, double> variables) override;
    
        std::string ToString() override;
    };
}

#endif