#include "MathScript/Rendering/Expressions/Fraction.h"

#include <cmath>

namespace MathScript
{
    Fraction::Fraction(ExpressionStructure* numerator, ExpressionStructure* denominator)
        : ExpressionStructure(), 
        m_Numerator(numerator),
        m_Denominator(denominator)
    {
    }

    Fraction::~Fraction()
    {
        delete m_Numerator;
        delete m_Denominator;
    }

    int Fraction::GetWidth(Font& font, const FontSize& size)
    {
        int width = std::max(m_Numerator->GetWidth(font, size), m_Denominator->GetWidth(font, size));

        if (m_Superscript != nullptr)
        {
            width += font.GetSuperscriptSpacing(size);
            width += m_Superscript->GetWidth(font, FontSize::SCRIPT);
        }

        return width;
    }

    int Fraction::GetHeight(Font& font, const FontSize& size)
    {
        int height = m_Numerator->GetHeight(font, size) + (font.GetMeanLine(size) / 2) + font.GetVinculumSpacing(size);

        if (m_Superscript != nullptr)
        {
            height += m_Superscript->GetHeight(font, FontSize::SCRIPT) - (font.GetMeanLine(FontSize::SCRIPT) / 2);
        }

        return height;
    }

    int Fraction::GetDepth(Font& font, const FontSize& size)
    {
        return m_Denominator->GetHeight(font, size) + m_Denominator->GetDepth(font, size) - ((font.GetMeanLine(size) / 2) - font.GetVinculumSpacing(size));
    }

    int Fraction::GetBearingX(Font& font, const FontSize& size)
    {
        return std::max(m_Numerator->GetBearingX(font, size), m_Denominator->GetBearingX(font, size));
    }

    int Fraction::GetRightBearingX(Font& font, const FontSize& size)
    {
        int bearingX = std::max(m_Numerator->GetRightBearingX(font, size), m_Denominator->GetRightBearingX(font, size));

        if (m_Superscript != nullptr)
        {
            bearingX += font.GetSuperscriptSpacing(size);
            bearingX += m_Superscript->GetWidth(font, FontSize::SCRIPT);
        }

        return bearingX;
    }

    void Fraction::Render(Font& font, Image* image, std::size_t x, std::size_t y, const FontSize& size, const Colour& colour) // x is advance, y is baseline
    {
        int maxWidth = std::max(m_Numerator->GetWidth(font, size), m_Denominator->GetWidth(font, size));
        m_Numerator->Render(font, image, x + (maxWidth - m_Numerator->GetWidth(font, size)) / 2, y - (font.GetMeanLine(size) / 2) - font.GetVinculumSpacing(size), size, colour);
        m_Denominator->Render(font, image, x + (maxWidth - m_Denominator->GetWidth(font, size)) / 2, y - (font.GetMeanLine(size) / 2) + font.GetVinculumSpacing(size) + m_Denominator->GetHeight(font, size), size, colour);

        image->DrawRectangle(x, y - (font.GetMeanLine(size) / 2) - (font.GetVinculumHeight(size) / 2), maxWidth, font.GetVinculumHeight(size), colour);

        // Colour* data = image->GetData();

        // for (std::size_t innerY = 0; innerY < font.GetVinculumHeight(size); ++innerY)
        // {
        //     for (std::size_t innerX = 0; innerX < maxWidth; ++innerX)
        //     {
        //         int index = ((x + ((y - (font.GetMeanLine(size) / 2) - (font.GetVinculumHeight(size) / 2)) * image->GetWidth())) + (innerX + (innerY * image->GetWidth())));

        //         data[index] = Colour(255, 255, 255);

        //         // data[index] = 255;
        //         // data[index + 1] = 255;
        //         // data[index + 2] = 255;
        //     }
        // }

        if (m_Superscript != nullptr)
        {
            int scriptY = y - (font.GetMeanLine(size) / 2) - font.GetVinculumSpacing(size) - m_Numerator->GetHeight(font, size) + (font.GetMeanLine(FontSize::SCRIPT) / 2);
            //int scriptY = y - (font.GetMeanLine(size) / 2) - font.GetVinculumSpacing(size) - (m_Superscript->GetHeight(font, FontSize::SCRIPT) - font.GetMeanLine(FontSize::SCRIPT))

            m_Superscript->Render(font, image, x + maxWidth + font.GetSuperscriptSpacing(size), scriptY, FontSize::SCRIPT, colour);
        }
    }

    void Fraction::Print(int indent)
    {
        std::string message = "";

        for (int i = 0; i < indent; ++i)
        {
            message += " ";
        }

        std::cout << message + " - Fraction: " << std::endl;
        
        m_Numerator->Print(indent + 1);
        m_Denominator->Print(indent + 1);
    }
}