#include "MathScript/Functions/Variable.h"

#include <map>

namespace MathScript
{
    Variable::Variable(std::string name)
    {
        _name = name;
    }

    double Variable::Evaluate(double value)
    {
        return value;
    }

    double Variable::Evaluate(std::map<std::string, double> variables)
    {
        for (std::map<std::string, double>::iterator it = variables.begin(); it != variables.end(); ++it)
        {
            if (it->first == _name)
            {
                return it->second;
            }
        }

        throw std::string("Variable " + _name + " not found in map.");
    }

    std::string Variable::ToString()
    {
        return _name;
    }
}