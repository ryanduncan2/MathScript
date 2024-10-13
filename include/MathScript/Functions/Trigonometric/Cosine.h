#ifndef MATHSCRIPT_FUNCTIONS_TRIGONOMETRIC_COSINE_H_
#define MATHSCRIPT_FUNCTIONS_TRIGONOMETRIC_COSINE_H_

#include "MathScript/Function.h"

namespace MathScript
{
    class Cosine : public Function
    {
    private:
        Function* _value;

    public:
        Cosine(Function* value);
        virtual ~Cosine();

        double Evaluate(double value) override;
        double Evaluate(std::map<std::string, double> variables) override;
    
        std::string ToString() override;
    };
}

#endif