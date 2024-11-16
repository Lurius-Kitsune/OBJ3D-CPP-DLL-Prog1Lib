#pragma once

#ifdef MYTOOL_EXPORTS
#define MYTOOL_API __declspec(dllexport)
#else
#define MYTOOL_API __declspec(dllimport)
#endif

#include "Macro.h"     
namespace Tools
{
	namespace UserInteraction
	{
		MYTOOL_API int GetInt();
		MYTOOL_API string GetLine(const string& _question = "");

		MYTOOL_API bool GetBool(const string& _answersPossible = "[0] Oui\t[1] Non");

		MYTOOL_API void DisplayMenu(const string* _options, const u_int& _currentIndex, const u_int& _maxOptions, const string& _question, string* _selectors, const string& _selectorColors);
		MYTOOL_API u_int OpenMenu(const string* _options, const u_int& _maxOptions, string* _selectors, const string& _selectorColors = "", const string& _question = "");
		MYTOOL_API u_int OpenMenu(const string* _options, const u_int& _maxOptions, const string& _question = "");
	}

}
