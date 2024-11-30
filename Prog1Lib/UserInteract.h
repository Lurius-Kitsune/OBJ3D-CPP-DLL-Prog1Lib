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
		/// <summary>
		/// Permet de récuper un input de l'utilisateur
		/// </summary>
		/// <typeparam name="T">Le type voulu</typeparam>
		/// <param name="_question">La question à posé</param>
		/// <returns>Renvoie un objet de type T correspondant</returns>
		template <typename Type>
		Type GetInput(const string& _question= "Que souhaitez-vous ?", const string& _answerAsker = "Réponse : ")
		{
			Type _answer;
			bool _isValid;

			DISPLAY(_question, true);
			do
			{
				DISPLAY(_answerAsker, false);
				cin >> _answer;
				_isValid = cin.good();
				CLEAR_CIN;
				CLEAR_SCREEN;

			} while (!_isValid);

			return _answer;
		}

		/// <summary>
		/// Permet d'obtenir une entrée utilisateur de string
		/// </summary>
		/// <param name="_question">La question à posé</param>
		/// <returns>Le string entrée</returns>
		MYTOOL_API string GetLine(const string& _question = "");

		/// <summary>
		/// Affiche un menu
		/// </summary>
		/// <param name="_options">La liste d'option</param>
		/// <param name="_currentIndex">L'index de la selection actuelle</param>
		/// <param name="_question">La question à posé</param>
		template <typename Type>
		void DisplayMenu(const vector<Type>& _options, const int _currentIndex, const string& _question, const string& _headMessage = "",
			const string& _endMessage = "", const bool _hasQuitOption = true, const vector<string>& _symbolsSelector = vector<string>())
		{
			const u_int& _size = static_cast<u_int>(_options.size());
			DISPLAY(_question, _question.empty() ? false : true);
			DISPLAY("==========ACTION==========", true);
			for (u_int _i = 0; _i < _size + _hasQuitOption; _i++)
			{
				string _firstSymbol = "", _secondSymbol = "" RESET;
				if (_i == _currentIndex)
				{
					_firstSymbol = PURPLE "[";
					_secondSymbol = PURPLE "]" RESET;
				}
				if (_i == _size)
				{
					DISPLAY(_firstSymbol << "Quitter" << _secondSymbol, true);
					break;
				}

				DISPLAY(_firstSymbol <<  _options[_i] << _secondSymbol, true);
			}
			DISPLAY("==========================", true);
		}

		template <typename Type>
		int OpenMenu(const vector<Type>& _options, const string& _question)
		{
			u_int _currentIndex = 0;
			const vector<string>& _symbolsSelector = { PURPLE "[", PURPLE "]" RESET };
			const u_int& _size = static_cast<u_int>(_options.size());
			DisplayMenu(_options, _currentIndex, _question, "==========ACTION==========", "==========================", true, _symbolsSelector);
			do
			{

				if (_kbhit())
				{
					// Attendre une touche
					u_int _input = 0;
					_input = _getch();

					// Si la touche est entrée, alors _isChoiceMade = true
					switch (_input)
					{
					case 13:
						return _currentIndex;
						// Si la touche est fleche du haut, alors _choiceIndex--
					case 72:
						_currentIndex = (_currentIndex <= 0 ? _size : _currentIndex - 1);
						break;
						// Si la touche est fleche du bas, alors _choiceIndex++
					case 80:
						_currentIndex = (_currentIndex >= _size ? 0 : _currentIndex + 1);
						break;
					default:
						break;
					}
					CLEAR_SCREEN;
					DisplayMenu(_options, _currentIndex, _question, "==========ACTION==========","==========================", true, _symbolsSelector);
				}

			} while (true);
		}
	}


	template <typename Type>
	int OpenMenuV2(const vector<Type>& _options, const string& _question,const u_int& _startIndex = 0, const string& _headMessage = "",
		const string& _endMessage = "", const bool _hasQuitOption = true, vector<string> _symbolsSelector = vector<string>())
	{
		u_int _currentIndex = _startIndex;
		if (_symbolsSelector.size() < 2)
			_symbolsSelector = { "<", ">"};

		const u_int& _size = static_cast<u_int>(_options.size());
		u_int _input = 0;
		while (true)
		{
			CLEAR_SCREEN;
			DisplayMenu(_options, _currentIndex, _question, _headMessage, _endMessage, _hasQuitOption, _symbolsSelector);
			// getch attend une touche
			_input = _getch();
			// Si la touche est entrée, alors _isChoiceMade = true
			switch (_input)
			{
			case 13:
				return _currentIndex;
				// Si la touche est fleche du haut, alors _choiceIndex--
			case 72:
				_currentIndex = (_currentIndex <= 0 ? _size : _currentIndex - 1);
				break;
				// Si la touche est fleche du bas, alors _choiceIndex++
			case 80:
				_currentIndex = (_currentIndex >= _size ? 0 : _currentIndex + 1);
				break;
			default:
				break;
			}
		}
	}
}
