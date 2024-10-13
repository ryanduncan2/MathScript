#include "MathScript/Rendering/Font.h"

#include <string>
#include <iostream>
#include <cmath>

namespace MathScript
{
    const float Font::BIG_OPERATOR_SCALE = 3.0f;
    const float Font::SCRIPT_SCALE = 0.75f;

    Font::Font(int size)
        : m_Size(size)
    {
        int error = FT_Init_FreeType(&m_Library);
        if (error)
        {
            throw std::string("Failed to initialise library.");
        }

        LoadFace("cambria.ttc", 1, &m_RegularFontFace);
        SetFaceSize(m_RegularFontFace, size);

        LoadFace("cmunti.ttf", 0, &m_ItalicsFontFace);
        SetFaceSize(m_ItalicsFontFace, size);

        // Calculating Mean Lines
        Glyph* glyph = GetGlyph('x');
        m_MeanLine = glyph->BearingY;
        delete glyph;

        glyph = GetGlyph('x', FontSize::SCRIPT);
        m_ScriptMeanLine = glyph->BearingY;
        delete glyph;

        // Calculating Superscript Elevations
        m_SuperscriptElevation = (int)std::floor((float)m_MeanLine * 0.75f);
        m_ScriptSuperscriptElevation = (int)std::floor((float)m_ScriptMeanLine * 0.75f);

        // Calculating Superscript Spacing
        m_SuperscriptSpacing = (int)std::floor((float)m_MeanLine * 0.25f);
        m_ScriptSuperscriptSpacing = (int)std::floor((float)m_ScriptMeanLine * 0.25f);

        // Calculating Vinculum Heights
        glyph = GetGlyph('-');
        m_VinculumHeight = std::max((int)glyph->Height / 2, 1);
        delete glyph;

        glyph = GetGlyph('-', FontSize::SCRIPT);
        m_ScriptVinculumHeight = std::max((int)glyph->Height / 2, 1);

        delete glyph;

        // Calculating Vinculum Spacings
        m_VinculumSpacing = GetMeanLine(FontSize::REGULAR) / 2;
        m_ScriptVinculumSpacing = GetMeanLine(FontSize::SCRIPT) / 4;
    }

    void Font::LoadFace(const std::string& path, int variant, FT_Face* face)
    {
        FT_Error error = FT_New_Face(m_Library, path.c_str(), variant, face);
        if (error == FT_Err_Unknown_File_Format)
        {
            throw std::string("Font format unsupported.");
        }
        else if (error)
        {
            throw std::string("Failed to load font.");
        }
    }

    void Font::SetFaceSize(FT_Face& face, int newSize)
    {
        for (int i = face->num_fixed_sizes - 1; i >= 0; --i)
        {
            if (newSize == (face->available_sizes[i].size / 64))
            {
                newSize--;
            }
        }

        FT_Set_Pixel_Sizes(face, 0, newSize);
    }

    Glyph* Font::GetGlyph(std::uint32_t asciiCode, const FontSize& size)
    {
        switch (size)
        {
            case FontSize::REGULAR: SetFaceSize(m_RegularFontFace, m_Size); break;
            case FontSize::BIG: SetFaceSize(m_RegularFontFace, (int)std::floor(m_Size * BIG_OPERATOR_SCALE)); break;
            case FontSize::SCRIPT: SetFaceSize(m_RegularFontFace, (int)std::floor(m_Size * SCRIPT_SCALE)); break;
        }

        FT_UInt index = FT_Get_Char_Index(m_RegularFontFace, asciiCode);
        int error = FT_Load_Glyph(m_RegularFontFace, index, FT_LOAD_DEFAULT);

        if (error)
        {
            std::cout << "Fail 1" << std::endl;
            throw std::string("Fail 1");
        }

        error = FT_Render_Glyph(m_RegularFontFace->glyph, FT_RENDER_MODE_NORMAL);

        if (error)
        {
            std::cout << "Fail 2" << std::endl;
            throw std::string("Fail 2");
        }

        Glyph* glyph = new Glyph(m_RegularFontFace->glyph->bitmap.width, m_RegularFontFace->glyph->bitmap.rows, m_RegularFontFace->glyph->bitmap_left, m_RegularFontFace->glyph->bitmap_top, (std::int32_t)m_RegularFontFace->glyph->advance.x / 64);
        glyph->Data = new std::uint8_t[glyph->Width * glyph->Height];

        for (std::uint32_t y = 0; y < glyph->Height; ++y)
        {
            for (std::uint32_t x = 0; x < glyph->Width; ++x)
            {
                int i = x + (glyph->Width * y);
                glyph->Data[i] = m_RegularFontFace->glyph->bitmap.buffer[i];
            }
        }

        return glyph;
    }

    Glyph* Font::GetItalicGlyph(std::uint32_t asciiCode, const FontSize& size)
    {
        switch (size)
        {
            case FontSize::REGULAR: SetFaceSize(m_ItalicsFontFace, m_Size); break;
            case FontSize::BIG: SetFaceSize(m_ItalicsFontFace, (int)std::floor(m_Size * BIG_OPERATOR_SCALE)); break;
            case FontSize::SCRIPT: SetFaceSize(m_ItalicsFontFace, (int)std::floor(m_Size * SCRIPT_SCALE)); break;
        }

        FT_UInt index = FT_Get_Char_Index(m_ItalicsFontFace, asciiCode);
        int error = FT_Load_Glyph(m_ItalicsFontFace, index, FT_LOAD_DEFAULT);

        if (error)
        {
            std::cout << "Fail 1" << std::endl;
            throw std::string("Fail 1");
        }

        error = FT_Render_Glyph(m_ItalicsFontFace->glyph, FT_RENDER_MODE_NORMAL);

        if (error)
        {
            std::cout << "Fail 2" << std::endl;
            throw std::string("Fail 2");
        }

        Glyph* glyph = new Glyph(m_ItalicsFontFace->glyph->bitmap.width, m_ItalicsFontFace->glyph->bitmap.rows, m_ItalicsFontFace->glyph->bitmap_left, m_ItalicsFontFace->glyph->bitmap_top, (std::int32_t)m_ItalicsFontFace->glyph->advance.x / 64);
        glyph->Data = new std::uint8_t[glyph->Width * glyph->Height];

        for (std::uint32_t y = 0; y < glyph->Height; ++y)
        {
            for (std::uint32_t x = 0; x < glyph->Width; ++x)
            {
                int i = x + (glyph->Width * y);
                glyph->Data[i] = m_ItalicsFontFace->glyph->bitmap.buffer[i];
            }
        }

        return glyph;
    }

    int Font::GetSuperscriptElevation(const FontSize& size) const noexcept
    {
        switch(size)
        {
            case FontSize::SCRIPT: return m_ScriptSuperscriptElevation;
            default: return m_SuperscriptElevation;
        }
    }

    int Font::GetSuperscriptSpacing(const FontSize& size) const noexcept
    {
        switch(size)
        {
            case FontSize::SCRIPT: return m_ScriptSuperscriptSpacing;
            default: return m_SuperscriptSpacing;
        }
    }

    int Font::GetMeanLine(const FontSize& size) const noexcept
    {
        switch(size)
        {
            case FontSize::SCRIPT: return m_ScriptMeanLine;
            default: return m_MeanLine;
        }
    }

    int Font::GetVinculumHeight(const FontSize& size) const noexcept
    {
        switch(size)
        {
            case FontSize::SCRIPT: return m_ScriptVinculumHeight;
            default: return m_VinculumHeight;
        }
    }

    int Font::GetVinculumSpacing(const FontSize& size) const noexcept
    {
        switch(size)
        {
            case FontSize::SCRIPT: return m_ScriptVinculumSpacing;
            default: return m_VinculumSpacing;
        }
    }
}