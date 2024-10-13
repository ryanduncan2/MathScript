#ifndef MATHSCRIPT_SCRIPTENGINE_H_
#define MATHSCRIPT_SCRIPTENGINE_H_

#include "MathScript/Function.h"
#include "MathScript/Range.h"
#include "MathScript/SymbolTree.h"

#include <string>

namespace MathScript
{
    class ScriptEngine
    {
    private:
        static bool IsBinarySymbol(const char ch);
        static bool CheckBinaryParams(std::string firstParam, std::string secondParam);
        static std::string SanitiseScript(const std::string& str);
        static Function* ParseFunction(const SymbolNode* node);
        static void Optimise(SymbolTree& tree);
        static bool SplitAtSymbol(const std::string& script, std::string& out1, std::string& out2, char symbol, int begin);
        static bool CheckForFunction(const std::string& script, std::string& out, const std::string& function);

    public:
        ScriptEngine() = delete;
        ~ScriptEngine() = delete;

        static Function* InterpretFunction(std::string script);
        static Range InterpretRange(std::string script);
    };
}

#endif