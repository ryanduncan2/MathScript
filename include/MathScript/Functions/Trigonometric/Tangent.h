#ifndef MATHSCRIPT_FUNCTIONS_TRIGONOMETRIC_TANGENT_H_
#define MATHSCRIPT_FUNCTIONS_TRIGONOMETRIC_TANGENT_H_

#include "MathScript/Function.h"

namespace MathScript
{
    class Tangent : public Function
    {
    private:
        Function* _value;

    public:
        Tangent(Function* value);
        virtual ~Tangent();

        double Evaluate(double value) override;
        double Evaluate(std::map<std::string, double> variables) override;
    
        std::string ToString() override;
    };
}

#endif