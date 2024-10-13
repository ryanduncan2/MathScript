cmake_minimum_required(VERSION 3.22)
project(MathScript VERSION 1.0.0 LANGUAGES CXX)

find_package(Freetype)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

option (BUILD_TESTS "Build MathScript Tests" ON)

set(MATHSCRIPT_SRC_FILES
    src/Calculator.cpp
    src/Exception.cpp
    src/ScriptEngine.cpp
    src/SymbolTree.cpp
    src/Range.cpp

    src/Functions/Constant.cpp
    src/Functions/Variable.cpp

    src/Functions/Binary/Exponential.cpp
    src/Functions/Binary/Logarithm.cpp
    src/Functions/Binary/Product.cpp
    src/Functions/Binary/Quotient.cpp
    src/Functions/Binary/Sum.cpp

    src/Functions/Trigonometric/Cosecant.cpp
    src/Functions/Trigonometric/Cosine.cpp
    src/Functions/Trigonometric/Cotangent.cpp
    src/Functions/Trigonometric/Secant.cpp
    src/Functions/Trigonometric/Sine.cpp
    src/Functions/Trigonometric/Tangent.cpp

    src/Functions/Unary/Negation.cpp

    src/Rendering/Image.cpp
    src/Rendering/Font.cpp
    src/Rendering/Colour.cpp
    src/Rendering/Expression.cpp
    src/Rendering/ExpressionStructure.cpp
    src/Rendering/Expressions/Chain.cpp
    src/Rendering/Expressions/Text.cpp
    src/Rendering/Expressions/Fraction.cpp
    src/Rendering/Expressions/Symbol.cpp
    src/Rendering/Expressions/Integral.cpp
    src/Rendering/Expressions/Sigma.cpp
)

add_library(MathScript STATIC ${MATHSCRIPT_SRC_FILES})
target_include_directories(MathScript PRIVATE include "${ST_INCLUDE_DIRS}" ${FREETYPE_INCLUDE_DIRS})
target_link_libraries(MathScript "${ST_LIBRARIES}" ${FREETYPE_LIBRARIES})

if (BUILD_TESTS)
    add_executable(MathScriptTests ${MATHSCRIPT_SRC_FILES} src/Main.cpp)
    target_include_directories(MathScriptTests PRIVATE include "${ST_INCLUDE_DIRS}" ${FREETYPE_INCLUDE_DIRS})
    target_link_libraries(MathScriptTests "${ST_LIBRARIES}" ${FREETYPE_LIBRARIES})
endif()