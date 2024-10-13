#ifndef MATHSCRIPT_FUNCTIONS_BINARY_LOGARITHM_H_
#define MATHSCRIPT_FUNCTIONS_BINARY_LOGARITHM_H_

#include "MathScript/Function.h"

namespace MathScript
{
    class Logarithm : public Function
    {
    private:
        Function* _base;
        Function* _argument;

    public:
        Logarithm(Function* base, Function* argument);
        virtual ~Logarithm();

        double Evaluate(double value) override;
        double Evaluate(std::map<std::string, double> variables) override;
    
        std::string ToString() override;
    };
}

#endif