#ifndef MATHSCIPT_FUNCTIONS_UNARY_NEGATION_H_
#define MATHSCIPT_FUNCTIONS_UNARY_NEGATION_H_

#include "MathScript/Function.h"

namespace MathScript
{
    class Negation : public Function
    {
    private:
        Function* _value;

    public:
        Negation(Function* value);
        virtual ~Negation();
        
        double Evaluate(double value) override;
        double Evaluate(std::map<std::string, double> variables) override;
    
        std::string ToString() override;
    };
}

#endif