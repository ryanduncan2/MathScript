#include "MathScript/Rendering/Expressions/Symbol.h"

namespace MathScript
{
    int Symbol::GetWidth(Font& font, const FontSize& size)
    {
        Glyph* glyph = font.GetGlyph(m_ASCIICode, size);
        int width = glyph->Width;

        if (m_Superscript != nullptr)
            width += m_Superscript->GetWidth(font, FontSize::SCRIPT) + font.GetSuperscriptSpacing(size);

        delete glyph;
        return width;
    }

    int Symbol::GetHeight(Font& font, const FontSize& size)
    {
        Glyph* glyph = font.GetGlyph(m_ASCIICode, size);
        int height = glyph->BearingY;

        if (m_Superscript != nullptr)
        {
            int heightWithScript = m_Superscript->GetHeight(font, FontSize::SCRIPT) + font.GetSuperscriptElevation(size);

            if (heightWithScript > height)
            {
                height = heightWithScript;
            }
        }

        delete glyph;
        return height;
    }

    int Symbol::GetDepth(Font& font, const FontSize& size)
    {
        Glyph* glyph = font.GetGlyph(m_ASCIICode, size);
        int depth = glyph->Height - glyph->BearingY;
        delete glyph;
        return depth;
    }

    int Symbol::GetBearingX(Font& font, const FontSize& size)
    {
        Glyph* glyph = font.GetGlyph(m_ASCIICode, size);
        int bearingX = glyph->BearingX;
        delete glyph;
        return bearingX;
    }
    
    int Symbol::GetRightBearingX(Font& font, const FontSize& size)
    {
        if (m_Superscript == nullptr)
        {
            Glyph* glyph = font.GetGlyph(m_ASCIICode, size);
            int advance = glyph->Advance - glyph->Width - glyph->BearingX;
            delete glyph;
            return advance;
        }
        else
        {
            return m_Superscript->GetRightBearingX(font, FontSize::SCRIPT);
        }
    }

    void Symbol::Render(Font& font, Image* image, std::size_t x, std::size_t y, const FontSize& size, const Colour& colour) // x is advance, y is baseline
    {
        Glyph* glyph = font.GetGlyph(m_ASCIICode, size);
        image->Draw(x, y - glyph->BearingY, glyph->Width, glyph->Height, glyph->Data, colour);

        if (m_Superscript != nullptr)
        {
            std::cout << "test" << std::endl;
            m_Superscript->Render(font, image, x + glyph->Width + font.GetSuperscriptSpacing(size), y - font.GetSuperscriptElevation(size), FontSize::SCRIPT, colour);
        }

        delete glyph;
    }

    void Symbol::Print(int indent)
    {
        std::string message = "";

        for (int i = 0; i < indent; ++i)
        {
            message += " ";
        }
        
        std::cout << message + " - Symbol Code: " + std::to_string(m_ASCIICode) << std::endl;
    }
}