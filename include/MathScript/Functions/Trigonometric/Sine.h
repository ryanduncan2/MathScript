#ifndef MATHSCRIPT_FUNCTIONS_TRIGONOMETRIC_SINE_H_
#define MATHSCRIPT_FUNCTIONS_TRIGONOMETRIC_SINE_H_

#include "MathScript/Function.h"

namespace MathScript
{
    class Sine : public Function
    {
    private:
        Function* _value;

    public:
        Sine(Function* value);
        virtual ~Sine();

        double Evaluate(double value) override;
        double Evaluate(std::map<std::string, double> variables) override;
    
        std::string ToString() override;
    };
}

#endif