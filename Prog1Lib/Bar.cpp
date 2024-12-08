#include "pch.h"
#include "Bar.h"

Bar::Bar()
{
	value = 0;
	maxValue = 0;
	maxDisplayChar = 10;
	color = Gradient();
}

Bar::Bar(const u_int& _maxValue, const u_int& _maxDisplayChar, const Gradient& _color)
{
	value = _maxValue;
	maxValue = _maxValue;
	maxDisplayChar = _maxDisplayChar;
	color = _color;
}

Bar::Bar(const int _value, const u_int& _maxValue, const u_int& _maxDisplayChar, const Gradient& _color)
{
	value = _value;
	maxValue = _maxValue;
	maxDisplayChar = _maxDisplayChar;
	color = _color;
}

void Bar::RegenBar(const u_int _regenValue)
{
	value = value + _regenValue >= maxValue ? maxValue : value + _regenValue;
}

void Bar::ReduceBar(const u_int _reduceValue)
{
	value = value - _reduceValue <= 0 ? 0 : value - _reduceValue;
}


string Bar::ToString() const
{
	u_int _maLifePercent = value * maxDisplayChar / maxValue;
	string _lifeDisplay;
	for (u_int _i = 0; _i < maxDisplayChar; _i++)
	{

		Color _color = _i < _maLifePercent ? color.ClampGradient(_i, maxDisplayChar) : Gradient({ 30, 33, 47 }, { 43, 46, 57 }).ClampGradient(_i, maxDisplayChar);
		_lifeDisplay += _color.ToString(false) + " ";
	}
	return _lifeDisplay + RESET;
}