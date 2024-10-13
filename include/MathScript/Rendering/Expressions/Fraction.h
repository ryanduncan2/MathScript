#ifndef MATHSCRIPT_RENDERING_EXPRESSIONS_FRACTION_H_
#define MATHSCRIPT_RENDERING_EXPRESSIONS_FRACTION_H_

#include "MathScript/Rendering/ExpressionStructure.h"

namespace MathScript
{
    class Fraction : public ExpressionStructure
    {
    private:
        ExpressionStructure* m_Numerator;
        ExpressionStructure* m_Denominator;

    public:
        Fraction(ExpressionStructure* numerator, ExpressionStructure* denominator);
        virtual ~Fraction();

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