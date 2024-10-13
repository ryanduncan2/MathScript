#ifndef MATHSCRIPT_RENDERING_EXPRESSIONS_SUM_H_
#define MATHSCRIPT_RENDERING_EXPRESSIONS_SUM_H_

#include "MathScript/Rendering/ExpressionStructure.h"

namespace MathScript
{
    class Sigma : public ExpressionStructure
    {
    private:
        const int SUM_CODE = 0x2211;

        ExpressionStructure* m_Argument;
        ExpressionStructure* m_UpperBound;
        ExpressionStructure* m_LowerBound;

    public:
        Sigma(ExpressionStructure* argument, ExpressionStructure* upperBound, ExpressionStructure* lowerBound);
        virtual ~Sigma();

        int GetWidth(Font& font, const FontSize& size = FontSize::REGULAR) override;
        int GetHeight(Font& font, const FontSize& size = FontSize::REGULAR) override;
        int GetDepth(Font& font, const FontSize& size = FontSize::REGULAR) override;
        int GetBearingX(Font& font, const FontSize& size = FontSize::REGULAR) override;
        int GetRightBearingX(Font& font, const FontSize& size = FontSize::REGULAR) override;

        void Render(Font& font, Image* image, std::size_t x, std::size_t y, const FontSize& size, const Colour& colour) override;
        void Print(int indent) override;
    };
}

#endif