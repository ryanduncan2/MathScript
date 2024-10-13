#include "MathScript/Rendering/Expressions/Sigma.h"

namespace MathScript
{
    Sigma::Sigma(ExpressionStructure* argument, ExpressionStructure* upperBound, ExpressionStructure* lowerBound)
        : ExpressionStructure(), 
        m_Argument(argument),
        m_UpperBound(upperBound),
        m_LowerBound(lowerBound)
    {
    }

    Sigma::~Sigma()
    {
        delete m_Argument;
        delete m_UpperBound;
        delete m_LowerBound;
    }

    int Sigma::GetWidth(Font& font, const FontSize& size)
    {
        Glyph* sum = font.GetGlyph(SUM_CODE, FontSize::BIG);
        int argument = m_Argument->GetWidth(font, size);

        int upperBoundLeftOverhang = (m_UpperBound->GetWidth(font, FontSize::SCRIPT) - (int)sum->Width) / 2;
        int upperBoundRightOverhang = upperBoundLeftOverhang + std::abs(m_UpperBound->GetRightBearingX(font, FontSize::SCRIPT)) - (sum->Advance - sum->Width - sum->BearingX) - argument;
        int lowerBoundLeftOverhang = (m_LowerBound->GetWidth(font, FontSize::SCRIPT) - (int)sum->Width) / 2;
        int lowerBoundRightOverhang = lowerBoundLeftOverhang + std::abs(m_LowerBound->GetRightBearingX(font, FontSize::SCRIPT)) - (sum->Advance - sum->Width - sum->BearingX) - argument;

        int width = std::max(std::max(upperBoundLeftOverhang, lowerBoundLeftOverhang), 0); // Added largest left overhang.
        width += sum->Advance - sum->BearingX;                                             // Added integral width + advance.
        width += argument;                                                                 // Added integrand width.
        width += std::max(std::max(upperBoundRightOverhang, lowerBoundRightOverhang), 0);  // Added largest right overhang.

        delete sum;

        return width;
    }

    int Sigma::GetHeight(Font& font, const FontSize& size)
    {
        Glyph* sum = font.GetGlyph(SUM_CODE, FontSize::BIG);
        int height = (sum->Height / 2) + font.GetMeanLine(size) + m_UpperBound->GetHeight(font, FontSize::SCRIPT) + m_UpperBound->GetDepth(font, FontSize::SCRIPT);
        delete sum;
        return height;
    }

    int Sigma::GetDepth(Font& font, const FontSize& size)
    {
        Glyph* sum = font.GetGlyph(SUM_CODE, FontSize::BIG);
        int depth = (sum->Height / 2) + m_LowerBound->GetHeight(font, FontSize::SCRIPT) + m_LowerBound->GetDepth(font, FontSize::SCRIPT);
        delete sum;
        return depth;
    }

    int Sigma::GetBearingX(Font& font, const FontSize& size)
    {
        Glyph* sum = font.GetGlyph(SUM_CODE, FontSize::BIG);

        int upperBoundLeftOverhang = (m_UpperBound->GetWidth(font, FontSize::SCRIPT) - (int)sum->Width) / 2;
        int lowerBoundLeftOverhang = (m_LowerBound->GetWidth(font, FontSize::SCRIPT) - (int)sum->Width) / 2;
        int bearingX = std::max(std::max(upperBoundLeftOverhang + m_UpperBound->GetBearingX(font, FontSize::SCRIPT), lowerBoundLeftOverhang + m_LowerBound->GetBearingX(font, FontSize::SCRIPT)), sum->BearingX);

        delete sum;

        return bearingX;
    }

    int Sigma::GetRightBearingX(Font& font, const FontSize& size)
    {
        return m_Argument->GetRightBearingX(font, size);
    }

    void Sigma::Render(Font& font, Image* image, std::size_t x, std::size_t y, const FontSize& size, const Colour& colour)
    {
        Glyph* sum = font.GetGlyph(SUM_CODE, FontSize::BIG);
        int argument = m_Argument->GetWidth(font, size);

        int upperBoundLeftOverhang = (m_UpperBound->GetWidth(font, FontSize::SCRIPT) - (int)sum->Width) / 2;
        int upperBoundRightOverhang = upperBoundLeftOverhang - sum->Advance - argument;
        int lowerBoundLeftOverhang = (m_LowerBound->GetWidth(font, FontSize::SCRIPT) - (int)sum->Width) / 2;
        int lowerBoundRightOverhang = lowerBoundLeftOverhang - sum->Advance - argument;

        int sumXOffset = std::max(std::max(upperBoundLeftOverhang, lowerBoundLeftOverhang), 0);
        int upperBoundBaseline = y - (sum->Height / 2) - font.GetMeanLine(size) - m_UpperBound->GetDepth(font, FontSize::SCRIPT);
        int lowerBoundBaseline = y + (sum->Height / 2) + m_LowerBound->GetHeight(font, FontSize::SCRIPT);

        image->Draw(x + sumXOffset, y - (sum->Height / 2) - (font.GetMeanLine(size) / 2), sum->Width, sum->Height, sum->Data, colour);

        m_Argument->Render(font, image, x + std::max(std::max(upperBoundLeftOverhang, lowerBoundLeftOverhang), 0) + sum->Advance - sum->BearingX, y, FontSize::REGULAR, colour);
        m_UpperBound->Render(font, image, x + sumXOffset + (((int)sum->Width - m_UpperBound->GetWidth(font, FontSize::SCRIPT)) / 2), upperBoundBaseline, FontSize::SCRIPT, colour);
        m_LowerBound->Render(font, image, x + sumXOffset + (((int)sum->Width - m_LowerBound->GetWidth(font, FontSize::SCRIPT)) / 2), lowerBoundBaseline, FontSize::SCRIPT, colour);
    }

    void Sigma::Print(int indent)
    {
        std::string message = "";

        for (int i = 0; i < indent; ++i)
        {
            message += " ";
        }

        std::cout << message + " - Sum: " << std::endl;
        
        m_UpperBound->Print(indent + 1);
        m_LowerBound->Print(indent + 1);
        m_Argument->Print(indent + 1);
    }
}