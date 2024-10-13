#include "MathScript/ScriptEngine.h"

#include <vector>
#include <iostream>

#include "MathScript/Functions/CommonFunctions.h"
#include "MathScript/Calculator.h"
#include "MathScript/Exception.h"

namespace MathScript
{
    std::string ScriptEngine::SanitiseScript(const std::string& str)
    {
        std::string result = str;

        for (std::size_t i = 0; i < result.length(); ++i)
        {
            if (result[i] == ' ')
            {
                result = result.substr(0, i) + result.substr(i + 1, result.length() - i - 1);
                i--;
            }
        }

        if (result.length() < 3 || result[0] != '(' || result[result.length() - 1] != ')')
        {
            return result;
        }

        int parenDepth = 0;

        for (std::size_t i = 1; i < result.length() - 1; ++i)
        {
            if (result[i] == '(')
            {
                parenDepth++;
            }

            if (result[i] == ')')
            {
                parenDepth--;

                if (parenDepth < 0)
                {
                    return result;
                }
            }
        }

        return SanitiseScript(result.substr(1, result.length() - 2));
    }

    Function* ScriptEngine::InterpretFunction(std::string script)
    {
        if (script.length() == 0)
        {
            return nullptr;
        }

        SymbolTree tree = SymbolTree(SanitiseScript(script));
        std::vector<SymbolNode*> uninspected = { tree.GetRoot() };

        while (!uninspected.empty())
        {
            SymbolNode* currentNode = uninspected[0];
            std::string script1, script2;

            // ----- Addition -----
            if (SplitAtSymbol(currentNode->_symbol, script1, script2, '+', 0))
            {
                if (!CheckBinaryParams(script1, script2))
                {
                    throw Exception::FromMessage("ScriptEngine::Interpret()", "Incorrect addition parameters.");
                }

                currentNode->Diverge(Operation::ADDITION, new SymbolNode(script1), new SymbolNode(script2));
            }
            // ----- Subtraction -----
            else if (SplitAtSymbol(currentNode->_symbol, script1, script2, '-', 1))
            {
                if (!CheckBinaryParams(script1, script2))
                {
                    throw Exception::FromMessage("ScriptEngine::Interpret()", "Incorrect subtraction parameters.");
                }

                currentNode->Diverge(Operation::SUBTRACTION, new SymbolNode(script1), new SymbolNode(script2));
            }
            // Multiplication
            else if (SplitAtSymbol(currentNode->_symbol, script1, script2, '*', 0))
            {
                if (!CheckBinaryParams(script1, script2))
                {
                    throw Exception::FromMessage("ScriptEngine::Interpret()", "Incorrect multiplication parameters.");
                }

                currentNode->Diverge(Operation::MULTIPLICATION, new SymbolNode(script1), new SymbolNode(script2));
            }
            // Division
            else if (SplitAtSymbol(currentNode->_symbol, script1, script2, '/', 0))
            {
                if (!CheckBinaryParams(script1, script2))
                {
                    throw Exception::FromMessage("ScriptEngine::Interpret()", "Incorrect division parameters.");
                }

                currentNode->Diverge(Operation::DIVISION, new SymbolNode(script1), new SymbolNode(script2));
            }
            // Exponentiation
            else if (SplitAtSymbol(currentNode->_symbol, script1, script2, '^', 0))
            {
                if (!CheckBinaryParams(script1, script2))
                {
                    throw Exception::FromMessage("ScriptEngine::Interpret()", "Incorrect exponentiation parameters.");
                }

                currentNode->Diverge(Operation::EXPONENTIATION, new SymbolNode(script1), new SymbolNode(script2));
            }
            // Negation
            else if (currentNode->_symbol[0] == '-')
            {
                std::string script = SanitiseScript(currentNode->_symbol.substr(1, currentNode->_symbol.length() - 1));

                if (script.length() == 0 || (IsBinarySymbol(script[0]) && script[0] != '-'))
                {
                    throw Exception::FromMessage("ScriptEngine::Interpret()", "Incorrect negation parameter.");
                }

                currentNode->Diverge(Operation::NEGATION, new SymbolNode(script), nullptr);
            }
            // Logarithms (log10)
            else if (CheckForFunction(currentNode->_symbol, script1, "log"))
            {
                currentNode->Diverge(Operation::LOGARITHM, new SymbolNode("10"), new SymbolNode(script1));
            }
            // Natural Logarithms
            else if (CheckForFunction(currentNode->_symbol, script1, "ln"))
            {
                currentNode->Diverge(Operation::LOGARITHM, new SymbolNode(std::to_string(Calculator::EDouble)), new SymbolNode(script1));
            }
            // Sine
            else if (CheckForFunction(currentNode->_symbol, script1, "sin"))
            {
                currentNode->Diverge(Operation::SIN, new SymbolNode(script1), nullptr);
            }
            // Cosine
            else if (CheckForFunction(currentNode->_symbol, script1, "cos"))
            {
                currentNode->Diverge(Operation::COS, new SymbolNode(script1), nullptr);
            }
            // Tangent
            else if (CheckForFunction(currentNode->_symbol, script1, "tan"))
            {
                currentNode->Diverge(Operation::TAN, new SymbolNode(script1), nullptr);
            }
            // Secant
            else if (CheckForFunction(currentNode->_symbol, script1, "sec"))
            {
                currentNode->Diverge(Operation::SEC, new SymbolNode(script1), nullptr);
            }
            // Cosecant
            else if (CheckForFunction(currentNode->_symbol, script1, "csc"))
            {
                currentNode->Diverge(Operation::CSC, new SymbolNode(script1), nullptr);
            }
            // Cotangent
            else if (CheckForFunction(currentNode->_symbol, script1, "cot"))
            {
                currentNode->Diverge(Operation::COT, new SymbolNode(script1), nullptr);
            }
            // Constant/Variable Check (this must be last)
            else if (Calculator::IsNumeric(currentNode->_symbol))
            {
                currentNode->_operation = Operation::CONSTANT;
            }
            else
            {
                currentNode->_operation = Operation::VARIABLE;
            }

            if (currentNode->_arg1 != nullptr)
            {
                uninspected.push_back(currentNode->_arg1);
            }

            if (currentNode->_arg2 != nullptr)
            {
                uninspected.push_back(currentNode->_arg2);
            }

            uninspected.erase(uninspected.begin());
        }

        Optimise(tree);

        return ParseFunction(tree.GetRoot());
    }

    Range ScriptEngine::InterpretRange(std::string script)
    {
        // Form: Q[-4,17];

        Number number;
        float min, max;
        bool includeLeft, includeRight;

        // Type of Number.

        switch (script[0])
        {
            case 'N': number = Number::NATURAL; break;
            case 'Z': number = Number::INTEGER; break;
            case 'Q': number = Number::RATIONAL; break;
            case 'R': number = Number::REAL; break;
        }

        // Lower Bound Inclusivity

        includeLeft = script[1] == '[' ? true : false;

        // Lower Bound

        std::string temp = "";
        int index = 2;
        while (script[index] != ',')
        {
            temp += script[index];
            index++;
        }

        try
        {
            min = std::stof(temp);
        }
        catch(const std::exception& e)
        {
            std::cout << "error parsing lower bound" << std::endl;
            return Range(0, 0); // TODO: throw error message.
        }

        // Upper Bound

        index++;
        temp = "";

        while (script[index] != ')' && script[index] != ']')
        {
            temp += script[index];
            index++;
        }

        try
        {
            max = std::stof(temp);
        }
        catch(const std::exception& e)
        {
            std::cout << "error parsing upper bound: " << temp << std::endl;
            return Range(0, 0); // TODO: throw error message.
        }

        // Upper Bound Inclusivity

        includeRight = script[script.length() - 1] == ']' ? true : false;

        return Range(min, max, number, includeLeft, includeRight);
    }

    void ScriptEngine::Optimise(SymbolTree& tree)
    {
        // Potential Optimisations: combining like terms and constants, trigonometric simplification

        std::vector<SymbolNode*> roots = { tree.GetRoot() };

        // Combining Constants (Addition)

        while (!roots.empty())
        {
            SymbolNode* accumulator = nullptr;
            std::vector<SymbolNode*> branches = { roots[0] };

            while (!branches.empty())
            {
                SymbolNode* currentNode = branches[0];

                if (currentNode->_operation == Operation::ADDITION)
                {
                    branches.push_back(currentNode->_arg1);
                    branches.push_back(currentNode->_arg2);
                }
                else if (currentNode->_operation == Operation::CONSTANT)
                {
                    if (accumulator == nullptr)
                    {
                        accumulator = currentNode;
                    }
                    else
                    {
                        accumulator->_symbol = std::to_string(Calculator::ParseDouble(currentNode->_symbol) + Calculator::ParseDouble(accumulator->_symbol));
                        tree.SpliceLeafNode(currentNode);
                    }
                }
                else
                {
                    if (currentNode->_arg1 != nullptr)
                    {
                        roots.push_back(currentNode->_arg1);
                    }

                    if (currentNode->_arg2 != nullptr)
                    {
                        roots.push_back(currentNode->_arg2);
                    }
                }

                branches.erase(branches.begin());
            }

            roots.erase(roots.begin());
        }
    }

    bool ScriptEngine::SplitAtSymbol(const std::string& script, std::string& out1, std::string& out2, const char symbol, int begin)
    {
        int parenDepth = 0;

        for (std::size_t i = begin; i < script.length(); ++i)
        {
            if (script[i] == '(')
            {
                parenDepth++;
            }
            else if (script[i] == ')')
            {
                parenDepth--;
            }
            else if (script[i] == symbol && parenDepth == 0)
            {
                out1 = SanitiseScript(script.substr(0, i));
                out2 = SanitiseScript(script.substr(i + 1, script.length() - i - 1));

                return true;
            }
        }

        return false;
    }

    bool ScriptEngine::CheckForFunction(const std::string& script, std::string& out, const std::string& function)
    {
        if (script.substr(0, function.length()) == function && script[function.length()] == '(')
        {
            int parenDepth = 1;

            for (std::size_t i = function.length() + 1; i < script.length(); ++i)
            {   
                switch (script[i])
                {
                    case '(': parenDepth++; break;
                    case ')': parenDepth--; break;
                }

                if (parenDepth == 0)
                {
                    out = SanitiseScript(script.substr(function.length() + 1, i - function.length() - 1));
                }
            }

            return true;
        }

        return false;
    }

    bool ScriptEngine::CheckBinaryParams(std::string firstParam, std::string secondParam)
    {
        if (firstParam.length() == 0 || secondParam.length() == 0)
        {
            return false;
        }

        char left = firstParam[firstParam.length() - 1];
        char right = secondParam[0];

        return !IsBinarySymbol(left) && !(IsBinarySymbol(right) && right != '-');
    }

    bool ScriptEngine::IsBinarySymbol(const char ch)
    {
        return ch == '+' ||
               ch == '-' ||
               ch == '*' ||
               ch == '/' ||
               ch == '^' ||
               ch == '%' ||
               ch == '!';
    }

    Function* ScriptEngine::ParseFunction(const SymbolNode* node)
    {
        switch (node->_operation)
        {
            case ADDITION:          return new Sum(ParseFunction(node->_arg1), ParseFunction(node->_arg2));
            case SUBTRACTION:       return new Sum(ParseFunction(node->_arg1), new Negation(ParseFunction(node->_arg2)));
            case MULTIPLICATION:    return new Product(ParseFunction(node->_arg1), ParseFunction(node->_arg2));
            case DIVISION:          return new Quotient(ParseFunction(node->_arg1), ParseFunction(node->_arg2));
            case EXPONENTIATION:    return new Exponential(ParseFunction(node->_arg1), ParseFunction(node->_arg2));
            case LOGARITHM:         return new Logarithm(ParseFunction(node->_arg1), ParseFunction(node->_arg2));
            case NEGATION:          return new Negation(ParseFunction(node->_arg1));
            case SIN:               return new Sine(ParseFunction(node->_arg1));
            case COS:               return new Cosine(ParseFunction(node->_arg1));
            case TAN:               return new Tangent(ParseFunction(node->_arg1));
            case SEC:               return new Secant(ParseFunction(node->_arg1));
            case CSC:               return new Cosecant(ParseFunction(node->_arg1));
            case COT:               return new Cotangent(ParseFunction(node->_arg1));
            case CONSTANT:          return new Constant(Calculator::ParseDouble(node->_symbol));
            case VARIABLE:          return new Variable(node->_symbol);
        }

        return nullptr;
    }
}