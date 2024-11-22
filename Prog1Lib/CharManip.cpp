#include "pch.h"
#include "CharManip.h"

MYTOOL_API char Tools::ToLower(char _char)
{
	const int _charValue = int(_char);
	if (_charValue >= 65 && _charValue <= 90)
	{
		_char = char(_charValue + 32);
	}

	return _char;
}

MYTOOL_API char Tools::ToUpper(char _char)
{
	const int _charValue = int(_char);
	if (_charValue >= 97 && _charValue <= 122)
	{
		_char = char(_charValue - 32);
	}

	return _char;
}

MYTOOL_API vector<string> Tools::SplitString(const string& _phrase, const char _separator)
{
	const size_t& _length = _phrase.length();
	vector<string> _splitString = vector<string>();
	string _word = "";
	for (u_int _i = 0; _i < _length; _i++)
	{
		if (_phrase[_i] == _separator)
		{
			_splitString.push_back(_word);
			_word = "";
			continue;
		}

		_word += _phrase[_i];
	}

	return _splitString;
}

MYTOOL_API string Tools::ToLowerString(const string& _phrase)
{
	const size_t& _length = _phrase.length();
	string _phraseModified = "";
	for (size_t _i = 0; _i < _length; _i++)
	{
		_phraseModified += ToLower(_phrase[_i]);
	}

	return _phraseModified;
}

MYTOOL_API string Tools::ToUpperString(const string& _phrase)
{
	const size_t& _length = _phrase.length();
	string _phraseModified = "";
	for (size_t _i = 0; _i < _length; _i++)
	{
		_phraseModified += ToUpper(_phrase[_i]);
	}

	return _phraseModified;
}

