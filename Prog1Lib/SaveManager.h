#pragma once

#ifdef MYTOOL_EXPORTS
#define MYTOOL_API __declspec(dllexport)
#else
#define MYTOOL_API __declspec(dllimport)
#endif

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <type_traits>

#include <vector>

#include "FileStream.h"
using namespace Tools;

using namespace std;

typedef ios_base ib;

namespace Save
{
	class MYTOOL_API SaveManager
	{
		string path;
		string* encryptionKey;

	public:
		SaveManager(const string& _path);
		SaveManager(const string& _path, const string& _encryptionKey);

		/// <summary>
		/// Sauvegarder une donn�e
		/// </summary>
		/// <typeparam name="T">Type de la donn�e</typeparam>
		/// <param name="_key">Cl�</param>
		/// <param name="_data">Valeur</param>
		template<typename T>
		void SaveData(const string& _key, const T& _data)
		{
			const string& _sData = "\n" + _key + ":" + Convert<T, string>(_data);
			FileStream _fs = FileStream(path, false, (encryptionKey ? *encryptionKey : ""), encryptionKey, ios_base::out | ios_base::binary | ios_base::in);

			if (KeyExists(_key))
			{
				cout << _fs.RemoveLine(GetKeyLine(_key)) << endl;
				cout << "Line: " << GetKeyLine(_key) << endl;
			} 

			// TODO Ajouter le _sData au fichier
		}

		/// <summary>
		/// Obtenir une donn�e � partir de sa cl�
		/// </summary>
		/// <typeparam name="T">Type de la donn�e</typeparam>
		/// <param name="_key">Cl�</param>
		/// <returns>Donn�e</returns>
		template<typename T>
		T GetData(const string& _key)
		{
			if (!KeyExists(_key)) throw exception("Key doesn't exist");
			
			FileStream _fs = FileStream(path, false, (encryptionKey ? *encryptionKey : ""), encryptionKey, ios_base::in | ios_base::binary);

			string _lineValue = _fs.ReadLine(GetKeyLine(_key));
			_lineValue = RemoveInvisibleChars(_lineValue);

			return Convert<string, T>(SplitString(_lineValue, ":")[1]);
		}

		/// <summary>
		/// V�rifier si une cl� donn�e existe
		/// </summary>
		/// <param name="_key">string : cl�</param>
		/// <returns>bool : existe ?</returns>
		bool KeyExists(const string& _key) const;


	private:
		/// <summary>
		/// Cr�er le fichier
		/// </summary>
		void FileCreate() const;

		/// <summary>
		/// R�cup�rer une instance flux entrant
		/// </summary>
		/// <returns>ifstream</returns>
		ifstream GetReadStream() const;

		/// <summary>
		/// R�cup�rer une istance de flux sortant
		/// </summary>
		/// <param name="_openmode">ios_base::openmode --> Pr�ciser quel mode d'ouverture (binary est compris dedans)</param>
		/// <returns>ofstream</returns>
		ofstream GetWriteStream(const int _openmode) const;

		/// <summary>
		/// R�cup�rer l'index � laquelle se trouve la cl�
		/// </summary>
		/// <param name="_key">string : cl�</param>
		/// <returns>int : -1 si non trouv�e | l'index de la ligne</returns>
		int GetKeyIndex(const string& _key) const;

		/// <summary>
		/// R�cup�rer la ligne � laquelle se trouve la cl�
		/// </summary>
		/// <param name="_key">string : cl�</param>
		/// <returns>int : -1 si non trouv�e | l'index de la ligne</returns>
		int GetKeyLine(const string& _key) const;

		/// <summary>
		/// M�thode pour recr�er le split d'un string
		/// </summary>
		/// <param name="_text">string : � split</param>
		/// <param name="_separator">char : sur quoi split</param>
		/// <returns>vector : tableau de string</returns>
		vector<string> SplitString(const string& _text, const char* _separator) const;


		/// <summary>
		/// Convertisseur entre types
		/// </summary>
		/// <typeparam name="Input">Type d'entr�e</typeparam>
		/// <typeparam name="Result">Type de sortie attendu</typeparam>
		/// <param name="_input">Valeur</param>
		/// <returns>Valeur en type attendu</returns>
		template<typename Input, typename Result>
		Result Convert(const Input& _input) const // "constexpr" sert � dire au compilateur qu'il doit analyser les chemins (les if), sinon il dit qu'il y'a une erreur car ce con pense
		{											// que t'essayes de convertir des types en de la merde. 

			if constexpr (is_same<Input, Result>::value) return _input;

			if constexpr (is_same<Input, string>::value) // Si la valeur d'entr�e est un string
			{
				if constexpr (is_same<Result, int>::value) return std::stoi(_input);
				else if constexpr (is_same<Result, bool>::value) return (_input == "true");
				else if constexpr (is_same<Result, char>::value) return _input[0];
			}
			else if constexpr (is_same<Input, int>::value) return to_string(_input);
			else if constexpr (is_same<Input, bool>::value) return (_input ? "true" : "false");
			else if constexpr (is_same<Input, char>::value) return _input[0];

			throw exception("Unable to convert type");
		}

		/// <summary>
		/// Retirer les caract�res invisibles d'une cha�ne de caract�re pour permettre une conversion
		/// </summary>
		/// <param name="_text"></param>
		/// <returns>string : cha�ne de caract�re sans les chars invisibles</returns>
		string RemoveInvisibleChars(string& _text)
		{
			_text.erase(std::remove(_text.begin(), _text.end(), '\0'), _text.end());
			_text.erase(std::remove(_text.begin(), _text.end(), ' '), _text.end());
			_text.erase(std::remove(_text.begin(), _text.end(), '\n'), _text.end());
			_text.erase(std::remove(_text.begin(), _text.end(), '\r'), _text.end());
			return _text;
		}
	};
}




