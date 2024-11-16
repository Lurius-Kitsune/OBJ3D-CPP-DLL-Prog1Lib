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
		/// Sauvegarder une donnée
		/// </summary>
		/// <typeparam name="T">Type de la donnée</typeparam>
		/// <param name="_key">Clé</param>
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
		/// Obtenir une donnée à partir de sa clé
		/// </summary>
		/// <typeparam name="T">Type de la donnée</typeparam>
		/// <param name="_key">Clé</param>
		/// <returns>Donnée</returns>
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
		/// Vérifier si une clé donnée existe
		/// </summary>
		/// <param name="_key">string : clé</param>
		/// <returns>bool : existe ?</returns>
		bool KeyExists(const string& _key) const;


	private:
		/// <summary>
		/// Créer le fichier
		/// </summary>
		void FileCreate() const;

		/// <summary>
		/// Récupérer une instance flux entrant
		/// </summary>
		/// <returns>ifstream</returns>
		ifstream GetReadStream() const;

		/// <summary>
		/// Récupérer une istance de flux sortant
		/// </summary>
		/// <param name="_openmode">ios_base::openmode --> Préciser quel mode d'ouverture (binary est compris dedans)</param>
		/// <returns>ofstream</returns>
		ofstream GetWriteStream(const int _openmode) const;

		/// <summary>
		/// Récupérer l'index à laquelle se trouve la clé
		/// </summary>
		/// <param name="_key">string : clé</param>
		/// <returns>int : -1 si non trouvée | l'index de la ligne</returns>
		int GetKeyIndex(const string& _key) const;

		/// <summary>
		/// Récupérer la ligne à laquelle se trouve la clé
		/// </summary>
		/// <param name="_key">string : clé</param>
		/// <returns>int : -1 si non trouvée | l'index de la ligne</returns>
		int GetKeyLine(const string& _key) const;

		/// <summary>
		/// Méthode pour recréer le split d'un string
		/// </summary>
		/// <param name="_text">string : à split</param>
		/// <param name="_separator">char : sur quoi split</param>
		/// <returns>vector : tableau de string</returns>
		vector<string> SplitString(const string& _text, const char* _separator) const;


		/// <summary>
		/// Convertisseur entre types
		/// </summary>
		/// <typeparam name="Input">Type d'entrée</typeparam>
		/// <typeparam name="Result">Type de sortie attendu</typeparam>
		/// <param name="_input">Valeur</param>
		/// <returns>Valeur en type attendu</returns>
		template<typename Input, typename Result>
		Result Convert(const Input& _input) const // "constexpr" sert à dire au compilateur qu'il doit analyser les chemins (les if), sinon il dit qu'il y'a une erreur car ce con pense
		{											// que t'essayes de convertir des types en de la merde. 

			if constexpr (is_same<Input, Result>::value) return _input;

			if constexpr (is_same<Input, string>::value) // Si la valeur d'entrée est un string
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
		/// Retirer les caractères invisibles d'une chaîne de caractère pour permettre une conversion
		/// </summary>
		/// <param name="_text"></param>
		/// <returns>string : chaîne de caractère sans les chars invisibles</returns>
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




