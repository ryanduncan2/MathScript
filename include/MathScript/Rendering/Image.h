#ifndef MATHSCRIPT_RENDERING_IMAGE_H_
#define MATHSCRIPT_RENDERING_IMAGE_H_

#include <cstddef>

#include "MathScript/Rendering/Colour.h"

namespace MathScript
{
    class Image
    {
    private:
        std::size_t m_Width, m_Height;
        Colour* m_Data;

    public:
        Image(const std::size_t width, const std::size_t height, const Colour& backgroundColour);
        ~Image();

        inline std::size_t GetWidth() const noexcept { return m_Width; }
        inline std::size_t GetHeight() const noexcept { return m_Height; }
        inline Colour* GetData() const noexcept { return m_Data; }
        std::uint8_t* GetRawData() const noexcept;
        
        void Draw(const std::size_t x, const std::size_t y, const std::size_t width, const std::size_t height, const std::uint8_t* data, const Colour& colour);
        void DrawRectangle(const std::size_t x, const std::size_t y, const std::size_t width, const std::size_t height, const Colour& colour);
    };
}

#endif