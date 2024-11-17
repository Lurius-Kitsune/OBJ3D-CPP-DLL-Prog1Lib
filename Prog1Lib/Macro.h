#pragma once

#ifdef MYTOOL_EXPORTS
#define MYTOOL_API __declspec(dllexport)
#else
#define MYTOOL_API __declspec(dllimport)
#endif

#include "Color.h"

namespace Tools
{

    #define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

    #define CLEAR_CIN cin.clear(); \
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');

    #define DISPLAY(_value, _makeEndl) cout << _value; \
                                       if (_makeEndl) cout << endl;
    #define SPACE DISPLAY("", true);
    #define DISPLAY_LINE DISPLAY("=========================", true);

    #define CLEAR_SCREEN system("cls");

    #pragma region Forward
        // Forward
        MYTOOL_API void Config();
    #pragma endregion
}



