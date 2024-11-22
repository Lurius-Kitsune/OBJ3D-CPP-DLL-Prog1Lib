#pragma once
#include "DynamicArray.h"
#include <string>

#ifdef MYTOOL_EXPORTS
#define MYTOOL_API __declspec(dllexport)
#else
#define MYTOOL_API __declspec(dllimport)
#endif

using namespace std;

namespace Tools
{
	/// <summary>
	/// Met le character en minuscule
	/// </summary>
	/// <param name="_char">Caractère concerner</param>
	/// <returns>Caractère miniscule si c'est une lettre, sinon juste le caractère</returns>
	MYTOOL_API char ToLower(char _char);
	
	/// <summary>
	/// Met le character en Majuscule
	/// </summary>
	/// <param name="_char">Caractère concerner</param>
	/// <returns>Caractère majuscule si c'est une lettre, sinon juste le caractère</returns>
	MYTOOL_API char ToUpper(char _char);

	MYTOOL_API DynamicArray<string> SplitString(const string& _phrase, const char _separator);

	/// <summary>
	/// Met le character en minuscule
	/// </summary>
	/// <param name="_char">Caractère concerner</param>
	/// <returns>Caractère miniscule si c'est une lettre, sinon juste le caractère</returns>
	MYTOOL_API string ToLowerString(const string& _phrase);

	/// <summary>
	/// Met le character en Majuscule
	/// </summary>
	/// <param name="_char">Caractère concerner</param>
	/// <returns>Caractère majuscule si c'est une lettre, sinon juste le caractère</returns>
	MYTOOL_API string ToUpperString(const string& _phrase);
}