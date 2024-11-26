#include "pch.h"
#include "Color.h"

MYTOOL_API string Tools::Console::RainbowEveryChar(const string& _word)
{
	string _newWord = "";
	for (u_int _i = 0; _i < _word.length(); _i++)
	{
		_newWord += GetRandomColor() + _word[_i];
	}

	return _newWord + RESET;
}

MYTOOL_API string Tools::Console::RainbowString(const string& _word)
{
	return GetRandomColor() + _word + RESET;
}

MYTOOL_API void Tools::Console::DisplayRainbow(const string& _text)
{
	while (!_kbhit())
	{
		CLEAR_SCREEN;
		DISPLAY(RainbowString(_text), true);
		const auto _start = high_resolution_clock::now();
		sleep_for(200ms);
		const auto _end = high_resolution_clock::now();
		const duration<double, milli> _elapsed = _end - _start;
	}
}

MYTOOL_API string Tools::Console::GetRandomColor()
{
	const string _rainbowTable[] =
	{
		WHITE,
		DARK_RED,
		RED ,
		DARK_ORANGE ,
		ORANGE,
		DARK_YELLOW,
		YELLOW,
		LIME,
		GREEN,
		BLUE,
		LIGHT_BLUE,
		CYAN,
		PINK,
		MAGENTA,
		PURPLE,
		BROWN
	};

	const u_int _rainbowSize = size(_rainbowTable) - 1;

	return _rainbowTable[RandomInt(0,_rainbowSize)];
}
