#include "pch.h"
#include "UserInteract.h"

MYTOOL_API int Tools::UserInteraction::GetInt()
{
	int _answer;
	bool _isValid;

	DISPLAY("Réponse : ", false);
	do
	{
		cin >> _answer;
		_isValid = cin.good();
		CLEAR_CIN;

	} while (!_isValid);
	
	return _answer;
}

MYTOOL_API string Tools::UserInteraction::GetLine(const string& _question)
{
	DISPLAY(_question, _question.empty() ? false : true)
	string _line = string();
	bool _wantToQuit;

	do
	{
		const int _charASCII = getchar();
		_wantToQuit = _charASCII == EOF || _charASCII == '\n';

		if (!_wantToQuit)
		{
			_line += char(_charASCII);
		}

	} while (!_wantToQuit);

	return _line;
}

MYTOOL_API bool Tools::UserInteraction::GetBool(const string& _answersPossible)
{
	DISPLAY(_answersPossible, true);
	DISPLAY("Réponse : ", false);
	bool _answer;
	cin >> _answer;
	CLEAR_CIN;
	return _answer;
}

MYTOOL_API void Tools::UserInteraction::DisplayMenu(const string* _options, 
	const u_int& _currentIndex, const u_int& _maxOptions, 
	const string& _question, 
	string* _selectors, const string& _selectorColors)
{
	DISPLAY(_question, _question.empty() ? false : true);
	DISPLAY("==========ACTION==========", true);
	for (u_int _i = 0; _i <= _maxOptions; _i++)
	{
		string _firstSymbol = "", _secondSymbol = "" RESET;
		if (_i == _currentIndex)
		{
			_firstSymbol = _selectorColors + _selectors[0];
			_secondSymbol = _selectorColors + _selectors[1] + RESET ;
		}
		DISPLAY(_firstSymbol + (_i == _maxOptions ? "Quitter" : _options[_i]) + _secondSymbol, true);
	}
	DISPLAY("==========================", true);
}

MYTOOL_API u_int Tools::UserInteraction::OpenMenu(const string* _options, 
	const u_int& _maxOptions, string* _selectors, 
	const string& _selectorColors, const string& _question)
{
	u_int _currentIndex = 0, _input = 0;
	while (true)
	{
		DisplayMenu(_options, _currentIndex, _maxOptions, _question, _selectors, _selectorColors);
		// Getch attend une entree utilisateur une touche
		_input = _getch();
		CLEAR_SCREEN;
		// Si la touche est entrée, alors _isChoiceMade = true
		switch (_input)
		{
		case 13:
			return _currentIndex;
			// Si la touche est fleche du haut, alors _choiceIndex--
		case 72:
			_currentIndex = (_currentIndex <= 0 ? _maxOptions : _currentIndex - 1);
			break;
			// Si la touche est fleche du bas, alors _choiceIndex++
		case 80:
			_currentIndex = (_currentIndex >= _maxOptions ? 0 : _currentIndex + 1);
			break;
		default:
			break;
		}
	}
}

MYTOOL_API u_int Tools::UserInteraction::OpenMenu(const string* _options, const u_int& _maxOptions, const string& _question)
{
	string _selectorSymbols[2] = { "[","]" };
	return OpenMenu(_options, _maxOptions, _selectorSymbols, "", _question);
}

