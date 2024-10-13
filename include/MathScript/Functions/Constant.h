#ifndef MATHSCIPRT_FUNCTIONS_CONSTANT_H_
#define MATHSCRIPT_FUNCTIONS_CONSTANT_H_

#include "MathScript/Function.h"

namespace MathScript
{
    class Constant : public Function
    {
    private:
        double _value;

    public:

        Constant(double value);
        virtual ~Constant() { }
        
        double Evaluate(double value) override;
        double Evaluate(std::map<std::string, double> variables) override;
    
        std::string ToString() override;
    };
}

#endif