#ifndef MATHSCRIPT_FUNCTIONS_TRIGONOMETRIC_COTANGENT_H_
#define MATHSCRIPT_FUNCTIONS_TRIGONOMETRIC_COTANGENT_H_

#include "MathScript/Function.h"

namespace MathScript
{
    class Cotangent : public Function
    {
    private:
        Function* _value;

    public:
        Cotangent(Function* value);
        virtual ~Cotangent();

        double Evaluate(double value) override;
        double Evaluate(std::map<std::string, double> variables) override;
    
        std::string ToString() override;
    };
}

#endif