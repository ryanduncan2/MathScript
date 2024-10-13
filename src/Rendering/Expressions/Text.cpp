#include "MathScript/Rendering/Expressions/Text.h"

#include <cmath>

namespace MathScript
{
    Text::Text(const std::string& expr, bool italics)
        : ExpressionStructure(), 
        m_Text(expr),
        m_Italics(italics)
    {
    }

    Glyph* Text::GetGlyph(Font& font, std::uint32_t asciiCode, const FontSize& size)
    {
        if (m_Italics && ((asciiCode >= 65 && asciiCode <= 90) || (asciiCode >= 97 && asciiCode <= 122)))
        {
            return font.GetItalicGlyph(asciiCode, size);
        }
        else
        {
            return font.GetGlyph(asciiCode, size);
        }
    }

    int Text::GetTextWidth(Font& font, const FontSize& size)
    {
        // First Glyph (excludes bearingX)
        Glyph* glyph = GetGlyph(font, m_Text[0], size);
        int width = glyph->Advance - glyph->BearingX;
        delete glyph;

        // Middle Glyphs
        for (std::size_t i = 1; i < m_Text.length(); ++i)
        {
            glyph = GetGlyph(font, m_Text[i], size);
            width += glyph->Advance;
            delete glyph;
        }

        // Removes extra space on last glyph.
        glyph = GetGlyph(font, m_Text[m_Text.length() - 1], size);
        width -= glyph->Advance - glyph->Width - glyph->BearingX;

        return width;
    }

    int Text::GetWidth(Font& font, const FontSize& size)
    {
        // First Glyph (excludes bearingX)
        Glyph* glyph = GetGlyph(font, m_Text[0], size);
        int width = glyph->Advance - glyph->BearingX;
        delete glyph;

        // Middle Glyphs
        for (std::size_t i = 1; i < m_Text.length(); ++i)
        {
            glyph = GetGlyph(font, m_Text[i], size);
            width += glyph->Advance;
            delete glyph;
        }

        // Removes extra space on last glyph.
        glyph = GetGlyph(font, m_Text[m_Text.length() - 1], size);
        width -= glyph->Advance - (int)glyph->Width - glyph->BearingX;

        // Text Decorations
        int scriptWidth = 0;

        if (m_Superscript != nullptr)
            scriptWidth = m_Superscript->GetWidth(font, FontSize::SCRIPT) + font.GetSuperscriptSpacing(size);

        if (m_Subscript != nullptr)
        {
            if (m_Italics)
            {
                scriptWidth = std::max(scriptWidth, (int)std::round(m_Subscript->GetWidth(font, FontSize::SCRIPT) + (float)font.GetSuperscriptSpacing(size) * 0.5f));
            }
            else
            {
                scriptWidth = std::max(scriptWidth, m_Subscript->GetWidth(font, FontSize::SCRIPT) + font.GetSuperscriptSpacing(size));
            }
        }

        width += scriptWidth;

        if (m_Underscript != nullptr)
        {
            int underscriptWidth = m_Underscript->GetWidth(font, FontSize::SCRIPT);
            width = std::max(width, underscriptWidth);
        }

        return width;
    }

    int Text::GetHeight(Font& font, const FontSize& size)
    {
        Glyph* glyph = GetGlyph(font, m_Text[0], size);
        int height = glyph->BearingY;
        delete glyph;

        for (std::size_t i = 1; i < m_Text.length(); ++i)
        {
            Glyph* glyph = GetGlyph(font, m_Text[i], size);

            if (glyph->BearingY > height)
            {
                height = glyph->BearingY;
            }

            delete glyph;
        }

        // Text Decorations
        if (m_Superscript != nullptr)
        {
            int heightWithScript = m_Superscript->GetHeight(font, FontSize::SCRIPT) + font.GetSuperscriptElevation(size);

            if (heightWithScript > height)
            {
                height = heightWithScript;
            }
        }

        return height;
    }

    int Text::GetDepth(Font& font, const FontSize& size)
    {
        int largestDepth = 0;

        for (std::size_t i = 0; i < m_Text.length(); ++i)
        {
            Glyph* glyph = GetGlyph(font, m_Text[i], size);
            int depth = std::abs((int)glyph->Height) - std::abs(glyph->BearingY);
            delete glyph;

            if (depth > largestDepth)
            {
                largestDepth = depth;
            }
        }

        if (m_Subscript != nullptr)
        {
            int depthWithScript = m_Subscript->GetDepth(font, FontSize::SCRIPT) + font.GetSuperscriptElevation(size);

            if (depthWithScript > largestDepth)
            {
                largestDepth = depthWithScript;
            }
        }

        if (m_Underscript != nullptr)
        {
            int depthWithUnderscript = (font.GetMeanLine(FontSize::SCRIPT) * 2) + m_Underscript->GetDepth(font, FontSize::SCRIPT);

            if (depthWithUnderscript > largestDepth)
            {
                largestDepth = depthWithUnderscript;
            }
        }

        return largestDepth;
    }

    int Text::GetBearingX(Font& font, const FontSize& size)
    {
        Glyph* glyph = GetGlyph(font, m_Text[0], size);
        int bearingX = glyph->BearingX;
        delete glyph;
        return bearingX;
    }

    int Text::GetRightBearingX(Font& font, const FontSize& size)
    {
        int scriptBearingX = 0;

        if (m_Superscript != nullptr || m_Subscript != nullptr)
        {
            if (m_Superscript != nullptr)
            {
                scriptBearingX = m_Superscript->GetRightBearingX(font, FontSize::SCRIPT);
            }

            if (m_Subscript != nullptr)
            {
                scriptBearingX = std::max(scriptBearingX, m_Subscript->GetRightBearingX(font, FontSize::SCRIPT));
            }

            return scriptBearingX;
        }

        Glyph* glyph = GetGlyph(font, m_Text[m_Text.length() - 1], size);
        int advance = glyph->Advance - glyph->Width - glyph->BearingX;
        delete glyph;
        return advance;
    }

    void Text::Render(Font& font, Image* image, std::size_t x, std::size_t y, const FontSize& size, const Colour& colour) // x is advance, y is baseline
    {
        // Offset Calculated for Undertext
        int xOffset = 0;
        if (m_Underscript != nullptr)
        {
            xOffset = (m_Underscript->GetWidth(font, FontSize::SCRIPT) - GetTextWidth(font, size)) / 2;
        }

        // First Glyph
        Glyph* glyph = GetGlyph(font, m_Text[0], size);
        image->Draw(x + std::max(0, xOffset), y - glyph->BearingY, glyph->Width, glyph->Height, glyph->Data, colour);
        int advance = glyph->Advance - glyph->BearingX;
        delete glyph;

        // Subsequent Glyphs
        for (std::size_t i = 1; i < m_Text.length(); ++i)
        {
            glyph = GetGlyph(font, m_Text[i], size);
            image->Draw(x + advance + glyph->BearingX + std::max(0, xOffset), y - glyph->BearingY, glyph->Width, glyph->Height, glyph->Data, colour);
            advance += glyph->Advance;
            delete glyph;
        }

        glyph = GetGlyph(font, m_Text[m_Text.length() - 1], size);
        advance -= glyph->Advance - glyph->Width - glyph->BearingX;
        delete glyph;

        // Text Decorations
        if (m_Superscript != nullptr)
            m_Superscript->Render(font, image, x + advance + font.GetSuperscriptSpacing(size) + std::max(0, xOffset), y - font.GetSuperscriptElevation(size), FontSize::SCRIPT, colour);

        if (m_Subscript != nullptr)
        {
            if (m_Italics)
            {
                m_Subscript->Render(font, image, x + advance + (int)std::round((float)font.GetSuperscriptSpacing(size) * 0.5f) + std::max(0, xOffset), y + font.GetSuperscriptElevation(size), FontSize::SCRIPT, colour);
            }
            else
            {
                m_Subscript->Render(font, image, x + advance + font.GetSuperscriptSpacing(size) + std::max(0, xOffset), y + font.GetSuperscriptElevation(size), FontSize::SCRIPT, colour);
            }
        }

        if (m_Underscript != nullptr)
        {
            m_Underscript->Render(font, image, x + std::abs(std::min(0, xOffset)), y + (font.GetMeanLine(FontSize::SCRIPT)) * 2, FontSize::SCRIPT, colour);
        }
    }

    void Text::Print(int indent)
    {
        std::string message = "";

        for (int i = 0; i < indent; ++i)
        {
            message += " ";
        }

        std::cout << message + " - Text: " + m_Text << std::endl;
    }
}