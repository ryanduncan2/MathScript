#ifndef MATHSCRIPT_FUNCTIONS_BINARY_SUM_H_
#define MATHSCRIPT_FUNCTIONS_BINARY_SUM_H_

#include "MathScript/Function.h"

namespace MathScript
{
    class Sum : public Function
    {
    private:
        Function* _addend1;
        Function* _addend2;

    public:
        Sum(Function* addend1, Function* addend2);
        virtual ~Sum();

        double Evaluate(double value) override;
        double Evaluate(std::map<std::string, double> variables) override;
    
        std::string ToString() override;
    };
}

#endif