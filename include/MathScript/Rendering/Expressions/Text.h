#ifndef MATHSCRIPT_RENDERING_EXPRESSIONS_TEXT_H_
#define MATHSCRIPT_RENDERING_EXPRESSIONS_TEXT_H_

#include "MathScript/Rendering/ExpressionStructure.h"

namespace MathScript
{
    class Text : public ExpressionStructure
    {
    private:
        bool m_Italics;

        std::string m_Text;

        Glyph* GetGlyph(Font& font, std::uint32_t asciiCode, const FontSize& size = FontSize::REGULAR);
        int GetTextWidth(Font& font, const FontSize& size = FontSize::REGULAR);

    public:
        Text(const std::string& expr, bool italics = true);

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