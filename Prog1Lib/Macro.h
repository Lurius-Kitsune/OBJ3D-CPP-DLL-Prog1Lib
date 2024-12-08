#pragma once

#ifdef MYTOOL_EXPORTS
#define MYTOOL_API __declspec(dllexport)
#else
#define MYTOOL_API __declspec(dllimport)
#endif

#include <iostream>

using namespace std;
namespace Tools
{

    #define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

    #define CLEAR_CIN cin.clear(); \
                cin.ignore((numeric_limits<streamsize>::max)(), '\n'); \
                cin.seekg(cin.beg);

    #define DISPLAY(_value, _makeEndl) cout << _value; \
                                       if (_makeEndl) cout << endl;
    #define SPACE DISPLAY("", true);
    #define DISPLAY_LINE DISPLAY("=========================", true);

    #define CLEAR_SCREEN system("cls");

    #pragma region Forward
        // Forward
        MYTOOL_API void Config(const bool _useLocal = false);
    #pragma endregion
}



