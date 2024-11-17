#include "pch.h"
#include "DisplaySystem.h"
#include <Windows.h>
#include <conio.h>
#include "Color.h"
#include <string>
#include <fstream>

using namespace Tools::Console;

string DisplayRainbowType(const string& _text, const RainbowType& _type)
{
	switch (_type)
	{
	case RT_OFF:
		return _text;
	case RT_CHAR:
		return RainbowEveryChar(_text);
	case RT_TEXT:
		return RainbowString(_text);
	}
	return _text;
}

DISPLAYSYSTEM_API void Tools::Console::SetCursorPosition(const u_int& _x, const u_int& _y, const bool _cursor)
{
	static const HANDLE _hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO _info;
	std::cout.flush();
	_info.dwSize = 100;
	_info.bVisible = _cursor;
	COORD coord = { (SHORT)_x, (SHORT)_y };
	SetConsoleCursorInfo(_hOut, &_info);
	SetConsoleCursorPosition(_hOut, coord);
}

DISPLAYSYSTEM_API Coord Tools::Console::GetCenterConsole()
{
	CONSOLE_SCREEN_BUFFER_INFO _csbi;
	int _columns, _rows;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &_csbi);
	_columns = _csbi.srWindow.Right - _csbi.srWindow.Left;
	_rows = _csbi.srWindow.Bottom - _csbi.srWindow.Top;
	return { _columns, _rows };
}

bool CheckConsoleSize(Coord& _center, Coord& _previousCenter, const string& _text, const Coord& _padding, int _height = 1)
{
	if (_height < 1) _height = 1;
	const string& _errorText = "Agrandissez la taille de la console !";
	_center = GetCenterConsole();
	if (_previousCenter.x != _center.x || _previousCenter.y != _center.y) system("cls");

	if (_center.x + _padding.x < _text.size() || _center.y + _padding.y < _height)
	{
		if (_errorText.size() > _center.x)
		{
			system("cls");
			return true;
		}
		SetCursorPosition((_center.x - u_int(_errorText.size())) / 2, 0);
		cout << BLINK_COLOR(RED) << _errorText << RESET;
		_previousCenter = _center;
		return true;
	}
	return false;
}

DISPLAYSYSTEM_API void Tools::Console::DisplayCenterLine(const string& _text, const RainbowType& _type, const Coord& _padding, const int _exitKey)
{
	int _key = 0;
	Coord _center = GetCenterConsole();
	Coord _previousCenter = _center;
	system("cls");
	do
	{
		if (_kbhit())
		{
			_key = _getch();
		}
		if (CheckConsoleSize(_center, _previousCenter, _text, _padding)) continue;
		SetCursorPosition(((_center.x + _padding.x) - u_int(_text.size())) / 2, (_center.y + _padding.y) / 2);
		printf(DisplayRainbowType(_text, _type).c_str());
		_previousCenter = _center;
	} while (_key != _exitKey);
	cout << RESET;
}

DISPLAYSYSTEM_API void Tools::Console::DisplayCenterLineWithInput(const string& _text, int& _input, const RainbowType& _type, const Coord& _padding)
{
	Coord _center = GetCenterConsole();
	Coord _previousCenter = _center;
	system("cls");
	do
	{
		if (_kbhit())
		{
			_input = _getch();
			cout << RESET;
			return;
		}
		if (CheckConsoleSize(_center, _previousCenter, _text, _padding)) continue;
		SetCursorPosition(((_center.x + _padding.x) - u_int(_text.size())) / 2, (_center.y + _padding.y) / 2);
		printf(DisplayRainbowType(_text, _type).c_str());
		_previousCenter = _center;
	} while (true);
}

DISPLAYSYSTEM_API void Tools::Console::DisplayCenterMultiLine(const string* _textArray, const u_int& _size, const RainbowType& _type, const Coord& _padding, const int _exitKey)
{
	int _key = 0;
	Coord _center = GetCenterConsole();
	Coord _previousCenter = _center;
	system("cls");
	do
	{
		for (u_int _index = 0; _index < _size; _index++)
		{
			if (_kbhit())
			{
				_key = _getch();
			}
			if (CheckConsoleSize(_center, _previousCenter, _textArray[_index], _padding, _size)) continue;
			SetCursorPosition(((_center.x + _padding.x) - u_int(_textArray[_index].size())) / 2, (_center.y + (2 * ((_padding.y - _size) / 2 + _index))) / 2);
			printf(DisplayRainbowType(_textArray[_index], _type).c_str());
			_previousCenter = _center;
		}
	} while (_key != _exitKey);
	cout << RESET;
}

DISPLAYSYSTEM_API void Tools::Console::DisplayCenterMultiLineWithInput(const string* _textArray, const u_int& _size, int& _input, const RainbowType& _type, const Coord& _padding)
{
	Coord _center = GetCenterConsole();
	Coord _previousCenter = _center;
	system("cls");
	do
	{
		for (u_int _index = 0; _index < _size; _index++)
		{
			if (_kbhit())
			{
				_input = _getch();
				cout << RESET;
				return;
			}
			if (CheckConsoleSize(_center, _previousCenter, _textArray[_index], _padding, _size)) continue;
			SetCursorPosition(((_center.x + _padding.x) - u_int(_textArray[_index].size())) / 2, (_center.y + (2 * ((_padding.y - _size) / 2 + _index))) / 2);
			printf(DisplayRainbowType(_textArray[_index], _type).c_str());
			_previousCenter = _center;
		}
	} while (true);
}

DISPLAYSYSTEM_API void Tools::Console::DisplayOnceCenterLine(const string& _text, const RainbowType& _type, const Coord& _padding)
{
	Coord _center = GetCenterConsole();
	Coord _previousCenter = _center;
	if (CheckConsoleSize(_center, _previousCenter, _text, _padding)) return;
	SetCursorPosition(((_center.x + _padding.x) - u_int(_text.size())) / 2, (_center.y + _padding.y) / 2);
	printf(DisplayRainbowType(_text, _type).c_str());
	cout << RESET;
	_previousCenter = _center;
}

DISPLAYSYSTEM_API void Tools::Console::DisplayOnceCenterMultiLine(const string* _textArray, const u_int& _size, const RainbowType& _type, const Coord& _padding)
{
	Coord _center = GetCenterConsole();
	Coord _previousCenter = _center;
	for (u_int _index = 0; _index < _size; _index++)
	{
		if (CheckConsoleSize(_center, _previousCenter, _textArray[_index], _padding, _size)) continue;
		SetCursorPosition(((_center.x + _padding.x) - u_int(_textArray[_index].size())) / 2, (_center.y + (2 * ((_padding.y - _size) / 2 + _index))) / 2);
		printf(DisplayRainbowType(_textArray[_index], _type).c_str());
		_previousCenter = _center;
	}
}

string** MakeAnimatedFrame(const string& _filePath, const string& _filePrefix, const u_int& _quantity, bool& _hasEnded)
{

	// TODO
	return nullptr;
}

DISPLAYSYSTEM_API void Tools::Console::DisplayAnimatedCenterMultiLine(const string& _filePath, const string& _filePrefix, const u_int& _quantity, const u_int& _size, const RainbowType& _type, const Coord& _padding)
{
	bool _hasEnded = false;
	while (!_hasEnded)
	{
		DisplayOnceCenterLine("Chargement...", RT_CHAR, _padding);
		//MakeAnimatedFrame(_filePath, _filePrefix, _quantity, _hasEnded);
	}
}