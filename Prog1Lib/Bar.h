#pragma once
#ifdef MYTOOL_EXPORTS
#define MYTOOL_API __declspec(dllexport)
#else
#define MYTOOL_API __declspec(dllimport)
#endif

#include <string>
#include "Color.h"

using namespace std;
using namespace Tools::Console;

class MYTOOL_API Bar
{
	int value;
	u_int maxValue;
	u_int maxDisplayChar;

	Gradient color;


public:
	inline int GetValue()const
	{
		return value;
	}

	inline u_int GetMaxValue()const
	{
		return maxValue;
	}

	void SetMaxValue(const u_int& _maxValue)
	{
		maxValue = _maxValue;
	}

	inline u_int GetMaxDisplayChar()const
	{
		return maxDisplayChar;
	}

	void SetMaxDisplayChar(const u_int& _maxDisplayChar)
	{
		maxDisplayChar = _maxDisplayChar;
	}

	inline Gradient GetColor()const
	{
		return color;
	}
	
	void SetColor(const Gradient& _color)
	{
		color = _color;
	}
public :
	Bar();
	Bar(const u_int& _maxValue, const u_int& _maxDisplayChar, const Gradient& _color);
	Bar(const int _value, const u_int& _maxValue, const u_int& _maxDisplayChar, const Gradient& _color);

public:

	/// <summary>
	/// Regénére la barre
	/// </summary>
	/// <param name="_regenValue"></param>
	void RegenBar(const u_int _regenValue);

	/// <summary>
	/// Reduit la barre
	/// </summary>
	/// <param name="_reduceValue"></param>
	void ReduceBar(const u_int _reduceValue);

	string ToString()const;
};

