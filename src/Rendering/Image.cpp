#include "MathScript/Rendering/Image.h"

#include <string>
#include <iostream>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace MathScript
{
    Image::Image(const std::size_t width, const std::size_t height, const Colour& backgroundColour)
        : m_Width(width),
          m_Height(height),
          m_Data(new Colour[m_Width * m_Height])
    {
        for (std::size_t i = 0; i < m_Width * m_Height; ++i)
        {
            m_Data[i] = backgroundColour;
        }
    }

    Image::~Image()
    {
        delete[] m_Data;
    }

    std::uint8_t* Image::GetRawData() const noexcept
    {
        std::uint8_t* rawData = new std::uint8_t[m_Width * m_Height * 3];

        for (std::size_t y = 0; y < m_Height; ++y)
        {
            for (std::size_t x = 0; x < m_Width; ++x)
            {
                for (std::size_t i = 0; i < 3; ++i)
                {
                    rawData[(x + (y * m_Width)) * 3] = m_Data[(x + (y * m_Width))].Red;
                    rawData[(x + (y * m_Width)) * 3 + 1] = m_Data[(x + (y * m_Width))].Green;
                    rawData[(x + (y * m_Width)) * 3 + 2] = m_Data[(x + (y * m_Width))].Blue;
                }
            }
        }

        return rawData;
    }

    void Image::Draw(const std::size_t x, const std::size_t y, const std::size_t width, const std::size_t height, const std::uint8_t* data, const Colour& colour)
    {
        if (x + width > m_Width || y + height > m_Height)
        {
            // std::cout << "Unable to draw image." << std::endl;
            // std::cout << "Image[Width: " + std::to_string(m_Width) + ", Height: " + std::to_string(m_Height) + "]" << std::endl;
            // std::cout << "Glyph[X: " + std::to_string(x) + ", Y: " + std::to_string(y) + ", Width: " + std::to_string(width) + ", Height: " + std::to_string(height) + "]" << std::endl;
            return;
        }
        // else
        // {
        //     std::cout << "Able to draw image." << std::endl;
        //     std::cout << "Image[Width: " + std::to_string(m_Width) + ", Height: " + std::to_string(m_Height) + "]" << std::endl;
        //     std::cout << "Glyph[X: " + std::to_string(x) + ", Y: " + std::to_string(y) + ", Width: " + std::to_string(width) + ", Height: " + std::to_string(height) + "]" << std::endl;
        // }

        for (std::size_t innerY = 0; innerY < height; ++innerY)
        {
            for (std::size_t innerX = 0; innerX < width; ++innerX)
            {
                int imageIndex = x + (y * m_Width) + innerX + (innerY * m_Width);
                int index = innerX + (innerY * width);
                m_Data[imageIndex].Add(colour, data[index]);
            }
        }
    }

    void Image::DrawRectangle(const std::size_t x, const std::size_t y, const std::size_t width, const std::size_t height, const Colour& colour)
    {
        if (x + width > m_Width || y + height > m_Height)
        {
            return;
        }

        for (std::size_t innerY = 0; innerY < height; ++innerY)
        {
            for (std::size_t innerX = 0; innerX < width; ++innerX)
            {
                std::size_t index = x + (y * m_Width) + innerX + (innerY * m_Width);
                m_Data[index] = colour;
            }
        }
    }
}