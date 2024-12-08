#pragma once
#ifdef MYTOOL_EXPORTS
#define MYTOOL_API __declspec(dllexport)
#else
#define MYTOOL_API __declspec(dllimport)
#endif

#include "Macro.h"
#include "Color.h"
#include "DisplaySystem.h"

using namespace Tools::Console;

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
		Type GetInput(const string& _question= "Que souhaitez-vous ?")
		{
			Type _answer;
			bool _isValid;

			DISPLAY(_question, true);
			do
			{
				DISPLAY("Réponse : ", false);
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
		void DisplayMenu(const vector<Type>& _options, const int _currentIndex, const string& _question, const bool _center)
		{
			vector<string> _menu;
			const size_t& _size = _options.size();
			_menu.push_back("==========ACTION==========");
			for (u_int _i = 0; _i < _size; _i++)
			{
				string _firstSymbol = "", _secondSymbol = "" RESET;
				if (_i == _currentIndex)
				{
					_firstSymbol = PURPLE "[";
					_secondSymbol = PURPLE "]" RESET;
				}

				_menu.push_back(_firstSymbol + to_string(_options[_i]) + _secondSymbol);
			}
			_menu.push_back("==========================");


			if (_center)
			{
				DisplayOnceCenterMultiLine(_menu, RT_OFF, { 0, 0 });
			}
			else
			{
				for (const string& _line : _menu)
				{
					DISPLAY(_line, true);
				}
			}
		}

		template <typename Type>
		void DisplayMenu(const vector<Type*>& _options, const int _currentIndex, const string& _question, const bool _center)
		{
			DisplayMenu(vector<Type>(_options.begin(), _options.end()), _currentIndex, _question, _center);
		}

		template <typename Type>
		int OpenMenu(const vector<Type>& _options, const string& _question, const bool _center = false)
		{
			u_int _currentIndex = 0;
			const size_t& _size = _options.size();
			DisplayMenu(_options, _currentIndex, _question, _center);
			do
			{

				if (_kbhit())
				{
					// Attendre une touche
					u_int _input = 0;
					_input = _getch();
					if (_input == 224)
					{
						_input = _getch();
					}

					// Si la touche est entrée, alors _isChoiceMade = true
					switch (_input)
					{
					case 13:
						system("cls");
						return _currentIndex;
					case 72:
						// Si la touche est fleche du haut, alors _choiceIndex--
						_currentIndex = (_currentIndex <= 0 ? (u_int)_size : _currentIndex - 1);
						break;
					case 80:
						// Si la touche est fleche du bas, alors _choiceIndex++
						_currentIndex = (_currentIndex >= (u_int)_size ? 0 : _currentIndex + 1);
						break;
					default:
						break;
					}
					CLEAR_SCREEN;
					DisplayMenu(_options, _currentIndex, _question, _center);
				}

			} while (true);
		}
	}

}
