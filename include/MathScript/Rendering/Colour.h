#ifndef MATHSCRIPT_RENDERING_COLOUR_H_
#define MATHSCRIPT_RENDERING_COLOUR_H_

#include <cstdint>

namespace MathScript
{
    class Colour
    {
    public:
        std::uint8_t Red, Green, Blue;
        inline Colour() : Red(0), Green(0), Blue(0) { }
        inline Colour(std::uint8_t red, std::uint8_t green, std::uint8_t blue) : Red(red), Green(green), Blue(blue) { }

        void Add(const Colour& colour, int opacity);
    };
}

#endif