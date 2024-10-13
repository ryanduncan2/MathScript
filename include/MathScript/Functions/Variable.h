#ifndef MATHSCRIPT_FUNCTIONS_VARIABLE_H_
#define MATHSCRIPT_FUNCTIONS_VARIABLE_H_

#include "MathScript/Function.h"

namespace MathScript
{
    class Variable : public Function
    {
    private:
        std::string _name;

    public:
        Variable(std::string name);
        virtual ~Variable() { }
        
        double Evaluate(double value) override;
        double Evaluate(std::map<std::string, double> variables) override;
    
        std::string ToString() override;
    };
}

#endif