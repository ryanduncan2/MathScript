#ifndef MATHSCRIPT_FUNCTION_H_
#define MATHSCRIPT_FUNCTION_H_

#include <iostream>
#include <string>
#include <map>

namespace MathScript
{
    class Function
    {
    public:
        virtual ~Function() { }

        virtual double Evaluate(double value) = 0;
        virtual double Evaluate(std::map<std::string, double> variables) = 0;
        virtual std::string ToString() = 0;
        
        void Print()
        {
            std::cout << ToString() << std::endl;
        }
    };
}

#endif