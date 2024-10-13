#ifndef MATHSCRIPT_FUNCTIONS_TRIGONOMETRIC_SECANT_H_
#define MATHSCRIPT_FUNCTIONS_TRIGONOMETRIC_SECANT_H_

#include "MathScript/Function.h"

namespace MathScript
{
    class Secant : public Function
    {
    private:
        Function* _value;

    public:
        Secant(Function* value);
        virtual ~Secant();

        double Evaluate(double value) override;
        double Evaluate(std::map<std::string, double> variables) override;
    
        std::string ToString() override;
    };
}

#endif