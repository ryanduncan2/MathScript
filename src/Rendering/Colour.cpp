#include "MathScript/Rendering/Colour.h"

#include <iostream>
#include <string>

namespace MathScript
{
    void Colour::Add(const Colour& colour, int opacity)
    {
        float opacityPercent = (float)opacity / 255.0f;

        Red = (colour.Red * opacityPercent) + ((1 - opacityPercent) * Red);
        Green = (colour.Green * opacityPercent) + ((1 - opacityPercent) * Green);
        Blue = (colour.Blue * opacityPercent) + ((1 - opacityPercent) * Blue);





        // Red = std::min((Red + colour.Red) / 2, 255);
        // Blue = std::min((Blue + colour.Blue) / 2, 255);
        // Green = std::min((Green + colour.Green) / 2, 255);

        // std::cout << "===== STARTING ADDITION =====" << std::endl;

        // Colour temp(Red, Green, Blue); 

        // float foregroundAlphaRatio = 1;
        // float backgroundAlphaRatio = (255.0f - (float)opacity) / 255.0f;

        // std::cout << "Before: Colour[R: " + std::to_string(Red) + ", G: " + std::to_string(Green) + ", B: " + std::to_string(Blue) + "]" << std::endl;
        // std::cout << "+ Colour[R: " + std::to_string(colour.Red) + ", G: " + std::to_string(colour.Green) + ", B: " + std::to_string(colour.Blue) + "]" << std::endl;
        // std::cout << "Opacity: " + std::to_string(opacity) << std::endl;

        // Red = colour.Red + ((float)temp.Red * backgroundAlphaRatio);
        // Green = colour.Green + ((float)temp.Green * backgroundAlphaRatio);
        // Blue = colour.Blue + ((float)temp.Blue * backgroundAlphaRatio);

        // std::cout << "After: Colour[R: " + std::to_string(Red) + ", G: " + std::to_string(Green) + ", B: " + std::to_string(Blue) + "]" << std::endl;
    }
}