#include "MathScript/Rendering/Expressions/Integral.h"

namespace MathScript
{
    Integral::Integral(ExpressionStructure* integrand, ExpressionStructure* upperBound, ExpressionStructure* lowerBound)
        : ExpressionStructure(), 
        m_Integrand(integrand),
        m_UpperBound(upperBound),
        m_LowerBound(lowerBound)
    {
    }

    Integral::~Integral()
    {
        delete m_Integrand;
        delete m_UpperBound;
        delete m_LowerBound;
    }

    int Integral::GetWidth(Font& font, const FontSize& size)
    {
        Glyph* integral = font.GetGlyph(INTEGRAL_CODE, FontSize::BIG);
        int integrand = m_Integrand->GetWidth(font, size);

        int upperBoundRightOverhang = (m_UpperBound->GetWidth(font, FontSize::SCRIPT) / 2) - (integral->Width / 4) - (integral->Advance - integral->Width - integral->BearingX) - integrand;
        int upperBoundLeftOverhang = (m_UpperBound->GetWidth(font, FontSize::SCRIPT) / 2) - ((3 * integral->Width) / 4);
        int lowerBoundRightOverhang = (m_LowerBound->GetWidth(font, FontSize::SCRIPT) / 2) - ((2 * integral->Width) / 3) - (integral->Advance - integral->Width - integral->BearingX) - integrand;
        int lowerBoundLeftOverhang = (m_LowerBound->GetWidth(font, FontSize::SCRIPT) / 2) - (integral->Width / 3);

        int width = std::max(std::max(upperBoundLeftOverhang, lowerBoundLeftOverhang), 0); // Added largest left overhang.
        width += integral->Advance - integral->BearingX;                                   // Added integral width.
        width += integrand;                                                                // Added integrand width.
        width += std::max(std::max(upperBoundRightOverhang, lowerBoundRightOverhang), 0);  // Added largest right overhang.

        delete integral;

        return width;
    }

    int Integral::GetHeight(Font& font, const FontSize& size)
    {
        Glyph* integral = font.GetGlyph(INTEGRAL_CODE, FontSize::BIG);
        int height = (integral->Height / 2) + font.GetMeanLine(size) + m_UpperBound->GetHeight(font, FontSize::SCRIPT) + m_UpperBound->GetDepth(font, FontSize::SCRIPT);
        delete integral;
        return height;
    }

    int Integral::GetDepth(Font& font, const FontSize& size)
    {
        Glyph* integral = font.GetGlyph(INTEGRAL_CODE, FontSize::BIG);
        int depth = (integral->Height / 2) + m_LowerBound->GetHeight(font, FontSize::SCRIPT) + m_LowerBound->GetDepth(font, FontSize::SCRIPT);
        delete integral;
        return depth;
    }

    int Integral::GetBearingX(Font& font, const FontSize& size)
    {
        Glyph* integral = font.GetGlyph(INTEGRAL_CODE, FontSize::BIG);

        int upperBoundLeftOverhang = (m_UpperBound->GetWidth(font, FontSize::SCRIPT) / 2) - ((2 * integral->Width) / 3);
        int lowerBoundLeftOverhang = (m_LowerBound->GetWidth(font, FontSize::SCRIPT) / 2) - (integral->Width / 3);

        int bearingX = std::max(upperBoundLeftOverhang + m_UpperBound->GetBearingX(font, FontSize::SCRIPT), lowerBoundLeftOverhang + m_LowerBound->GetBearingX(font, FontSize::SCRIPT));

        delete integral;

        return bearingX;
    }

    int Integral::GetRightBearingX(Font& font, const FontSize& size)
    {
        return m_Integrand->GetRightBearingX(font, size);
    }

    void Integral::Render(Font& font, Image* image, std::size_t x, std::size_t y, const FontSize& size, const Colour& colour)
    {
        Glyph* integral = font.GetGlyph(INTEGRAL_CODE, FontSize::BIG);
        int integrand = m_Integrand->GetWidth(font, size);

        int upperBoundRightOverhang = (m_UpperBound->GetWidth(font, FontSize::SCRIPT) / 2) - (integral->Width / 4) - (integral->Advance - integral->Width - integral->BearingX) - integrand;
        int upperBoundLeftOverhang = (m_UpperBound->GetWidth(font, FontSize::SCRIPT) / 2) - ((3 * integral->Width) / 4);
        int lowerBoundRightOverhang = (m_LowerBound->GetWidth(font, FontSize::SCRIPT) / 2) - ((2 * integral->Width) / 3) - (integral->Advance - integral->Width - integral->BearingX) - integrand;
        int lowerBoundLeftOverhang = (m_LowerBound->GetWidth(font, FontSize::SCRIPT) / 2) - (integral->Width / 3);

        int integralXOffset = std::max(std::max(upperBoundLeftOverhang, lowerBoundLeftOverhang), 0);
        int upperBoundBaseline = y - (integral->Height / 2) - font.GetMeanLine(size) - m_UpperBound->GetDepth(font, FontSize::SCRIPT);
        int lowerBoundBaseline = y + (integral->Height / 2) + m_LowerBound->GetHeight(font, FontSize::SCRIPT);

        image->Draw(x + integralXOffset, y - (integral->Height / 2) - (font.GetMeanLine(size) / 2), integral->Width, integral->Height, integral->Data, colour);

        m_Integrand->Render(font, image, x + std::max(std::max(upperBoundLeftOverhang, lowerBoundLeftOverhang), 0) + integral->Advance - integral->BearingX, y, FontSize::REGULAR, colour);
        m_UpperBound->Render(font, image, x + std::max(0, lowerBoundLeftOverhang - upperBoundLeftOverhang), upperBoundBaseline, FontSize::SCRIPT, colour);
        m_LowerBound->Render(font, image, x + std::max(0, upperBoundLeftOverhang -lowerBoundLeftOverhang), lowerBoundBaseline, FontSize::SCRIPT, colour);
    }

    void Integral::Print(int indent)
    {
        std::string message = "";

        for (int i = 0; i < indent; ++i)
        {
            message += " ";
        }

        std::cout << message + " - Integral: " << std::endl;
        
        m_UpperBound->Print(indent + 1);
        m_LowerBound->Print(indent + 1);
        m_Integrand->Print(indent + 1);
    }
}