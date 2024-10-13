#ifndef MATHSCRIPT_RENDERING_EXPRESSIONSTRUCTURE_H_
#define MATHSCRIPT_RENDERING_EXPRESSIONSTRUCTURE_H_

#include <string>
#include <vector>

#include "MathScript/Rendering/Image.h"
#include "MathScript/Rendering/Font.h"

namespace MathScript
{
    class ExpressionStructure
    {
    protected:
        // Expression Decorations
        ExpressionStructure* m_Superscript;
        ExpressionStructure* m_Subscript;
        ExpressionStructure* m_Underscript;

    public:
        ExpressionStructure();
        ~ExpressionStructure();

        // Decoration Setters
        inline void SetSuperscript(ExpressionStructure* superscript) { m_Superscript = superscript; }
        inline void SetSubscript(ExpressionStructure* subscript) { m_Subscript = subscript; }
        inline void SetUnderscript(ExpressionStructure* underscript) { m_Underscript = underscript; }

        // Expression Metrics
        virtual int GetWidth(Font& font, const FontSize& size) = 0;
        virtual int GetHeight(Font& font, const FontSize& size) = 0;
        virtual int GetDepth(Font& font, const FontSize& size) = 0;
        virtual int GetBearingX(Font& font, const FontSize& size) = 0;
        virtual int GetRightBearingX(Font& font, const FontSize& size) = 0;

        // Expression Functions
        virtual void Render(Font& font, Image* image, std::size_t x, std::size_t y, const FontSize& size, const Colour& colour) = 0;
        virtual void Print(int indent) = 0;
    };
}

#endif