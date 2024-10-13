#ifndef MATHSCRIPT_FUNCTIONS_BINARY_PRODUCT_H_
#define MATHSCRIPT_FUNCTIONS_BINARY_PRODUCT_H_

#include "MathScript/Function.h"

namespace MathScript
{
    class Product : public Function
    {
    private:
        Function* _multiplicand;
        Function* _multiplier;

    public:
        Product(Function* multiplicand, Function* multiplier);
        virtual ~Product();

        double Evaluate(double value) override;
        double Evaluate(std::map<std::string, double> variables) override;
    
        std::string ToString() override;
    };
}

#endif