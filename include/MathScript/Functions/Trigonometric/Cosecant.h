#ifndef MATHSCRIPT_FUNCTIONS_TRIGONOMETRIC_COSECANT_H_
#define MATHSCRIPT_FUNCTIONS_TRIGONOMETRIC_COSECANT_H_

#include "MathScript/Function.h"

namespace MathScript
{
    class Cosecant : public Function
    {
    private:
        Function* _value;

    public:
        Cosecant(Function* value);
        virtual ~Cosecant();

        double Evaluate(double value) override;
        double Evaluate(std::map<std::string, double> variables) override;
    
        std::string ToString() override;
    };
}

#endif