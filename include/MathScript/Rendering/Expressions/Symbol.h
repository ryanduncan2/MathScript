#ifndef MATHSCRIPT_RENDERING_EXPERSSIONS_SYMBOL_H_
#define MATHSCRIPT_RENDERING_EXPERSSIONS_SYMBOL_H_

#include "MathScript/Rendering/ExpressionStructure.h"

namespace MathScript
{
    class Symbol : public ExpressionStructure
    {
    private:
        std::uint32_t m_ASCIICode;

    public:
        inline Symbol(const std::uint32_t asciiCode) : ExpressionStructure(), m_ASCIICode(asciiCode) { }

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