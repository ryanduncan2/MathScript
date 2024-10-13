#ifndef MATHSCRIPT_RENDERING_EXPRESSIONS_CHAIN_H_
#define MATHSCRIPT_RENDERING_EXPRESSIONS_CHAIN_H_

#include <vector>

#include "MathScript/Rendering/ExpressionStructure.h"

namespace MathScript
{
    class Chain : public ExpressionStructure
    {
    private:
        std::vector<ExpressionStructure*> m_ChainContents;

    public:
        Chain(const std::vector<ExpressionStructure*>& contents);
        virtual ~Chain();

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