#include "MathScript/Functions/CommonFunctions.h"
#include "MathScript/ScriptEngine.h"
#include "MathScript/Calculator.h"
#include "MathScript/Range.h"
#include "MathScript/Rendering/Image.h"
#include "MathScript/Rendering/Font.h"
#include "MathScript/Rendering/Expression.h"
#include "MathScript/Rendering/Expressions/Text.h"

#include <iostream>
#include <fstream>
#include <Windows.h>
#include <cmath>

#define print(x) std::cout << x << std::endl

int main(int argc, char* argv[])
{
    MathScript::Expression expr("f(x) = \\sum{\\frac{\\exp{x,2} + 2x,-7\\exp{x,3} + \\sub{a,n}} dx, \\inf, -\\pi}");
    expr.Print();
    MathScript::Image* rawImage = expr.Render(25, MathScript::Colour(240, 240, 240), MathScript::Colour(31, 31, 34), 50, 50);

    std::int32_t rowSize = rawImage->GetWidth() * 3;
    std::int32_t paddedRowSize = std::ceil((24.0f * (float)rawImage->GetWidth()) / 32.0f) * 4;
    std::int32_t paddingCount = paddedRowSize - rowSize;
    std::int32_t imageSize = paddedRowSize * 3 * rawImage->GetHeight();

    BITMAPFILEHEADER bf = { };
    bf.bfType = 'B' + ('M' << 8);
    bf.bfSize = sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER) + imageSize;
    bf.bfOffBits = sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER);

    BITMAPINFOHEADER bi = { };
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biBitCount = 24;
    bi.biClrImportant = 0;
    bi.biClrUsed = 0;
    bi.biCompression = 0;
    bi.biWidth = rawImage->GetWidth();
    bi.biHeight = -rawImage->GetHeight();
    bi.biPlanes = 1;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 2835;
    bi.biYPelsPerMeter = 2835;

    // Constructing Pixel Array

    std::uint32_t bufferSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + imageSize;
    std::uint8_t* buffer = new std::uint8_t[bufferSize];
    memcpy(buffer, &bf, sizeof(BITMAPFILEHEADER));
    memcpy(buffer + sizeof(BITMAPFILEHEADER), &bi, sizeof(BITMAPINFOHEADER));

    std::uint32_t index = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    for (std::size_t i = 0; i < rawImage->GetHeight(); ++i)
    {
        memcpy(buffer + index, rawImage->GetData() + (i * rawImage->GetWidth()), rawImage->GetWidth() * 3);
        memset(buffer + index + rawImage->GetWidth() * 3, 0, paddingCount);
        index += (rawImage->GetWidth() * 3) + paddingCount;
    }

    std::ofstream file;
    file.open("test.bmp", std::ios::out | std::ios::app | std::ios::binary);
    file.write((const char*)buffer, sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + imageSize);
    file.close();

    delete rawImage;
    print("done");

    return 0;
}