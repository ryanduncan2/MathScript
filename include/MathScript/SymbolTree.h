#ifndef MATHSCRIPT_SYMBOLTREE_H_
#define MATHSCRIPT_SYMBOLTREE_H_

#include <string>

namespace MathScript
{
    enum Operation
    {
        CONSTANT, VARIABLE,
        ADDITION, SUBTRACTION, MULTIPLICATION, DIVISION, EXPONENTIATION, LOGARITHM,
        SIN, COS, TAN, SEC, CSC, COT,
        ARCSIN, ARCCOS, ARCTAN, ARCSEC, ARCCSC, ARCCOT,
        SINH, COSH, TANH, SECH, CSCH, COTH,
        ARSINH, ARCOSH, ARTANH, ARSECH, ARCSCH, ARCOTH,
        NEGATION, FACTORIAL, CEILING, FLOOR, ABS
    };

    class SymbolNode
    {
    public:
        std::string _symbol;

        Operation _operation;
        SymbolNode* _arg1;
        SymbolNode* _arg2;
        SymbolNode* _parent;

        SymbolNode(std::string symbol);
        ~SymbolNode();

        void Diverge(Operation operation, SymbolNode* arg1, SymbolNode* arg2);
    };

    class SymbolTree
    {
    private:
        SymbolNode* _root;

    public:
        SymbolTree(std::string script);
        ~SymbolTree();

        SymbolNode* GetRoot();
        void SetRoot(SymbolNode* root);
        void SpliceLeafNode(SymbolNode* node);
        void Print(SymbolNode* node, int indent);
    };
}

#endif