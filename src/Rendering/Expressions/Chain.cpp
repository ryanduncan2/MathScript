#include "MathScript/Rendering/Expressions/Chain.h"
#include "MathScript/Rendering/Expressions/Text.h"
#include "MathScript/Rendering/Expressions/Fraction.h"

namespace MathScript
{
    Chain::Chain(const std::vector<ExpressionStructure*>& contents)
        : ExpressionStructure(), 
        m_ChainContents(contents)
    {
    }

    Chain::~Chain()
    {
        for (std::size_t i = 0; i < m_ChainContents.size(); ++i)
        {
            delete m_ChainContents[i];
        }
    }

    int Chain::GetWidth(Font& font, const FontSize& size)
    {
        int width = 0;

        for (std::size_t i = 0; i < m_ChainContents.size() - 1; ++i)
        {
            width += m_ChainContents[i]->GetWidth(font, size) + m_ChainContents[i]->GetRightBearingX(font, size);
        }

        return width + m_ChainContents[m_ChainContents.size() - 1]->GetWidth(font, size);
    }

    int Chain::GetHeight(Font& font, const FontSize& size)
    {
        int height = 0;

        for (std::size_t i = 0; i < m_ChainContents.size(); ++i)
        {
            if (m_ChainContents[i]->GetHeight(font, size) > height)
            {
                height = m_ChainContents[i]->GetHeight(font, size);
            }
        }

        return height;
    }

    int Chain::GetDepth(Font& font, const FontSize& size)
    {
        int depth = 0;

        for (std::size_t i = 0; i < m_ChainContents.size(); ++i)
        {
            if (m_ChainContents[i]->GetDepth(font, size) > depth)
            {
                depth = m_ChainContents[i]->GetDepth(font, size);
            }
        }

        return depth;
    }

    int Chain::GetBearingX(Font& font, const FontSize& size)
    {
        return m_ChainContents[0]->GetBearingX(font, size);
    }

    int Chain::GetRightBearingX(Font& font, const FontSize& size)
    {
        return m_ChainContents[m_ChainContents.size() - 1]->GetRightBearingX(font, size);
    }

    void Chain::Render(Font& font, Image* image, std::size_t x, std::size_t y, const FontSize& size, const Colour& colour) // x is advance, y is baseline
    {
        int advance = 0;

        for (std::size_t i = 0; i < m_ChainContents.size(); ++i)
        {
            m_ChainContents[i]->Render(font, image, x + advance, y, size, colour);
            advance += m_ChainContents[i]->GetWidth(font, size) + m_ChainContents[i]->GetRightBearingX(font, size);
        }
    }

    void Chain::Print(int indent)
    {
        std::cout << "printing chain" << std::endl;

        std::string message = "";

        for (int i = 0; i < indent; ++i)
        {
            message += " ";
        }

        std::cout << message + " - Chain: " << std::endl;
        
        for (int i = 0; i < m_ChainContents.size(); ++i)
        {
            m_ChainContents[i]->Print(indent + 1);
        }
    }
}