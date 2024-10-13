#ifndef MATHSCRIPT_RENDERING_FONT_H_
#define MATHSCRIPT_RENDERING_FONT_H_

#include <ft2build.h>
#include FT_FREETYPE_H

#include <cstdint>
#include <iostream>

#include "MathScript/Rendering/FontSize.h"
#include "MathScript/Rendering/Colour.h"

namespace MathScript
{
    class Glyph
    {
    public:
        std::uint32_t Width, Height;
        std::uint8_t* Data;
        std::int32_t BearingX, BearingY;
        std::int32_t Advance;

        inline Glyph(std::uint32_t width, std::uint32_t height, std::uint32_t bearingX, std::uint32_t bearingY, std::uint32_t advance) 
            : Width(width), Height(height), BearingX(bearingX), BearingY(bearingY), Advance(advance), Data(nullptr) { }
        inline ~Glyph() { if (Data != nullptr) delete[] Data; }
    };

    class Font
    {
    private:
        static const float BIG_OPERATOR_SCALE; 
        static const float SCRIPT_SCALE; 

        FT_Library m_Library;

        FT_Face m_RegularFontFace;
        FT_Face m_ItalicsFontFace;

        int m_Size;

        int m_SuperscriptElevation, m_ScriptSuperscriptElevation;
        int m_SuperscriptSpacing, m_ScriptSuperscriptSpacing;
        int m_MeanLine, m_ScriptMeanLine;
        int m_VinculumHeight, m_ScriptVinculumHeight;
        int m_VinculumSpacing, m_ScriptVinculumSpacing;

        void LoadFace(const std::string& path, int variant, FT_Face* face);
        void SetFaceSize(FT_Face& face, int newSize);

    public:
        Font(int size);

        Glyph* GetGlyph(std::uint32_t asciiCode, const FontSize& size = FontSize::REGULAR);
        Glyph* GetItalicGlyph(std::uint32_t asciiCode, const FontSize& size = FontSize::REGULAR);

        int GetMeanLine(const FontSize& size) const noexcept;
        int GetSuperscriptElevation(const FontSize& size) const noexcept;
        int GetSuperscriptSpacing(const FontSize& size) const noexcept;
        int GetVinculumHeight(const FontSize& size) const noexcept;
        int GetVinculumSpacing(const FontSize& size) const noexcept;
    };
}

#endif