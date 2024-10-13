#include "MathScript/Rendering/Expression.h"

#include "MathScript/Rendering/Expressions/Text.h"
#include "MathScript/Rendering/Expressions/Chain.h"
#include "MathScript/Rendering/Expressions/Fraction.h"
#include "MathScript/Rendering/Expressions/Symbol.h"
#include "MathScript/Rendering/Expressions/Integral.h"
#include "MathScript/Rendering/Expressions/Sigma.h"

#define print(x) std::cout << x << std::endl

namespace MathScript
{
    Expression::Expression(const std::string& script)
    {
        m_Root = InterpretScript(script);
    }

    Image* Expression::Render(int fontSize, const Colour& foregroundColour, const Colour& backgroundColour, int xPadding, int yPadding)
    {
        Font font(fontSize);

        int imageWidth = m_Root->GetWidth(font, FontSize::REGULAR) + (xPadding * 2);
        int imageHeight = m_Root->GetHeight(font, FontSize::REGULAR) + m_Root->GetDepth(font, FontSize::REGULAR) + (yPadding * 2);
        Image* image = new Image(imageWidth, imageHeight, backgroundColour);

        m_Root->Render(font, image, xPadding, m_Root->GetHeight(font, FontSize::REGULAR) + yPadding, FontSize::REGULAR, foregroundColour);

        return image;
    }

    ExpressionStructure* Expression::InterpretScript(const std::string& script)
    {
        std::vector<ExpressionStructure*> structures;

        bool inMarkupZone = false;
        bool inCommand = false;
        int braceDepth = 0;
        std::size_t index = 0;

        for (std::size_t i = 0; i < script.length(); ++i)
        {
            if (inMarkupZone)
            {
                if (inCommand)
                {
                    if (script[i] == '}')
                    {
                        if (braceDepth > 0)
                        {
                            braceDepth--;
                        }
                        else
                        {
                            structures.push_back(DecodeCommand(script.substr(index, i - index + 1)));

                            inMarkupZone = false;
                            inCommand = false;
                            index = i + 1;
                        }
                    }
                    else if (script[i] == '{')
                    {
                        braceDepth++;
                    }
                }
                else if (script[i] == '{')
                {
                    inCommand = true;
                }
                else if (script[i] == ' ')
                {
                    structures.push_back(SelectSymbol(script.substr(index, i - index)));
                    
                    inMarkupZone = false;
                    index = i;
                }
                else if (i == script.length() - 1)
                {
                    structures.push_back(SelectSymbol(script.substr(index, i + 1)));
                }
            }
            else if (script[i] == '\\')
            {
                if (i > 0)
                {
                    std::string str = script.substr(index, i - index);
                    if (str.length() > 0)
                    {
                        structures.push_back(SelectCommand("text", { str }));
                    }
                }

                inMarkupZone = true;
                index = i + 1;
            }
            else if (i == script.length() - 1)
            {
                std::string str = script.substr(index, i + 1);
                if (str.length() > 0)
                {
                    structures.push_back(SelectCommand("text", { str }));
                }
            }
        }

        if (structures.size() > 1)
        {
            return new Chain(structures);
        }
        else
        {
            return structures[0];
        }
    }

    ExpressionStructure* Expression::InterpretText(const std::string& text)
    {
        std::vector<ExpressionStructure*> structures;

        std::size_t index = 0;
        for (std::size_t i = 0; i < text.length(); ++i)
        {
            // Converts hyphens to subtraction signs.
            if (text[i] == '-')
            {
                if (i != 0)
                {
                    structures.push_back(new Text(text.substr(index, i - index)));
                }
                
                structures.push_back(new Symbol(0x2212));
                index = i + 1;
            }
        }

        if (index < text.length())
        {
            structures.push_back(new Text(text.substr(index, text.length() - index)));
        }

        if (structures.size() == 1)
        {
            return structures[0];
        }

        return new Chain(structures);
    }

    ExpressionStructure* Expression::DecodeCommand(const std::string& command)
    {
        // Command in the form of, for example, frac{x, y}.

        std::string commandCode = "";
        for (std::size_t i = 0; i < command.length(); ++i)
        {
            if (command[i] == '{') // Indicates the start of arguments.
            {
                commandCode = command.substr(0, i);
                break;
            }
        }

        std::vector<std::string> params;
        int lastParamIndex = commandCode.length() + 1;
        int braceDepth = 0;
        for (std::size_t i = lastParamIndex; i < command.length(); ++i)
        {
            if ((command[i] == ',' || command[i] == '}') && braceDepth == 0) // Indicates the end of a parameter.
            {
                params.push_back(command.substr(lastParamIndex, i - lastParamIndex));
                lastParamIndex = i + 1;
            }
            else if (command[i] == '{')
            {
                braceDepth++;
            }
            else if (command[i] == '}')
            {
                braceDepth--;
            }
        }

        return SelectCommand(commandCode, params);
    }

    ExpressionStructure* Expression::SelectCommand(const std::string& commandCode, const std::vector<std::string>& params)
    {
        if (commandCode == "text") { return InterpretText(params[0]); } 
        else if (commandCode == "frac") { return new Fraction(InterpretScript(params[0]), InterpretScript(params[1])); }
        else if (commandCode == "int") { return new Integral(InterpretScript(params[0]), InterpretScript(params[1]), InterpretScript(params[2])); }
        else if (commandCode == "sum") { return new Sigma(InterpretScript(params[0]), InterpretScript(params[1]), InterpretScript(params[2])); }
        else if (commandCode == "exp") { auto s = InterpretScript(params[0]); s->SetSuperscript(InterpretScript(params[1])); return s; }
        else if (commandCode == "sub") { auto s = InterpretScript(params[0]); s->SetSubscript(InterpretScript(params[1])); return s; }
        else if (commandCode == "expsub") { auto s = InterpretScript(params[0]); s->SetSuperscript(InterpretScript(params[1])); s->SetSubscript(InterpretScript(params[2])); return s; }
        else if (commandCode == "fn") { return new Chain({ new Text(params[0], false), InterpretScript(" " + params[1]) }); }
        else if (commandCode == "under") { auto s = InterpretScript(params[0]); s->SetUnderscript(InterpretScript(params[1])); return s; }

        else if (commandCode == "sin") { return new Chain({ new Text("sin", false), InterpretScript(" " + params[0]) }); }
        else if (commandCode == "cos") { return new Chain({ new Text("cos", false), InterpretScript(" " + params[0]) }); }
        else if (commandCode == "tan") { return new Chain({ new Text("tan", false), InterpretScript(" " + params[0]) }); }
        else if (commandCode == "csc") { return new Chain({ new Text("csc", false), InterpretScript(" " + params[0]) }); }
        else if (commandCode == "sec") { return new Chain({ new Text("sec", false), InterpretScript(" " + params[0]) }); }
        else if (commandCode == "cot") { return new Chain({ new Text("cot", false), InterpretScript(" " + params[0]) }); }

        else if (commandCode == "lim")
        {
            auto s = new Text("lim", false);
            s->SetUnderscript(InterpretScript(params[0]));
            return new Chain({ s, InterpretScript(" " + params[1]) });
        }
    }

    ExpressionStructure* Expression::SelectSymbol(const std::string& symbolCode)
    {
        // Greek Lowercase
        if (symbolCode == "alpha") { return new Symbol(0x1D6FC); }
        else if (symbolCode == "beta") { return new Symbol(0x1D6FD); }
        else if (symbolCode == "gamma") { return new Symbol(0x1D6FE); }
        else if (symbolCode == "delta") { return new Symbol(0x1D6FF); }
        else if (symbolCode == "epsilon") { return new Symbol(0x1D700); }
        else if (symbolCode == "zeta") { return new Symbol(0x1D701); }
        else if (symbolCode == "eta") { return new Symbol(0x1D702); }
        else if (symbolCode == "theta") { return new Symbol(0x1D703); }
        else if (symbolCode == "iota") { return new Symbol(0x1D704); }
        else if (symbolCode == "kappa") { return new Symbol(0x1D705); }
        else if (symbolCode == "lamda") { return new Symbol(0x1D706); }
        else if (symbolCode == "mu") { return new Symbol(0x1D707); }
        else if (symbolCode == "nu") { return new Symbol(0x1D708); }
        else if (symbolCode == "xi") { return new Symbol(0x1D709); }
        else if (symbolCode == "omicron") { return new Symbol(0x1D70A); }
        else if (symbolCode == "pi") { return new Symbol(0x1D70B); }
        else if (symbolCode == "rho") { return new Symbol(0x1D70C); }
        else if (symbolCode == "sigma") { return new Symbol(0x1D70E); }
        else if (symbolCode == "tau") { return new Symbol(0x1D70F); }
        else if (symbolCode == "upsilon") { return new Symbol(0x1D710); }
        else if (symbolCode == "phi") { return new Symbol(0x1D711); }
        else if (symbolCode == "chi") { return new Symbol(0x1D712); }
        else if (symbolCode == "psi") { return new Symbol(0x1D713); }
        else if (symbolCode == "omega") { return new Symbol(0x1D714); }

        // Greek Uppercase
        else if (symbolCode == "ALPHA") { return new Symbol(0x1D6E2); }
        else if (symbolCode == "BETA") { return new Symbol(0x1D6E3); }
        else if (symbolCode == "GAMMA") { return new Symbol(0x1D6E4); }
        else if (symbolCode == "DELTA") { return new Symbol(0x1D6E5); }
        else if (symbolCode == "EPSILON") { return new Symbol(0x1D6E6); }
        else if (symbolCode == "ZETA") { return new Symbol(0x1D6E7); }
        else if (symbolCode == "ETA") { return new Symbol(0x1D6E8); }
        else if (symbolCode == "THETA") { return new Symbol(0x1D6E9); }
        else if (symbolCode == "IOTA") { return new Symbol(0x1D6EA); }
        else if (symbolCode == "KAPPA") { return new Symbol(0x1D6EB); }
        else if (symbolCode == "LAMDA") { return new Symbol(0x1D6EC); }
        else if (symbolCode == "MU") { return new Symbol(0x1D6ED); }
        else if (symbolCode == "NU") { return new Symbol(0x1D6EE); }
        else if (symbolCode == "XI") { return new Symbol(0x1D6EF); }
        else if (symbolCode == "OMICRON") { return new Symbol(0x1D6F0); }
        else if (symbolCode == "PI") { return new Symbol(0x1D6F1); }
        else if (symbolCode == "RHO") { return new Symbol(0x1D6F2); }
        else if (symbolCode == "SIGMA") { return new Symbol(0x1D6F4); }
        else if (symbolCode == "TAU") { return new Symbol(0x1D6F5); }
        else if (symbolCode == "UPSILON") { return new Symbol(0x1D6F6); }
        else if (symbolCode == "PHI") { return new Symbol(0x1D6F7); }
        else if (symbolCode == "CHI") { return new Symbol(0x1D6F8); }
        else if (symbolCode == "PSI") { return new Symbol(0x1D6F9); }
        else if (symbolCode == "OMEGA") { return new Symbol(0x1D6FA); }

        // Double-Struck
        else if (symbolCode.length() == 3 && symbolCode.substr(0, 2) == "ds")
        {
            // DS Lowercase
            if (symbolCode[2] == 'a') { return new Symbol(0x1D552); }
            else if (symbolCode[2] == 'b') { return new Symbol(0x1D553); }
            else if (symbolCode[2] == 'c') { return new Symbol(0x1D554); }
            else if (symbolCode[2] == 'd') { return new Symbol(0x1D555); }
            else if (symbolCode[2] == 'e') { return new Symbol(0x1D556); }
            else if (symbolCode[2] == 'f') { return new Symbol(0x1D557); }
            else if (symbolCode[2] == 'g') { return new Symbol(0x1D558); }
            else if (symbolCode[2] == 'h') { return new Symbol(0x1D559); }
            else if (symbolCode[2] == 'i') { return new Symbol(0x1D55A); }
            else if (symbolCode[2] == 'j') { return new Symbol(0x1D55B); }
            else if (symbolCode[2] == 'k') { return new Symbol(0x1D55C); }
            else if (symbolCode[2] == 'l') { return new Symbol(0x1D55D); }
            else if (symbolCode[2] == 'm') { return new Symbol(0x1D55E); }
            else if (symbolCode[2] == 'n') { return new Symbol(0x1D55F); }
            else if (symbolCode[2] == 'o') { return new Symbol(0x1D560); }
            else if (symbolCode[2] == 'p') { return new Symbol(0x1D561); }
            else if (symbolCode[2] == 'q') { return new Symbol(0x1D562); }
            else if (symbolCode[2] == 'r') { return new Symbol(0x1D563); }
            else if (symbolCode[2] == 's') { return new Symbol(0x1D564); }
            else if (symbolCode[2] == 't') { return new Symbol(0x1D565); }
            else if (symbolCode[2] == 'u') { return new Symbol(0x1D566); }
            else if (symbolCode[2] == 'v') { return new Symbol(0x1D567); }
            else if (symbolCode[2] == 'w') { return new Symbol(0x1D568); }
            else if (symbolCode[2] == 'x') { return new Symbol(0x1D569); }
            else if (symbolCode[2] == 'y') { return new Symbol(0x1D56A); }
            else if (symbolCode[2] == 'z') { return new Symbol(0x1D56B); }
            
            // DS Uppercase
            else if (symbolCode[2] == 'A') { return new Symbol(0x1D538); }
            else if (symbolCode[2] == 'B') { return new Symbol(0x1D539); }
            else if (symbolCode[2] == 'C') { return new Symbol(0x2102); }
            else if (symbolCode[2] == 'D') { return new Symbol(0x1D53B); }
            else if (symbolCode[2] == 'E') { return new Symbol(0x1D53C); }
            else if (symbolCode[2] == 'F') { return new Symbol(0x1D53D); }
            else if (symbolCode[2] == 'G') { return new Symbol(0x1D53E); }
            else if (symbolCode[2] == 'H') { return new Symbol(0x210D); }
            else if (symbolCode[2] == 'I') { return new Symbol(0x1D540); }
            else if (symbolCode[2] == 'J') { return new Symbol(0x1D541); }
            else if (symbolCode[2] == 'K') { return new Symbol(0x1D542); }
            else if (symbolCode[2] == 'L') { return new Symbol(0x1D543); }
            else if (symbolCode[2] == 'M') { return new Symbol(0x1D544); }
            else if (symbolCode[2] == 'N') { return new Symbol(0x2115); }
            else if (symbolCode[2] == 'O') { return new Symbol(0x1D546); }
            else if (symbolCode[2] == 'P') { return new Symbol(0x2119); }
            else if (symbolCode[2] == 'Q') { return new Symbol(0x211A); }
            else if (symbolCode[2] == 'R') { return new Symbol(0x211D); }
            else if (symbolCode[2] == 'S') { return new Symbol(0x1D54A); }
            else if (symbolCode[2] == 'T') { return new Symbol(0x1D54B); }
            else if (symbolCode[2] == 'U') { return new Symbol(0x1D54C); }
            else if (symbolCode[2] == 'V') { return new Symbol(0x1D54D); }
            else if (symbolCode[2] == 'W') { return new Symbol(0x1D54E); }
            else if (symbolCode[2] == 'X') { return new Symbol(0x1D54F); }
            else if (symbolCode[2] == 'Y') { return new Symbol(0x1D550); }
            else if (symbolCode[2] == 'Z') { return new Symbol(0x2124); }
        }

        // Operators
        else if (symbolCode == "int") { return new Symbol(0x222B); }
        else if (symbolCode == "inf") { return new Symbol(0x221E); }
        else if (symbolCode == "RArrow") { return new Symbol(0x2192); }
        else if (symbolCode == "LArrow") { return new Symbol(0x2190); }
    }
}