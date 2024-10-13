#ifndef MATHSCRIPT_RENDERING_EXPRESSION
#define MATHSCRIPT_RENDERING_EXPRESSION

#include <string>

#include "MathScript/Rendering/ExpressionStructure.h"

namespace MathScript
{
    class Expression
    {
    private:
        ExpressionStructure* m_Root;

        static ExpressionStructure* InterpretScript(const std::string& script);
        static ExpressionStructure* InterpretText(const std::string& text);
        static ExpressionStructure* DecodeCommand(const std::string& command);
        static ExpressionStructure* SelectSymbol(const std::string& symbolCode);
        static ExpressionStructure* SelectCommand(const std::string& commandCode, const std::vector<std::string>& params);

    public:
        Expression(const std::string& script);
        inline ~Expression() { delete m_Root; }

        Image* Render(int fontSize, const Colour& foregroundColour, const Colour& backgroundColour, int xPadding = 0, int yPadding = 0);

        inline int GetWidth(Font& font, const FontSize& size = FontSize::REGULAR) { return m_Root->GetWidth(font, size); }
        inline int GetHeight(Font& font, const FontSize& size = FontSize::REGULAR) { return m_Root->GetHeight(font, size); }
        inline int GetDepth(Font& font, const FontSize& size = FontSize::REGULAR) { return m_Root->GetDepth(font, size); }

        inline void Print() { m_Root->Print(0); }
    };
}

#endif