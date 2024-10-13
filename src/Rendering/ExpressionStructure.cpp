#include "MathScript/Rendering/ExpressionStructure.h"

namespace MathScript
{
    ExpressionStructure::ExpressionStructure()
        : m_Superscript(nullptr), 
          m_Subscript(nullptr),
          m_Underscript(nullptr)
    {
    }

    ExpressionStructure::~ExpressionStructure()
    {
        delete m_Superscript;
        delete m_Subscript;
        delete m_Underscript;
    }
}